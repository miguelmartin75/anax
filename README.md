# anax 1.0

anax, the open source C++ entity system is designed to be a portable, lightweight and an easy to use library for Game Development. Although it is thought that [Entity Systems] are used for MMOGs, it can be in fact used for just about any [video game genre].

## Author

- Miguel Martin - <miguel.martin7.5@hotmail.com>

## License
Copyright (C) 2013 Miguel Martin. All rights reserved.

This software is provided 'as-is', without any express or implied warranty. 
In no event will the authors be held liable for any damages arising from the 
use of this software.

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished 
to do so, subject to the following conditions:

1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment
   in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.

3. The above copyright notice and this permission notice shall be included in 
   all copies or substantial portions of the Software.

## Inspiration

This entity system is originally inspired from the Java Framework, [Artemis], which provides an Entity System for the Java programming language. Further inspiration was recieved from [entityx](https://github.com/alecthomas/entityx). Although those two frameworks are good, I felt it was necessary to alter and change them to my liking, mainly for performance reasons and just the right "feel".

## Dependices

To compile, install, and use anax, the following libraries and C++11 support are required:

 - The following [boost](http://boost.org/) libraries:
	- [boost::dynamic_bitset](http://www.boost.org/doc/libs/1_52_0/libs/dynamic_bitset/dynamic_bitset.html)
- C++11 smart pointers (``std::shared_pointer``, ``std::unique_ptr``)

## Getting Started

### Downloading the Library

There are multiple ways to download the library. You can either [clone](github-mac://openRepo/https://github.com/miguelishawt/anax) the library, or download a tarball ([zip](https://api.github.com/repos/miguelishawt/anax/zipball)/[tar-gz](https://api.github.com/repos/miguelishawt/anax/tarball)).

### Installation

Unfortunately, at this time, this library does _not_ use [CMake](http://www.cmake.org/), since I currently do not know how to use it. Therefore you currently have these options:

1. Build the project with your own method (i.e. makefile, project files)
2. Include the source files (under the `include/` and `src/` directories) into your project

Either of these methods should work. Please note for the second method, you must have a search path to the `include/` directory.

### **NOTES**
> 
> 1. It is worth mentioning that I do have an Xcode project (since I develop with a Mac) within the repo at this current time of Version 0.2, you could use that. However I must mention that build settings may not work. If it doesn't check the build settings and look at the include/library search file paths settings, and change them to the directory in which boost library is located on your machine.
> 2. I __will__ add support for CMake, or an alternative automatic building system for this library

### Using the library

It is assumed that you know what an entity-system/entity-component-system. If you don't know what one is, I reccomend reading [this]().

 


#### Entities


#### World


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