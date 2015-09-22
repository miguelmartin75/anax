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

#ifndef ANAX_DETAIL_FILTER_HPP
#define ANAX_DETAIL_FILTER_HPP

#include <type_traits>

#include <anax/Config.hpp>
#include <anax/Component.hpp>

#include <anax/detail/ClassTypeId.hpp>
#include <anax/detail/ComponentTypeList.hpp>

namespace anax
{
    namespace detail
    {
        template <class... Args>
        struct TypeList { };

        struct BaseRequires { };
        struct BaseExcludes { };

        struct Filter 
        {
        public:

            Filter(ComponentTypeList requires, ComponentTypeList excludes) :
                m_requires(requires), m_excludes(excludes)
            { }

            bool doesPassFilter(const ComponentTypeList& typeList) const;

        private:

            ComponentTypeList m_requires;
            ComponentTypeList m_excludes;
        };

        template <class... Args>
        static ComponentTypeList types(TypeList<Args...> typeList) { return ComponentTypeList(); }

        template <class T, class... Args>
        static ComponentTypeList types(detail::TypeList<T, Args...> typeList)
        {
            static_assert(std::is_base_of<Component, T>::value, "Invalid component");
            return ComponentTypeList().set(ComponentTypeId<T>()) | types(detail::TypeList<Args...>());
        }

        template <class RequireList, class ExcludeList> 
        Filter MakeFilter()
        {
            static_assert(std::is_base_of<BaseRequires, RequireList>::value, "RequireList is not a requirement list");
            static_assert(std::is_base_of<BaseExcludes, ExcludeList>::value, "ExcludeList is not an excludes list");
            return Filter{types(RequireList{}), types(ExcludeList{})};
        }
    }
}



#endif // ANAX_DETAIL_FILTER_HPP
