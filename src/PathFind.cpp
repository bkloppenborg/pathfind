/*
 * PathFinding.cpp
 *
 *  Created on: Oct. 25, 2011
 *      Author: bkloppenborg
 */

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

#include "PathFind.hpp"

/// Find the path of the current executable using GetModuleFileNameW (Windows)
string do_GetModuleFileNameW()
{
#if defined (WIN32) // Windows
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);
#else
	string path = "";
#endif

	return string(path);
}

/// Find the path of the current executable using _NSGetExecutablePath (Apple/Mac)
string do_NSGetExecutablePath()
{
#if defined (__APPLE__) || defined(MACOSX)	// Apple / OSX
	char path[1024];
	uint32_t size = sizeof(path);
	if (_NSGetExecutablePath(path, &size) == 0)
	    printf("executable path is %s\n", path);
	else
	    printf("buffer too small; need size %u\n", size);
#else
	string path = "";
#endif

	return string(path);
}

/// Find the path of the current executable using do_readlink (BSD, Solaris, Linux)
string do_readlink(std::string const& path)
{
    char buff[1024];
#if defined (BSD) || defined(__gnu_linux__) || defined(sun) || defined(__sun)	 // BSD, Linux, Solaris
    ssize_t len = ::readlink(path.c_str(), buff, sizeof(buff)-1);
#endif

    return string(buff);
}

string FindExecutable()
{
	string path;

#if defined (__APPLE__) || defined(MACOSX)	// Apple / OSX
	path = do_NSGetExecutablePath();
#elif defined (WIN32) // Windows
	path = do_GetModuleFileNameW();
#elif defined (BSD) // BSD variants
	path = do_readlink("/proc/curproc/file");
#elif defined (sun) || defined(__sun) // Solaris
	path = do_readlink("/proc/self/path/a.out");
#elif defined (__gnu_linux__)	// Linux
	path = do_readlink("/proc/self/exe");
#endif

	return path;
}
