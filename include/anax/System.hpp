#ifndef ANAX_SYSTEM_HPP
#define ANAX_SYSTEM_HPP

#include <cstddef>
#include <vector>

#include <anax/FilterOptions.hpp>

#include <anax/detail/BaseSystem.hpp>
#include <anax/detail/ClassTypeId.hpp>

namespace anax
{
    /// \brief A class that follows the CRTP pattern, used to define custom systems
    /// \tparam T The System you are defining
    /// \tparam RequirementList 
    ///
    /// This class uses the CRTP pattern to make a unique identifier for each system
    /// class
    ///
    /// \see BaseSystem
    /// If you wish to store systems generically and for further documentation.
    ///
    /// \author Miguel Martin
    template <class RequireList, class ExcludeList = Excludes<>>
    class System : public detail::BaseSystem
    {
    public:

        /// Default constructor
        System() :
            BaseSystem{detail::MakeFilter<RequireList, ExcludeList>()}
        {
        }
    };

    template<class T>
    detail::TypeId SystemTypeId()
    {
        return detail::ClassTypeId<detail::BaseSystem>::GetTypeId<T>();
    }
}

#endif // ANAX_SYSTEM_HPP
