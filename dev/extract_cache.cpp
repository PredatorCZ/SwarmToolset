/*  ExtractCache
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
#include "spike/app_context.hpp"
#include "spike/except.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/io/stat.hpp"
#include "stcache_internal.hpp"
#include "zstd.h"
#include <map>

std::string_view filters[]{
    ".stmod$",
};

static AppInfo_s appInfo{
    .header = ExtractCache_DESC " v" ExtractCache_VERSION
                                ", " ExtractCache_COPYRIGHT "Lukas Cone",
    .filters = filters,
};

AppInfo_s *AppInitModule() { return &appInfo; }

static std::map<stcache::CacheFileType, const char *> EXTENSIONS{
    {stcache::CacheFileType::Avi, "avi"},
    {stcache::CacheFileType::Dds, "dds"},
    {stcache::CacheFileType::GameInfo, "gameinfo"},
    {stcache::CacheFileType::Level, "level"},
    {stcache::CacheFileType::Ogg, "ogg"},
    {stcache::CacheFileType::Sba, "sba"},
    {stcache::CacheFileType::Sbm, "sbm"},
    {stcache::CacheFileType::Sbt, "sbt"},
    {stcache::CacheFileType::ShaderFragment, "psh"},
    {stcache::CacheFileType::ShaderHlsl, "hlsl"},
    {stcache::CacheFileType::ShaderVertex, "vsh"},
    {stcache::CacheFileType::Tga, "tga"},
    {stcache::CacheFileType::Wav, "wav"},
    {stcache::CacheFileType::UnknownBinaryResource, "bin"},
    {stcache::CacheFileType::UnknownTextResource, "txt"},
    {stcache::CacheFileType::UnknownUncachedBinaryResource, "bin"},
    {stcache::CacheFileType::Instances, "instances"},
    {stcache::CacheFileType::InstancesStatic, "instancesstatic"},
    {stcache::CacheFileType::Resources, "resources"},
};

void AppProcessFile(AppContext *ctx) {
  std::string buffer_ = ctx->GetBuffer();
  stcache::Cache *cache = reinterpret_cast<stcache::Cache *>(buffer_.data());
  auto rStream = ctx->RequestFile(ctx->workingFile.ChangeExtension2("dat"));
  stcache::AddCachePair(cache, rStream.Get());

  auto *ectx = ctx->ExtractContext();
  std::string buffer;

  for (auto &f : cache->files) {
    char fileName[0x40]{};
    auto fileType = f.fileType;
    snprintf(fileName, sizeof(fileName), "%X.%s", f.nameHash,
             EXTENSIONS.at(fileType));
    ectx->NewFile(fileName);
    buffer.resize(stcache::FileSize(f));
    stcache::GetFileData(f, buffer.data(), 0, buffer.size());

    ectx->SendData(buffer);
  }
}
