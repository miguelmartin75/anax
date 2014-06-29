///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///

#ifndef ANAX_HPP
#define ANAX_HPP

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
#define ANAX_VERSION_MINOR 1
#define ANAX_PATCH_NUMBER 1

#define ANAX_VERSION_NUMBER ANAX_VERSION_MAJOR.ANAX_VERSION_MINOR.ANAX_PATCH_NUMBER

#include <anax/World.hpp>

#endif // ANAX_HPP
