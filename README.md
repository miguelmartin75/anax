# anax v1.0

anax, the open source C++ entity system is designed to be a portable, lightweight and an easy to use library for Game Development. Although it is thought that [Entity Systems] are used for MMOGs, it can be in fact used for just about any [video game genre].

## Disclaimer
This software is provided 'as-is', without any express or implied warranty. 
In no event will the authors be held liable for any damages arising from the 
use of this software.

## License
Please see [LICENCE.txt](LICENCE.txt)

## Inspiration

This entity system is originally inspired from the Java Framework, [Artemis], which provides an Entity System for the Java programming language.

## Dependices

To compile, install, and use anax, the following libraries and C++11 support are required:

 - The following [boost](http://boost.org/) libraries:
	- [boost::dynamic_bitset](http://www.boost.org/doc/libs/1_52_0/libs/dynamic_bitset/dynamic_bitset.html)
- C++11 smart pointers (``std::shared_pointer``, ``std::unique_ptr``)

## Installation

Unfortunately, at this time, this library does _not_ use [CMake](http://www.cmake.org/), since I currently do not know how to use it. Therefore you currently have these options:

1. Build the project with your own method (i.e. makefile, project files)
2. Include the source files (under the `include/` and `src/` directories) into your project

Either of these methods should work. Please note for the second method, you must have a search path to the `include/` directory.

### **NOTE**
> 
> It is worth mentioning that I do have an Xcode project (since I develop with a Mac) within the repo at this current time of Version 0.2, you could use that. However I must mention that build settings may not work. If it doesn't check the build settings and look at the include/library search file paths settings, and change them to the directory in which boost library is located on your machine.

## Getting Started Guide

TODO

## Get Involved

Want to get involved with the project? You are free to help out on the project, here are the possible methods to help out:

- The Code
	- Implement requested features
	- Implement new features
    - Optimise code
    - Fix bugs
    - Help create/fix documentation
- The [wiki]
	- Create video/written tutorials (be add any links to the [wiki], or write it up on the wiki)
    - Fix spelling/grammar errors
	- Add examples to the [examples] repo

If you do help out, [email] me and I'll put your name in the contributers file.

[email]: mailto:miguel.martin7.5@hotmail.com
[wiki]: https://github.com/miguelishawt/anax/wiki
[website-install]: https://github.com/miguelishawt/anax/wiki/install.md
[examples]: https://github.com/miguelishawt/anax-examples
[logo]: doc/logo.png
[Entity Systems]:http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/)
[video game genre]:(http://en.wikipedia.org/wiki/Video_game_genres)
[Artemis]: http://gamadu.com/artemis/