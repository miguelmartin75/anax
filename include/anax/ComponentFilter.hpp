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

#ifndef __ANAX_COMPONENTFILTER_HPP__
#define __ANAX_COMPONENTFILTER_HPP__

#include <boost/dynamic_bitset.hpp>

#include "detail/EntityIdPool.hpp"
#include "util/ContainerUtils.hpp"

#include "config.hpp"

namespace anax
{
	struct ComponentFilter
	{
		typedef boost::dynamic_bitset<> BitSet;
		
		/// Contains all the Component IDs (IDs are the index of the BitSet), which the ComponentFilter WILL keep
		/// This is used if you want to make sure an Entity WILL have a Component attached to it
		BitSet requiredComponentsBitSet;
		
		/// Contains all the Component IDs (IDs are the index of the BitSet), which the ComponentFilter WILL set as optional
		/// This is used if you optionally want the Component to be attached
		BitSet requiresOneOfComponentsBitSet;
		
		/// Contains all the Component IDs (IDs are the index of the BitSet), which the ComponentFilter WILL filter out
		/// This is used if you want to make sure a Component is NOT attached to an Entity
		BitSet excludeComponentsBitSet;
		
		
		ComponentFilter() {}
		ComponentFilter(const ComponentFilter&) = default;
		ComponentFilter(ComponentFilter&&) = default;
		ComponentFilter& operator=(const ComponentFilter&) = default;
		ComponentFilter& operator=(ComponentFilter&&) = default;
		
#ifdef ANAX_DONT_USE_VARIADIC_TEMPLATES
		
		template <typename TComponent, typename... TComponents>
		ComponentFilter& requires()
		{
			util::EnsureCapacity(requiredComponentsBitSet, TComponent::GetTypeId());
			requiredComponentsBitSet[TComponent::GetTypeId()] = true;
			
			requires<TComponents...>();
			
			return *this;
		}
		
		template <typename TComponent, typename... TComponents>
		ComponentFilter& requiresOneOf()
		{
			util::EnsureCapacity(requiresOneOfComponentsBitSet, TComponent::GetTypeId());
			requiresOneOfComponentsBitSet[TComponent::GetTypeId()] = true;
			
			requiresOneOf<TComponents...>();
			
			return *this;
		}
		
		template <typename TComponent, typename... TComponents>
		ComponentFilter& exclude()
		{
			util::EnsureCapacity(excludeComponentsBitSet, TComponent::GetTypeId());
			excludeComponentsBitSet[TComponent::GetTypeId()] = true;
			
			exclude<TComponents...>();
			
			return *this;
		}
		
#endif // ANAX_DONT_USE_VARIADIC_TEMPLATES
		
		
		bool matches(const ComponentFilter& componentFilter) const
		{ return Matches(*this, componentFilter); }
		
		static bool Matches(const ComponentFilter& filter1, const ComponentFilter& filter2);
	};
}

#endif // __ANAX_COMPONENTFILTER_HPP__