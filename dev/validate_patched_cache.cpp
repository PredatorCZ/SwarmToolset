/*  ValidatePatchedCache
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

#include "spike/except.hpp"
#include "spike/io/directory_scanner.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/io/stat.hpp"
#include "stcache_internal.hpp"
#include <fstream>
#include <map>
#include <memory>

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

std::vector<es::MappedFile> files;
std::vector<std::unique_ptr<std::ifstream>> streams;

void LoadCacheFolder(std::string_view folder) {
  DirectoryScanner sc;
  sc.AddFilter(std::string_view(".stmod"));
  sc.Scan(std::string(folder));

  for (auto &f : sc) {
    stcache::Cache *c =
        static_cast<stcache::Cache *>(files.emplace_back(f).data);
    auto *d = streams
                  .emplace_back(std::make_unique<std::ifstream>(
                      AFileInfo(f).ChangeExtension2("dat")))
                  .get();
    AddCachePair(c, d);
  }

  stcache::PatchCache();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    throw std::runtime_error("Expected path");
  }

  LoadCacheFolder(argv[1]);

  {
    std::ofstream str("dump", std::ios_base::binary);
    str.write(static_cast<const char *>(files.front().data), 384160);
  }

  stcache::Cache *cache = static_cast<stcache::Cache *>(files.front().data);

  std::string buffer;

  for (auto &f : cache->files) {
    buffer.resize(stcache::FileSize(f));
    stcache::GetFileData(f, buffer.data(), 0, buffer.size());
  }
}
