/*  ValidateScripts
    Copyright(C) 2023 Lukas Cone

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

#include "project.h"
#include "script.hpp"
#include "spike/app_context.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/master_printer.hpp"
#include "spike/reflect/reflector.hpp"
#include <fstream>
#include <set>

std::string_view filters[]{
    ".resources$", ".instances", ".level$",
    ".gameinfo$",  ".stats$",    ".session$",
};

static AppInfo_s appInfo{
    .filteredLoad = true,
    .multithreaded = false,
    .header = ValidateScripts_DESC " v" ValidateScripts_VERSION
                                   ", " ValidateScripts_COPYRIGHT "Lukas Cone",
    .filters = filters,
};

std::set<std::string_view> IGNORE_MEMBERS{
    "ReloadAfterXMisfires",
    "Collidable",
    "EngineCutoffVelocity",
    "AmmoType",
    "FullParticleLighting",
    "Team",
    "Head",
    "ForceFOV",
    "ForceFOVVal",
    "UseNewEffects",
    "VelvetFactor",
    "RagDollResource",
    "PSFXT_SHIELDREGENSTART___NOT_USED",
    "PSFXT_SHIELDREGENEND___NOT_USED",
    "SpreadForPlayer",
    "HitBoxModifier",
    "MinimumPersonalInterval",
    "HeadShotModifier",
    "BurstFire",
};

std::map<std::string_view, std::set<std::string_view>> IGNORE_CLASSMEMBERS{
    {"AILift", {"QUICKSAVE"}},
    {"AIBugCliffMite", {"QUICKSAVE", "Dust_System"}},
    {"AIBugWarrior", {"QUICKSAVE", "Dust_System"}},
    {"AIBugChariot", {"Dust_System", "Special_Mode"}},
    {"AIBugHopper", {"Dust_System"}},
    {"AIBugBlaster", {"Dust_System", "Special_Mode"}},
    {"AIBugTankerBaby", {"Dust_System"}},
    {"AIDropshipMarauder", {"QUICKSAVE_AIDropshipGrunt"}},
    {"AIStaticGunDouble",
     {"PrimaryAmmo", "SecondaryAmmo", "Sounds", "UsePrompt"}},
    {"AIBugWarriorTigerShard", {"QUICKSAVE", "Dust_System"}},
    {"AIBugWarriorTigerSpit", {"QUICKSAVE", "Dust_System"}},
    {"AIBugWarriorTiger", {"QUICKSAVE", "Dust_System"}},
    {"AIBugWarriorRoyal", {"QUICKSAVE", "Dust_System"}},
    {"AIPickupItemHealth", {"QUICKSAVE", "Amount"}},
    {"AIWeaponRailgun", {"QUICKSAVE_Railgun", "QUICKSAVE", "Flash"}},
    {"AIWeaponShotgun", {"QUICKSAVE", "Flash"}},
    {"AIWeaponRocket", {"QUICKSAVE", "QUICKSAVE_Rocket"}},
    {"AIWeaponMoritiaMk2Carbine", {"QUICKSAVE", "QUICKSAVE_Mk2Carbine"}},
    {"AIWeaponMoritiaMk2Shotgun",
     {"QUICKSAVE", "QUICKSAVE_Mk2Shotgun", "BulletAmmo"}},
    {"AIWeaponMoritiaMk2Zoom",
     {"QUICKSAVE", "QUICKSAVE_Mk2Zoom", "Flash", "Tracer", "Flash3D"}},
    {"AIBugSentinel", {"Dust_System", "Special_Mode"}},
    {"AIPickupItemObjective", {"QUICKSAVE"}},
    {"AIBugTanker", {"Special_Mode"}},
    {"AIWeaponMissile", {"QUICKSAVE"}},
    {"AIBugHopperRippler", {"Dust_System"}},
    {"AIPlayer", {"Weapon_StowedHeavy", "Weapon_Stowed0", "Dust", "Torch"}},
    {"TuningDataScript_MoritiaMk4Grenades",
     {"ProximityCheckTime", "ProximityCheckRadius", "ProximityCheckLife",
      "LaunchVel", "LaunchVelZ", "Drag", "Blastforce", "BlastHotspot",
      "BlastFalloff"}},
    {"TuningDataScriptDamage", {"Threshold"}},
    {"TuningDataScript_Tanker", {"FootImpact"}},
    {"TuningDataScript_Warrior", {"FootImpact"}},
    {"TuningDataScriptShake", {"Length"}},
    {"ResourceParticleFlareParticle",
     {"Smoke_ParticleType", "Smoke_Min_U", "Smoke_Max_U", "Smoke_Min_V",
      "Smoke_Max_V", "Smoke_Size0", "Smoke_Size1", "Smoke_Life", "Smoke_Rate"}},
    {"ResourceParticleNuclearBlastForce",
     {"StartTime", "EndTime", "StartVel", "EndVel", "WithDir",
      "AgainstDir", "dirx", "diry", "dirz"}},
};

AppInfo_s *AppInitModule() { return &appInfo; }

struct ReflectorFriend : Reflector {
  using Reflector::GetReflectedType;
};

struct ClassInfo {
  ClassInfo(const reflectorStatic *ref) : refInst(ref, nullptr), pv(refInst) {}
  operator bool() { return pv.data; }
  ReflectorFriend &Get() { return reinterpret_cast<ReflectorFriend &>(pv); }

  // private:
  ReflectedInstance refInst;
  ReflectorPureWrap pv;
};

std::map<std::string, size_t> folderScriptSize;

void AppFinishContext() {
  for (auto &[fld, sz] : folderScriptSize) {
    PrintInfo(fld, ": ", sz);
  }
};

void AppProcessFile(AppContext *ctx) {
  std::vector<ClassInfo> classes;
  classes.reserve(50);
  size_t scriptSize = 0;

  auto NewClass = [&](std::string_view name) {
    if (!name.starts_with("class_")) {
      throw std::runtime_error("class must start with class_");
    }
    name.remove_prefix(6);
    classes.clear();

    auto found = reflectorStatic::Registry().find(name);

    if (found != reflectorStatic::Registry().end()) {
      classes.emplace_back(found->second);
      scriptSize += found->second->classSize;
    } else {
      PrintError("Cannot find reflected class: ", name);
    }
  };

  auto NewMember = [&](std::string_view name, ValueType type) {
    if (classes.empty()) {
      return;
    }

    auto lastClass = classes.back();

    if (!lastClass) {
      if (type == VL_SUBCLASS) {
        classes.emplace_back(nullptr);
      }
      return;
    }

    int8 index = -1;

    if (name.size() > 3 && name.back() == '_' &&
        name.at(name.size() - 3) == '_') {
      index = name.at(name.size() - 2);
      name.remove_suffix(3);
    }

    auto memberType = lastClass.Get().GetReflectedType(name);

    if (!memberType) {
      auto found = IGNORE_CLASSMEMBERS.find(lastClass.Get().GetClassName());

      if ((found == IGNORE_CLASSMEMBERS.end() ||
           !found->second.contains(name)) &&
          !IGNORE_MEMBERS.contains(name)) {
        auto parentClass =
            classes.size() > 1 ? classes.at(classes.size() - 2) : nullptr;
        std::string_view parentClassName(
            parentClass ? parentClass.Get().GetClassName() : "");
        PrintError("Member: ", name,
                   " not found in class: ", lastClass.Get().GetClassName(),
                   ", ", parentClassName);
      }

      if (type == VL_SUBCLASS) {
        classes.emplace_back(nullptr);
      }
      return;
    } else if (index > -1) {
      if (memberType->type != REFType::Array) {
        PrintError("Member: ", name, " reflected type is not array.");
      } else if (index - '0' >= memberType->asArray.numItems) {
        PrintError("Member: ", name, " array index out of range, ", index - '0',
                   " >= ", memberType->asArray.numItems);
      }
    } else if (memberType->container == REFContainer::ContainerVectorMap) {
      classes.emplace_back(nullptr);
      return;
    }

    if (type == VL_SUBCLASS) {
      if (memberType->type == REFType::Vector) {
        classes.emplace_back(nullptr);
        return;
      }

      auto cHash = memberType->asClass.typeHash;

      if (memberType->type == REFType::Array) {
        if (memberType->asArray.type != REFType::Class) {
          classes.emplace_back(nullptr);
          return;
        }

        cHash = memberType->asArray.asClass.typeHash;
      }

      auto found = reflectorStatic::Registry().find(JenHash(cHash));

      if (found != reflectorStatic::Registry().end()) {
        classes.emplace_back(found->second);
      } else {
        classes.emplace_back(nullptr);
        PrintError("Cannot find reflected sub class for member: ", name);
      }
    }
  };

  ScriptParser parser{ctx->GetStream()};
  parser.newClass = NewClass;
  parser.newMember = NewMember;
  parser.newValue = [](auto) {};
  parser.subclassEnd = [&] {
    if (classes.empty()) {
      return;
    }

    classes.pop_back();
  };

  parser.Process();

  auto folderName = ctx->workingFile.GetFolder();

  folderName.remove_suffix(sizeof("scripts/"));
  folderName.remove_prefix(folderName.find_last_of('/') + 1);

 folderScriptSize[std::string(folderName)] += scriptSize;
}
