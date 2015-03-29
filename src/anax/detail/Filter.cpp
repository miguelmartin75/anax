#include <anax/detail/Filter.hpp>

namespace anax
{
    namespace detail
    {
        bool Filter::doesPassFilter(const ComponentTypeList& componentTypeList) const
        {
            for(std::size_t i = 0; i < m_requires.size(); ++i)
            {
                if(m_requires[i] == true && componentTypeList[i] == false)
                {
                    return false;
                }
            }

            if((m_excludes & componentTypeList).any())
            {
                return false;
            }

            return true;
        }
    }
}
