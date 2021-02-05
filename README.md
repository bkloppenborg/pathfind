PathFind
===========

A C++ library for finding the path to the current executable on Windows,
Apple/OSX, and Linux. Licensed under LGPL-V3.

Build and install instructions:

```
cd build
cmake ..
make
make install
```

Example usage:

```
#include <iostream>
#include <pathfind.hpp>

int main()
{
	std::cout << PathFind::FindExecutable() << std::endl;
	return 0;
}
```
