///
/// anax
/// Copyright (C) 2013 Anax Creations. All rights reserved.
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

#include "anax/Identifiable.h"
#include "anax/ObjectCreator.h"

namespace anax
{
	/// \class Component
	/// \brief An abstract class that defines a Component
	///
	/// This class is a component, which is used to wrap data
	/// with, in order to
	///
	/// \author Miguel Martin
	class BaseComponent
	{
		ANAX_IDENTIFIABLE_BASE(BaseComponent) // TODO: remove
		
	public:
		
		/// Pure virtual destructor
		virtual ~BaseComponent() = 0;
	};
	
	/// Used for readability
	typedef BaseComponent::Class ComponentType;
	
	// inherit from THIS class
	// e.g.
	// struct Example : Component<Example>
	template <typename T>
	class Component
		: public BaseComponent
	{
		ANAX_IDENTIFIABLE(Component) // TODO: remove
		
	public:
		
		virtual ~Component() = 0;
	};
	
	template <typename T>
	Component<T>::~Component()
	{
	}
}

#endif // __ANAX_COMPONENT_H__