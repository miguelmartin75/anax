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

#ifndef __ANAX_COMPONENT_H__
#define __ANAX_COMPONENT_H__

#include <cstddef>

#include "detail/ClassTypeId.hpp"

namespace anax
{
	class BaseComponent
	{
	public:
	
		typedef std::size_t TypeId;

#	ifdef ANAX_COMPONENT_VIRTUAL_DESTRUCTORS
		virtual ~BaseComponent() = 0;
#	endif // ANAX_COMPONENT_VIRTUAL_DESTRUCTORS
	};
	
	template <typename T>
	class Component
		: BaseComponent
	{
	public:
		
#	ifdef ANAX_COMPONENT_VIRTUAL_DESTRUCTORS
		virtual ~Component() = 0;
#	endif // ANAX_COMPONENT_VIRTUAL_DESTRUCTORS
		
		static TypeId GetTypeId()
		{
			return detail::ClassTypeId<BaseComponent>::GetTypeId<T>();
		}
	};
	
#ifdef ANAX_COMPONENT_VIRTUAL_DESTRUCTORS
	template <typename T>
	Component<T>::~Component()
	{
	}
#endif // ANAX_COMPONENT_VIRTUAL_DESTRUCTORS
}

#endif // __ANAX_COMPONENT_H__
