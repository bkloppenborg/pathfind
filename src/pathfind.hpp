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

#if defined (__APPLE__) || defined(MACOSX)	// Apple
#include <mach-o/dyld.h>
#elif defined (WIN32) // Windows
#include <windows.h>
#elif defined (BSD) || defined(__gnu_linux__) || defined(__linux__) || defined(sun) || defined(__sun)	 // BSD, Linux, Solaris
#include <unistd.h>
#endif

#include <string>

namespace PathFind {

  /// Windows only: Find the path of the current executable using
  /// GetModuleFileNameW
  /// \param max_path Maximum length of path to accept.
  std::string do_GetModuleFileNameW(int max_path = 1024);


  /// Apple/Mac only: Find the path of the current executable using
  /// _NSGetExecutablePath
  /// \param max_path Maximum length of path to accept.
  std::string do_NSGetExecutablePath(int max_path = 1024);

  /// Linux, Solaris, FreeBSD (if it has procfs) only: Find the path of the
  /// current executable using do_readlink
  /// \param max_path Maximum length of path to accept.
  std::string do_readlink(std::string const& path, int max_path = 1024);

  /// Find the path to the current executable regardless of operating system
  /// \param max_path Maximum length of path to accept.
  /// \return Path to the current executable
  std::string FindExecutable(int max_path = 1024);

}; // namespace PathFind
