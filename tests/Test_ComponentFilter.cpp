///
/// anax tests
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

#include <lest.hpp>

#include <anax/FilterOptions.hpp>

#include "Components.hpp"

constexpr const unsigned MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST = 4;

using namespace anax;
using namespace anax::detail;

namespace 
{
    // I don't think this is possible with functions
    template <class... Types>
    struct Assigner { void operator()(ComponentTypeList& list) const; };

    template <class Type>
    struct Assigner<Type>
    {
        void operator()(ComponentTypeList& list) const 
        {
            list[ComponentTypeId<Type>()] = true;
        }
    };

    template <class Type, class... Types>
    struct Assigner<Type, Types...>
    {
        void operator()(ComponentTypeList& list) const 
        {
            Assigner<Type>()(list);
            Assigner<Types...>()(list);
        }
    };

    template <class Type, class... Types>
    ComponentTypeList createTypeList()
    {
        ComponentTypeList temp(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);
        Assigner<Type, Types...>()(temp);
        return temp;
    }
}


// All posibilities (with fail or pass):
// requires 
// requiresOneOf
// excludes
// requires and excludes
// requires and requiresOneOf 
// requiresOneOf and excludes
// requires, requiresOneOf, and excludes
const lest::test specification[] =
{
    CASE("requires (pass)")
    {
        auto filter = MakeFilter<Requires<PositionComponent, VelocityComponent>, Excludes<>>();
        auto typeList = createTypeList<PositionComponent, VelocityComponent>();

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("requires (fail)")
    {
        auto filter = MakeFilter<Requires<PositionComponent, VelocityComponent>, Excludes<>>();
        auto typeList = createTypeList<PlayerComponent>();

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("excludes (pass)")
    {
        auto filter = MakeFilter<Requires<>, Excludes<PositionComponent, VelocityComponent>>();
        auto typeList = createTypeList();

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("excludes (fail via one)")
    {
        auto filter = MakeFilter<Requires<>, Excludes<PositionComponent, VelocityComponent>>();
        auto typeList = createTypeList<PositionComponent>();

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("excludes (fail via all)")
    {
        auto filter = MakeFilter<anax::Requires<>, Excludes<PositionComponent, VelocityComponent>>();
        auto typeList = createTypeList<PlayerComponent, VelocityComponent>();

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires and excludes (pass)")
    {
        auto filter = MakeFilter<Requires<PositionComponent, VelocityComponent>, Excludes<PlayerComponent>>();
        auto typeList = createTypeList<PositionComponent, VelocityComponent>();

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("requires and excludes (fail via requires)")
    {
        auto filter = MakeFilter<Requires<PositionComponent, VelocityComponent>, Excludes<PlayerComponent>>();
        auto typeList = createTypeList<VelocityComponent>();

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires and excludes (fail via excludes)")
    {
        auto filter = MakeFilter<Requires<PositionComponent, VelocityComponent>, Excludes<PlayerComponent>>();
        auto typeList = createTypeList<VelocityComponent, PositionComponent, PlayerComponent>();

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires and excludes (fail via all)")
    {
        auto filter = MakeFilter<Requires<PositionComponent, VelocityComponent>, Excludes<PlayerComponent>>();
        auto typeList = createTypeList<PlayerComponent>();

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
