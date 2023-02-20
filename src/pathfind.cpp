/*
 * Copyright (c) 2012 Brian Kloppenborg
 *
 * This file is part of the Path Finding Library (PathFind).
 *
 *  PathFind is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  PathFind is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with LIBOI.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pathfind.hpp"

#include <cassert>
#include <cstring>

std::string PathFind::do_GetModuleFileNameW(int max_path)
{
  std::string ret;

#if defined (WIN32) // Windows
  TCHAR buff[MAX_PATH]{};
  HMODULE hModule = GetModuleHandle(NULL);
  GetModuleFileNameA(hModule, buff, max_path);

  ret = buff;
#endif

  return ret;
}

std::string PathFind::do_NSGetExecutablePath(int max_path)
{
  std::string ret;

#if defined(__APPLE__) || defined(MACOSX) // Apple / OSX
  char* buff = new char[max_path + 1];
  memset(buff, '\0', max_path + 1);

  uint32_t max_path_ = max_path;
  assert(static_cast<int>(max_path_) == max_path && "max_path is not representable");
  _NSGetExecutablePath(buff, &max_path_);

  ret = std::move(std::string(buff));
  delete[] buff;
#endif

  return ret;
}

std::string PathFind::do_readlink(std::string const& path, int max_path)
{
  // allocate a buffer in which to store the path.
  std::string ret;

#if defined(BSD) || defined(__gnu_linux__) || defined(__linux__) || defined(sun) || defined(__sun)
  char* buff = new char[max_path + 1];
  memset(buff, '\0', max_path + 1);

  size_t len = ::readlink(path.c_str(), buff, max_path);

  ret = std::move(std::string(buff));
  delete[] buff;
#endif

  return ret;
}

/// Find the path to the current executable
std::string PathFind::FindExecutable(int max_path)
{
  std::string path;

  // OS-specific calls to find the path to the current executable.
#if defined (__APPLE__) || defined(MACOSX)  // Apple / OSX
  path = PathFind::do_NSGetExecutablePath(max_path);
#elif defined (WIN32) // Windows
  path = PathFind::do_GetModuleFileNameW(max_path);
#elif defined (BSD) // BSD variants
  path = PathFind::do_readlink("/proc/curproc/file", max_path);
#elif defined (sun) || defined(__sun) // Solaris
  path = PathFind::do_readlink("/proc/self/path/a.out", max_path);
#elif defined (__gnu_linux__)  || defined (__linux__)// Linux
  path = PathFind::do_readlink("/proc/self/exe", max_path);
#endif

  return path;
}
