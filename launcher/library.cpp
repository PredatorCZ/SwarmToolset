/*  LibModStgame
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

#define NOMINMAX
#include <stdio.h>
#include <windows.h>

#include "detours.h"
#include "stcache.hpp"

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <vector>

struct CacheHandle {
  HANDLE handle;
  const stcache::CacheFile *file = nullptr; // Yay let's segfault everything :)
  size_t virtualPosition = 0;
  size_t size;
};

static HANDLE virtualSlakHandle = 0;
static std::string virtualSlak;
static size_t virtualPosition = 0;
static HANDLE searchHandle = 0;
static HANDLE cacheHandle = 0;
static std::string workDir;
static std::vector<CacheHandle> openedCacheHandles;
static FILETIME cacheFiletime;
static stcache::ScriptIterator globalResources{};
static HANDLE globalResourcesHandle = INVALID_HANDLE_VALUE;
static stcache::ScriptIterator globalInstances{};
static HANDLE globalInstancesHandle = INVALID_HANDLE_VALUE;

decltype(openedCacheHandles)::iterator FindHandle(HANDLE handle) {
  for (auto it = openedCacheHandles.begin(); it != openedCacheHandles.end();
       it++) {
    if (it->handle == handle) {
      return it;
    }
  }

  return openedCacheHandles.end();
}

#pragma region Read File
///////////////////////////////
//---------READ FILE---------//
///////////////////////////////

static WINBOOL(WINAPI *OldReadFile)(HANDLE hFile, LPVOID lpBuffer,
                                    DWORD nNumberOfBytesToRead,
                                    LPDWORD lpNumberOfBytesRead,
                                    LPOVERLAPPED lpOverlapped) = ReadFile;

WINBOOL WINAPI NewReadFile(HANDLE hFile, LPVOID lpBuffer,
                           DWORD nNumberOfBytesToRead,
                           LPDWORD lpNumberOfBytesRead,
                           LPOVERLAPPED lpOverlapped) {
  if (hFile == virtualSlakHandle) {
    CopyMemory(lpBuffer, virtualSlak.data() + virtualPosition,
               nNumberOfBytesToRead);
    *lpNumberOfBytesRead = nNumberOfBytesToRead;
    virtualPosition += nNumberOfBytesToRead;

    return TRUE;
  } else if (auto found = FindHandle(hFile);
             found != openedCacheHandles.end()) {
    const size_t toRead = std::min(found->size, size_t(found->virtualPosition +
                                                       nNumberOfBytesToRead)) -
                          found->virtualPosition;
    stcache::GetFileData(*found->file, static_cast<char *>(lpBuffer),
                         found->virtualPosition, toRead);
    *lpNumberOfBytesRead = toRead;
    found->virtualPosition += toRead;
    return TRUE;
  }

  return OldReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead,
                     lpOverlapped);
}

#pragma endregion

#pragma region Close Handle
//////////////////////////////////
//---------CLOSE HANDLE---------//
//////////////////////////////////

static WINBOOL(WINAPI *OldCloseHandle)(HANDLE hFile) = CloseHandle;

WINBOOL WINAPI NewCloseHandle(HANDLE hFile) {
  if (hFile == virtualSlakHandle) {
    virtualPosition = 0;
    virtualSlakHandle = 0;
  } else if (auto found = FindHandle(hFile);
             found != openedCacheHandles.end()) {
    OldCloseHandle(found->handle);
    openedCacheHandles.erase(found);
    return TRUE;
  }
  return OldCloseHandle(hFile);
}

static WINBOOL(WINAPI *OldFindClose)(HANDLE) = FindClose;

WINBOOL WINAPI NewFindClose(HANDLE hFindFile) {
  if (hFindFile == searchHandle) {
    return TRUE;
  } else if (hFindFile == globalResourcesHandle) {
    globalResourcesHandle = INVALID_HANDLE_VALUE;
  } else if (hFindFile == globalInstancesHandle) {
    globalInstancesHandle = INVALID_HANDLE_VALUE;
  }

  return OldFindClose(hFindFile);
}

#pragma endregion

#pragma region Search File
/////////////////////////////////
//---------SEARCH FILE---------//
/////////////////////////////////

WINBOOL NextGlobalResource(LPWIN32_FIND_DATAA lpFindFileData) {
  std::string_view curItem = globalResources.Next();

  if (curItem.empty()) {
    return FALSE;
  }

  std::string fullFileName("st/globals/scripts/");
  fullFileName.append(curItem);
  fullFileName.append(".resources");

  *lpFindFileData = {};
  CopyMemory(lpFindFileData->cFileName, curItem.data(), curItem.size());
  CopyMemory(lpFindFileData->cFileName + curItem.size(), ".resources", 10);

  return TRUE;
}

WINBOOL NextGlobalInstance(LPWIN32_FIND_DATAA lpFindFileData) {
  std::string_view curItem = globalInstances.Next();

  if (curItem.empty()) {
    return FALSE;
  }

  std::string fullFileName("st/globals/scripts/");
  fullFileName.append(curItem);
  fullFileName.append(".instances");

  *lpFindFileData = {};
  CopyMemory(lpFindFileData->cFileName, curItem.data(), curItem.size());
  CopyMemory(lpFindFileData->cFileName + curItem.size(), ".instances", 10);

  return TRUE;
}

HANDLE(WINAPI *OldFindFirstFileA)
(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) = FindFirstFileA;

HANDLE WINAPI NewFindFirstFileA(LPCSTR lpFileName,
                                LPWIN32_FIND_DATAA lpFindFileData) {
  std::string_view fileView(lpFileName);
  std::string normFileName(lpFileName);
  std::transform(normFileName.begin(), normFileName.end(), normFileName.begin(),
                 [](char c) -> char {
                   if (c == '\\') {
                     return '/';
                   }

                   return std::tolower(c);
                 });

  if (normFileName.ends_with(".slak")) {
    return INVALID_HANDLE_VALUE;
  }

  if (normFileName.starts_with(workDir)) {
    normFileName.erase(0, workDir.size() + 1);
    //printf("Find CWD file: %s\n", normFileName.c_str());

    if (size_t foundWC = normFileName.find_last_of('*');
        foundWC != std::string::npos) {

      if (normFileName == "st/globals/scripts/*.instances") {
        globalInstances = stcache::GlobalInstancesIterator();
        DuplicateHandle(GetCurrentProcess(), searchHandle, GetCurrentProcess(),
                        &globalInstancesHandle, 0, FALSE,
                        DUPLICATE_SAME_ACCESS);
        NextGlobalInstance(lpFindFileData);
        return globalInstancesHandle;
      } else if (normFileName == "st/globals/scripts/*.resources") {
        globalResources = stcache::GlobalResourcesIterator();
        DuplicateHandle(GetCurrentProcess(), searchHandle, GetCurrentProcess(),
                        &globalResourcesHandle, 0, FALSE,
                        DUPLICATE_SAME_ACCESS);
        NextGlobalResource(lpFindFileData);
        return globalResourcesHandle;
      }

      normFileName.erase(foundWC - 1, 2);
    }

    try {
      auto currentCacheFile = stcache::GetFile(normFileName);

      if (currentCacheFile) {
        *lpFindFileData = {};
        strcpy(lpFindFileData->cFileName,
               fileView.data() + fileView.find_last_of('\\') + 1);
        lpFindFileData->nFileSizeLow = stcache::FileSize(*currentCacheFile);
        lpFindFileData->ftLastWriteTime = cacheFiletime;

        //printf("Found cached file: %s\n", lpFindFileData->cFileName);

        return searchHandle;
      }
    } catch (const std::runtime_error &) {
    }
  } else {
    printf("Find NWD file: %s\n", normFileName.c_str());
  }

  return OldFindFirstFileA(lpFileName, lpFindFileData);
}

static WINBOOL(WINAPI *OldFindNextFileA)(
    HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) = FindNextFileA;

WINBOOL WINAPI NewFindNextFileA(HANDLE hFindFile,
                                LPWIN32_FIND_DATAA lpFindFileData) {
  if (hFindFile == searchHandle) {
    // printf("Found next file\n");
    return FALSE;
  } else if (hFindFile == globalResourcesHandle) {
    return NextGlobalResource(lpFindFileData);
  } else if (hFindFile == globalInstancesHandle) {
    return NextGlobalInstance(lpFindFileData);
  }

  return OldFindNextFileA(hFindFile, lpFindFileData);
}

#pragma endregion

#pragma region Seek File
///////////////////////////////
//---------SEEK FILE---------//
///////////////////////////////

static DWORD(WINAPI *OldSetFilePointer)(HANDLE hFile, LONG liDistanceToMove,
                                        PLONG lpDistanceToMoveHigh,
                                        DWORD dwMoveMethod) = SetFilePointer;

DWORD WINAPI NewSetFilePointer(HANDLE hFile, LONG liDistanceToMove,
                               PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod) {
  if (hFile == virtualSlakHandle) {
    virtualPosition = liDistanceToMove;
  } else if (auto found = FindHandle(hFile);
             found != openedCacheHandles.end()) {
    switch (dwMoveMethod) {
    case FILE_BEGIN:
      found->virtualPosition = liDistanceToMove;
      break;

    case FILE_CURRENT:
      found->virtualPosition += liDistanceToMove;
      break;

    case FILE_END:
      found->virtualPosition = found->size - liDistanceToMove;
      break;

    default:
      break;
    }

    // printf("SEEK [%X] %u %u %u\n", GetCurrentThread(), liDistanceToMove,
    //        lpDistanceToMoveHigh, dwMoveMethod);
    return found->virtualPosition;
  }
  return OldSetFilePointer(hFile, liDistanceToMove, lpDistanceToMoveHigh,
                           dwMoveMethod);
}

#pragma endregion

#pragma region Create File
/////////////////////////////////
//---------CREATE FILE---------//
/////////////////////////////////

static HANDLE(WINAPI *OldCreateFileW)(
    LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) = CreateFileW;

HANDLE WINAPI NewCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess,
                             DWORD dwShareMode,
                             LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                             DWORD dwCreationDisposition,
                             DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
  wprintf(L"WIDE: Attempt to access file: %ls\n", lpFileName);
  return OldCreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
                        lpSecurityAttributes, dwCreationDisposition,
                        dwFlagsAndAttributes, hTemplateFile);
}

static HANDLE(WINAPI *OldCreateFileA)(
    LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) = CreateFileA;

HANDLE WINAPI NewCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess,
                             DWORD dwShareMode,
                             LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                             DWORD dwCreationDisposition,
                             DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
  if (std::string_view fileNameView(lpFileName);
      fileNameView.ends_with(".slak")) {
    if (fileNameView.ends_with("Common.slak")) {
      DuplicateHandle(GetCurrentProcess(), cacheHandle, GetCurrentProcess(),
                      &virtualSlakHandle, 0, FALSE, DUPLICATE_SAME_ACCESS);
      return virtualSlakHandle;
    }

    return INVALID_HANDLE_VALUE;
  }

  std::string normFileName(lpFileName);
  std::transform(normFileName.begin(), normFileName.end(), normFileName.begin(),
                 [](char c) -> char {
                   if (c == '\\') {
                     return '/';
                   }

                   return std::tolower(c);
                 });

  if (normFileName.starts_with(workDir)) {
    normFileName.erase(0, workDir.size() + 1);
    if (size_t foundWC = normFileName.find_last_of('*');
        foundWC != std::string::npos) {
      normFileName.erase(foundWC - 1, 2);
    }

    //printf("Accessing CWD file: %s\n", normFileName.c_str());

    auto currentCacheFile = stcache::GetFile(normFileName);

    if (currentCacheFile) {
      HANDLE newHandle;
      DuplicateHandle(GetCurrentProcess(), cacheHandle, GetCurrentProcess(),
                      &newHandle, 0, FALSE, DUPLICATE_SAME_ACCESS);
      //printf("Cached file: %s\n", normFileName.c_str());
      openedCacheHandles.emplace_back(CacheHandle{
          .handle = newHandle,
          .file = currentCacheFile,
          .size = stcache::FileSize(*currentCacheFile),
      });

      return newHandle;
    } else {
      printf("Accessing NWD file: %s\n", normFileName.c_str());
    }
  }

  return OldCreateFileA(lpFileName, dwDesiredAccess, dwShareMode,
                        lpSecurityAttributes, dwCreationDisposition,
                        dwFlagsAndAttributes, hTemplateFile);
}

#pragma endregion

struct MappedFile {
  HANDLE mapping;
  HANDLE fileHandle;
  void *data;

  MappedFile(const wchar_t *path) {
    fileHandle = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
      throw std::runtime_error("Cannot open mod file");
    }

    mapping = CreateFileMapping(fileHandle, NULL, PAGE_WRITECOPY, 0, 0, NULL);

    if (!mapping) {
      auto errCode = GetLastError();
      throw std::runtime_error("Cannot open mod file mapping " +
                               std::to_string(errCode));
    }

    data = MapViewOfFileEx(mapping, FILE_MAP_COPY, 0, 0, 0, NULL);
    CloseHandle(mapping);

    if (!data) {
      auto errCode = GetLastError();
      throw std::runtime_error("Cannot open mod file view " +
                               std::to_string(errCode));
    }

    if (cacheHandle == 0) {
      cacheHandle = fileHandle;
      GetFileTime(fileHandle, NULL, NULL, &cacheFiletime);
    }
  }
};

wchar_t *Changepath(wchar_t *path) {
  wcscpy(path + wcslen(path) - 5, L"dat");
  return path;
}

struct MappedMod {
  MappedFile cache;
  std::unique_ptr<std::ifstream> stream;

  MappedMod(wchar_t *path)
      : cache(path), stream(std::make_unique<std::ifstream>(Changepath(path),
                                                            std::ios::binary)) {
    stcache::AddCachePair(static_cast<stcache::Cache *>(cache.data),
                          stream.get());
  }
};

static std::vector<MappedMod> mappedMods;

void LoadCacheFolder() {
  wchar_t absPath[MAX_PATH]{};
  GetFullPathName(L"mods/*.stmod", MAX_PATH, absPath, NULL);
  char workDirC[MAX_PATH]{};
  GetFullPathNameA(".", MAX_PATH, workDirC, NULL);
  workDir = workDirC;
  std::transform(workDir.begin(), workDir.end(), workDir.begin(),
                 [](char c) -> char {
                   if (c == '\\') {
                     return '/';
                   }

                   return std::tolower(c);
                 });

  WIN32_FIND_DATA foundData = {};
  searchHandle = FindFirstFile(absPath, &foundData);

  if (searchHandle == INVALID_HANDLE_VALUE) {
    return;
  }

  do {
    if ((foundData.dwFileAttributes & FILE_ATTRIBUTE_DEVICE) != 0) {
      continue;
    }

    wchar_t absPathMod[MAX_PATH]{};
    GetFullPathName(L"mods/", MAX_PATH, absPathMod, NULL);
    wcscat(absPathMod, foundData.cFileName);

    printf("Found mod: %ls\n", absPathMod);
    mappedMods.emplace_back(absPathMod);
  } while (FindNextFile(searchHandle, &foundData));

  // FindClose(fleHandle);
  stcache::PatchCache();

  virtualSlak = stcache::MakeVirtualSlak();
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {
  (void)hinst;
  (void)reserved;

  if (DetourIsHelperProcess()) {
    return TRUE;
  }

  if (dwReason == DLL_PROCESS_ATTACH) {
    DetourRestoreAfterWith();
    printf("libstmod.dll: Starting.\n");
    fflush(stdout);
    LoadCacheFolder();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&OldCreateFileA, NewCreateFileA);
    DetourAttach(&OldCreateFileW, NewCreateFileW);
    DetourAttach(&OldReadFile, NewReadFile);
    DetourAttach(&OldCloseHandle, NewCloseHandle);
    DetourAttach(&OldSetFilePointer, NewSetFilePointer);
    DetourAttach(&OldFindFirstFileA, NewFindFirstFileA);
    DetourAttach(&OldFindClose, NewFindClose);
    DetourAttach(&OldFindNextFileA, NewFindNextFileA);

    LONG error = DetourTransactionCommit();

    if (error != NO_ERROR) {
      throw std::runtime_error("Failed to attach function");
    }
  } else if (dwReason == DLL_PROCESS_DETACH) {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&OldCreateFileA, NewCreateFileA);
    DetourDetach(&OldCreateFileW, NewCreateFileW);
    DetourDetach(&OldReadFile, NewReadFile);
    DetourDetach(&OldCloseHandle, NewCloseHandle);
    DetourDetach(&OldSetFilePointer, NewSetFilePointer);
    DetourDetach(&OldFindFirstFileA, NewFindFirstFileA);
    DetourDetach(&OldFindClose, NewFindClose);
    DetourDetach(&OldFindNextFileA, NewFindNextFileA);
    DetourTransactionCommit();
  }

  return TRUE;
}
