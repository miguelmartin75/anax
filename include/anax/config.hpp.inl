///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
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

#ifndef __ANAX_CONFIG_HPP__
#define __ANAX_CONFIG_HPP__

#cmakedefine ANAX_32_BIT_ENTITY_IDS @ANAX_32_BIT_ENTITY_IDS@
#cmakedefine ANAX_VIRTUAL_DTORS_IN_COMPONENT @ANAX_VIRTUAL_DTORS_IN_COMPONENT@
#cmakedefine ANAX_USE_VARIADIC_TEMPLATES @ANAX_VARIADIC_TEMPLATES@

#ifdef ANAX_32_BIT_ENTITY_IDS
#	define ANAX_ENTITY_ID_INDEX_BIT_COUNT 20
#	define ANAX_ENTITY_ID_COUNTER_BIT_COUNT 12
#else
#	define ANAX_ENTITY_ID_INDEX_BIT_COUNT 48
#	define ANAX_ENTITY_ID_COUNTER_BIT_COUNT 16
#endif

#endif // __ANAX_CONFIG_HPP__
