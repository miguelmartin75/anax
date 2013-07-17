///
/// anax
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
///
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is hereby granted, free of charge, to any person
/// obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// 1. The origin of this software must not be misrepresented;
///    you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment
///    in the product documentation would be appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such,
///	   and must not be misrepresented as being the original software.
///
/// 3. The above copyright notice and this permission notice shall be included in
///    all copies or substantial portions of the Software.
///

#ifndef __ANAX_HPP__
#define __ANAX_HPP__

/// \brief A namespace that contains all classes/functions for the anax library
///
/// This namespace contains all you need to use the anax library.
///
/// \author Miguel Martin
namespace anax
{
}


/// \mainpage
///
/// \section welcome Welcome
///
/// Welcome to the anax documentation, here you may find
/// detailed documentation on how to use specific classes/methods for the library.
///
/// \section resources Extra-resources
/// You may find more resources to learn about the anax library on
/// the anax's wiki, hosted on GitHub
/// <a href="https://github.com/miguelishawt/anax/wiki"> here</a>.

#define ANAX_VERSION_MAJOR 1
#define ANAX_VERSION_MINOR 0
#define ANAX_PATCH_NUMBER 0

#define ANAX_VERSION_NUMBER ANAX_VERSION_MAJOR.ANAX_VERSION_MINOR.ANAX_PATCH_NUMBER

#include "World.hpp"

#endif // __ANAX_HPP__