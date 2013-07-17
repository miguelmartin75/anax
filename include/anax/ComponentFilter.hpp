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
#include "detail/ContainerUtils.hpp"

#include "config.hpp"
#include "ComponentTypeList.hpp"

namespace anax
{
	/// \brief A class used to filter out Components
	///
	/// This class was designed to be used in conjuction
	/// with systems in the entity systems. As it grants
	/// the ability to filter out entities with specific
	/// components.
	///
	/// \author Miguel Martin
	class ComponentFilter
	{
	public:
		
		ComponentFilter() {}
		ComponentFilter(const ComponentFilter&) = default;
		ComponentFilter(ComponentFilter&&) = default;
		ComponentFilter& operator=(const ComponentFilter&) = default;
		ComponentFilter& operator=(ComponentFilter&&) = default;
		
		// TODO: Documentation
		
		template <typename TComponent>
		ComponentFilter& require()
		{
			util::EnsureCapacity(_requiredComponentsList, TComponent::GetTypeId());
			_requiredComponentsList[TComponent::GetTypeId()] = true;
			
			return *this;
		}
		
		template <typename TComponent>
		ComponentFilter& requireOne()
		{
			util::EnsureCapacity(_requiresOneOfComponentsList, TComponent::GetTypeId());
			_requiresOneOfComponentsList[TComponent::GetTypeId()] = true;
			
			return *this;
		}
		
		template <typename TComponent>
		ComponentFilter& exclude()
		{
			util::EnsureCapacity(_excludeComponentsList, TComponent::GetTypeId());
			_excludeComponentsList[TComponent::GetTypeId()] = true;
			
			return *this;
		}
		
		
#ifndef ANAX_DONT_USE_VARIADIC_TEMPLATES
		
		template <typename TComponent, typename... TComponents>
		ComponentFilter& requires()
		{
			require<TComponent>();
			requires<TComponents...>();
			
			return *this;
		}
		
		template <typename TComponent, typename... TComponents>
		ComponentFilter& requiresOneOf()
		{
			requireOne<TComponent>();
			requiresOneOf<TComponents...>();
			
			return *this;
		}
		
		template <typename TComponent, typename... TComponents>
		ComponentFilter& excludes()
		{
			exclude<TComponent>();
			excludes<TComponents...>();
			
			return *this;
		}
		
#endif // ANAX_DONT_USE_VARIADIC_TEMPLATES
		
		
		/// Determines if a list of component types passes the filter
		/// \param componentTypeList The list of component types you wish to check if it passes through the filter
		/// \return true if the list of component types passes through the filter (i.e. is valid)
		bool doesPassFilter(const ComponentTypeList& componentTypeList) const;
		
	private:
		
		/// A list of component types that are required
		ComponentTypeList _requiredComponentsList;
		
		/// A list of component types that are required
		/// at least once
		ComponentTypeList _requiresOneOfComponentsList;
		
		/// A list of component types that must be excluded
		ComponentTypeList _excludeComponentsList;
	};
}

#endif // __ANAX_COMPONENTFILTER_HPP__