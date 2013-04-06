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

#ifndef __ANAX_COMPONENTFILTER_H__
#define __ANAX_COMPONENTFILTER_H__

#include "util/DynamicArrayUtils.h"

#include "Types.h"
#include "Component.h"

namespace anax
{
	/// \class ComponentFilter
	/// \brief A "filter" for Components that is used with an EntitySystem
	///
	/// This class is designed to be used with an EntitySystem, this is because an EntitySystem will only
	/// process Entity objects of a particular type.
	///
	/// \author Miguel Martin
	struct ComponentFilter
	{
		/// Contains all the Component IDs (IDs are the index of the BitSet), which the ComponentFilter WILL keep
		/// This is used if you want to make sure an Entity WILL have a Component attached to it
		DynamicBitSet requiredComponentsBitSet;
		/// Contains all the Component IDs (IDs are the index of the BitSet), which the ComponentFilter WILL set as optional
		/// This is used if you optionally want the Component to be attached
		DynamicBitSet oneComponentBits;
		/// Contains all the Component IDs (IDs are the index of the BitSet), which the ComponentFilter WILL filter out
		/// This is used if you want to make sure a Component is NOT attached to an Entity
		DynamicBitSet excludeComponentBitSet;
		
		
		/// Default Constructor
		ComponentFilter()
		{
			/* do nothing */
		}
		
		
		/// Copy Constuctor
		/// \param componentFilter The ComponentFilter you wish to copy from
		ComponentFilter(const ComponentFilter& componentFilter)
			: requiredComponentsBitSet(componentFilter.requiredComponentsBitSet),
			  oneComponentBits(componentFilter.oneComponentBits),
			  excludeComponentBitSet(componentFilter.excludeComponentBitSet)
		{
			/* do nothing */
		}
		
		/// Destructor
		~ComponentFilter()
		{
			/* do nothing */
		}
		
		
		
		/// Use this method if you require an Entity to have a specific type of Component
		/// \tparam T Must be derived from Component
		/// \return *this
		template<typename T>
		ComponentFilter& requires()
		{
			util::AssignBitsetIndexWithAutoResize(requiredComponentsBitSet, T::GetClass().getId(), true);
			return *this;
		}
		
		/// Use this method if you require an Entity to have at least one Component
		/// that you have decided upon.
		/// \tparam T Must be derived from Component
		/// \return *this
		template<typename T>
		ComponentFilter& requiresOne()
		{
			util::AssignBitsetIndexWithAutoResize(oneComponentBits, T::GetClass().getId(), true);
			return *this;
		}
		
		/// Use this method if you require an Entity to not have a specific type of Component
		/// \tparam T Must be derived from Component
		/// \return *this
		template<typename T>
		ComponentFilter& exclude()
		{
			util::AssignBitsetIndexWithAutoResize(excludeComponentBitSet, T::GetClass().getId(), true);
			return *this;
		}
		
		
		
		/// Assignment opeartor
		/// \param componentFilter The ComponentFilter you wish to copy from
		/// \return *this
		const ComponentFilter& operator=(const ComponentFilter& componentFilter)
		{
			if(this != &componentFilter)
			{
				requiredComponentsBitSet = componentFilter.requiredComponentsBitSet;
				oneComponentBits = componentFilter.oneComponentBits;
				excludeComponentBitSet = componentFilter.excludeComponentBitSet;
			}
			
			return *this;
		}
	};
}

#endif // __ANAX_COMPONENTFILTER_H__