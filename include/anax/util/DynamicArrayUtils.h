///
/// anax
/// Copyright (C) 2012-2013 Anax Creations. All rights reserved.
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

#ifndef __ANAX_UTIL_DYNAMICARRAYUTILS_H__
#define __ANAX_UTIL_DYNAMICARRAYUTILS_H__

namespace anax
{
	namespace util
	{
		template <class T>
		void AssignVectorIndexWithAutoResize(T& vector, typename T::size_type index, typename T::value_type value)
		{
			// if we need to resize
			if(vector.size() <= index)
			{
				// then we shall resize!
				vector.resize(index + 1);
			}
			
			// assign the requested element
			vector[index] = value;
		}
		
		template <class T>
		void EnsureCapacity(T& vector, typename T::size_type index)
		{
			// if we need to resize
			if(vector.size() <= index)
			{
				// then we shall resize!
				vector.resize(index + 1);
			}
		}
		
		template <class T>
		typename T::value_type GetFromIndexWithAutoResize(T& vector, typename T::size_type index)
		{
			EnsureCapacity(vector, index);
			return vector[index];
		}
		
		template <class T>
		bool GetFromIndexWithAutoResizeBitset(T& bitset, typename T::size_type index)
		{
			EnsureCapacity(bitset, index);
			return bitset[index];
		}
		
		template <class T>
		void AssignBitsetIndexWithAutoResize(T& bitset, typename T::size_type index, bool value)
		{
			// if we need to resize
			EnsureCapacity(bitset, index);
			// assign the requested element
			bitset[index] = value;
		}
	}
}

#endif // __ANAX_UTIL_DYNAMICARRAYUTILS_H__