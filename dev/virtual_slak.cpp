/*  VirtualSlak
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
#include "spike/io/directory_scanner.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/io/stat.hpp"
#include "stcache.hpp"
#include <fstream>
#include <memory>

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

  std::string virtualSlak = stcache::MakeVirtualSlak();
  std::string compath(argv[1]);
  compath.append("/common.slak");

  std::ofstream str(compath);
  str.write(virtualSlak.data(), virtualSlak.size());
}
