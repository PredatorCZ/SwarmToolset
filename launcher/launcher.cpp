/*  ModStgame
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

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <windows.h>

#include "detours.h"

int main(int argc, char *argv[]) {
  STARTUPINFOA startInfo{};
  startInfo.cb = sizeof(startInfo);
  PROCESS_INFORMATION processInfo{};
  SetLastError(0);
  std::string args("/c");

  for (int a = 1; a < argc; a++) {
    args.push_back(' ');
    args.append(argv[a]);
  }

  if (!DetourCreateProcessWithDllA(
          "stgame.exe",
          const_cast<char *>(args.c_str()),             // args
          NULL,                                         // lpProcessAttributes,
          NULL,                                         // lpThreadAttributes,
          TRUE,                                         // bInheritHandles,
          CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED, // dwCreationFlags,
          NULL,                                         // lpEnvironment,
          NULL, //"/media/data/Games/Starship Troopers/",       // lpCurrentDirectory,
          &startInfo,                                   //
          &processInfo,
          "libstmod.dll",
          NULL // pfCreateProcessW
          )) {
    LPSTR lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                       FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   lpMsgBuf, 0, NULL);

    printf("mod_stgame.exe: DetourCreateProcessWithDll failed: %s\n", lpMsgBuf);
    LocalFree(lpMsgBuf);
    ExitProcess(9009);
  }

  ResumeThread(processInfo.hThread);

  WaitForSingleObject(processInfo.hProcess, INFINITE);

  CloseHandle(processInfo.hProcess);
  CloseHandle(processInfo.hThread);

  DWORD dwResult = 0;
  if (!GetExitCodeProcess(processInfo.hProcess, &dwResult)) {
    printf("mod_stgame.exe: GetExitCodeProcess failed: %ld\n", GetLastError());
    return 9010;
  }
  return 0;
}
