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

#include <anax/ComponentFilter.hpp>

namespace anax
{
    void ComponentFilter::clear()
    {
        m_requiredComponentsList.reset();
        m_requiresOneOfComponentsList.reset();
        m_excludeComponentsList.reset();
    }

    bool ComponentFilter::doesPassFilter(const ComponentTypeList &componentTypeList) const
    {
        // loop through all the component type bits
#ifdef ANAX_USE_DYNAMIC_AMOUNT_OF_COMPONENTS        
        std::size_t i = m_requiredComponentsList.find_first();
        for(; i != ComponentTypeList::npos; i = m_requiredComponentsList.find_next(i))
#else
        for(std::size_t i = 0; i < m_requiredComponentsList.size(); ++i)
#endif
        {
            // ensure that the none of the component types at index
            // are false (i.e. ensure that it meets all of the requirement list)
            if(
#ifdef ANAX_USE_DYNAMIC_AMOUNT_OF_COMPONENTS        
               i >= componentTypeList.size() || 
#else
               m_requiredComponentsList[i] == true && 
#endif // ANAX_USE_DYNAMIC_AMOUNT_OF_COMPONENTS

                componentTypeList[i] == false)
            {
                return false;
            }
        }

        if(!m_requiresOneOfComponentsList.none())
        {
            if(
#ifdef ANAX_USE_DYNAMIC_AMOUNT_OF_COMPONENTS
                // NOTE: Can't use dynamic_bitset's operator^ as it causes a crash
                !m_requiresOneOfComponentsList.intersects(componentTypeList)
#else
                !(m_requiresOneOfComponentsList ^ componentTypeList).any()
#endif
              )
            {
                return false;
            }
        }

        if(!m_excludeComponentsList.none())
        {
            if(
#ifdef ANAX_USE_DYNAMIC_AMOUNT_OF_COMPONENTS
                m_excludeComponentsList.intersects(componentTypeList)
#else
                (m_excludeComponentsList ^ componentTypeList).any()
#endif
              )
            {
                return false;
            }
        }

        return true;
    }
}
