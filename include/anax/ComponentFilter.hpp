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

#ifndef ANAX_COMPONENTFILTER_HPP
#define ANAX_COMPONENTFILTER_HPP

#include <type_traits>

#include <boost/dynamic_bitset.hpp>

#include <anax/detail/EntityIdPool.hpp>
#include <anax/detail/ContainerUtils.hpp>

#include <anax/config.hpp>
#include <anax/Component.hpp>
#include <anax/ComponentTypeList.hpp>

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
		
		template <typename C1>
		ComponentFilter& requires()
		{
			static_assert(std::is_base_of<BaseComponent, C1>(), "C1 does not inherit from Component");
			
			detail::EnsureCapacity(m_requiredComponentsList, C1::GetTypeId());
			m_requiredComponentsList[C1::GetTypeId()] = true;
			
			return *this;
		}
		
		template <typename C1>
		ComponentFilter& requiresOneOf()
		{
			static_assert(std::is_base_of<BaseComponent, C1>(), "C1 does not inherit from Component");
			
			detail::EnsureCapacity(m_requiresOneOfComponentsList, C1::GetTypeId());
			m_requiresOneOfComponentsList[C1::GetTypeId()] = true;
			
			return *this;
		}
		
		template <typename C1>
		ComponentFilter& excludes()
		{
			static_assert(std::is_base_of<BaseComponent, C1>(), "C1 does not inherit from Component");

			detail::EnsureCapacity(m_excludeComponentsList, C1::GetTypeId());
			m_excludeComponentsList[C1::GetTypeId()] = true;
			
			return *this;
		}
		
		
#ifdef ANAX_USE_VARIADIC_TEMPLATES
		
		template <typename C1, typename C2, typename... Components>
		ComponentFilter& requires()
		{
			requires<C1>();
			requires<C2, Components...>();
			
			return *this;
		}
		
		template <typename C1, typename C2, typename... Components>
		ComponentFilter& requiresOneOf()
		{
			requiresOneOf<C1>();
			requiresOneOf<C2, Components...>();
			
			return *this;
		}
		
		template <typename C1, typename C2, typename... Components>
		ComponentFilter& excludes()
		{
			excludes<C1>();
			excludes<C2, Components...>();
			
			return *this;
		}
		
#endif // ANAX_USE_VARIADIC_TEMPLATES
		
		
		/// Determines if a list of component types passes the filter
		/// \param componentTypeList The list of component types you wish to check if it passes through the filter
		/// \return true if the list of component types passes through the filter (i.e. is valid)
		bool doesPassFilter(const ComponentTypeList& componentTypeList) const;
		
		/// Clears the filter
		void clear();
		
	private:
		
		/// A list of component types that are required
		ComponentTypeList m_requiredComponentsList;
		
		/// A list of component types that are required
		/// at least once
		ComponentTypeList m_requiresOneOfComponentsList;
		
		/// A list of component types that must be excluded
		ComponentTypeList m_excludeComponentsList;
	};
}

#endif // ANAX_COMPONENTFILTER_HPP
