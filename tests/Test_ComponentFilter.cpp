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

#include <anax/detail/Filter.hpp>

#include <anax/FilterOptions.hpp>

#include "Components.hpp"

constexpr const unsigned MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST = 4;

// All posibilities (with fail or pass):
// requires 
// requiresOneOf
// excludes
// requires and excludes
// requires and requiresOneOf 
// requiresOneOf and excludes
// requires, requiresOneOf, and excludes
//
// TODO: fix maintainability of this code... It's just a lot of copy pasta atm
const lest::test specification[] =
{
    CASE("requires (pass)")
    {
        auto filter = anax::detail::MakeFilter<anax::Requires<PositionComponent, VelocityComponent>, anax::Excludes<>>();

        anax::detail::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[anax::ComponentTypeId<PositionComponent>()] = true;
        typeList[anax::ComponentTypeId<VelocityComponent>()] = true;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("requires (fail)")
    {
        auto filter = anax::detail::MakeFilter<anax::Requires<PositionComponent, VelocityComponent>, anax::Excludes<>>();

        anax::detail::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[anax::ComponentTypeId<PlayerComponent>()] = true;
        typeList[anax::ComponentTypeId<VelocityComponent>()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("excludes (pass)")
    {
        auto filter = anax::detail::MakeFilter<anax::Requires<>, anax::Excludes<PositionComponent, VelocityComponent>>();

        anax::detail::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[anax::ComponentTypeId<PlayerComponent>()] = false;
        typeList[anax::ComponentTypeId<VelocityComponent>()] = false;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("excludes (fail via one)")
    {
        auto filter = anax::detail::MakeFilter<anax::Requires<>, anax::Excludes<PositionComponent, VelocityComponent>>();

        anax::detail::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[anax::ComponentTypeId<PositionComponent>()] = true;
        typeList[anax::ComponentTypeId<VelocityComponent>()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("excludes (fail via all)")
    {
        auto filter = anax::detail::MakeFilter<anax::Requires<>, anax::Excludes<PositionComponent, VelocityComponent>>();

        anax::detail::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[anax::ComponentTypeId<PlayerComponent>()] = true;
        typeList[anax::ComponentTypeId<VelocityComponent>()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires and excludes (pass)")
    {
        auto filter = anax::detail::MakeFilter<anax::Requires<PositionComponent, VelocityComponent>, anax::Excludes<PlayerComponent>>();

        anax::detail::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[anax::ComponentTypeId<PositionComponent>()] = true;
        typeList[anax::ComponentTypeId<VelocityComponent>()] = true;
        typeList[anax::ComponentTypeId<PlayerComponent>()] = false;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("requires and excludes (fail via requires)")
    {
        auto filter = anax::detail::MakeFilter<anax::Requires<PositionComponent, VelocityComponent>, anax::Excludes<PlayerComponent>>();

        anax::detail::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[anax::ComponentTypeId<VelocityComponent>()] = true;
        typeList[anax::ComponentTypeId<PositionComponent>()] = false;

        typeList[anax::ComponentTypeId<PlayerComponent>()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires and excludes (fail via excludes)")
    {
        auto filter = anax::detail::MakeFilter<anax::Requires<PositionComponent, VelocityComponent>, anax::Excludes<PlayerComponent>>();

        anax::detail::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[anax::ComponentTypeId<VelocityComponent>()] = true;
        typeList[anax::ComponentTypeId<PositionComponent>()] = true;

        typeList[anax::ComponentTypeId<PlayerComponent>()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires and excludes (fail via all)")
    {
        auto filter = anax::detail::MakeFilter<anax::Requires<PositionComponent, VelocityComponent>, anax::Excludes<PlayerComponent>>();

        anax::detail::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[anax::ComponentTypeId<VelocityComponent>()] = false;
        typeList[anax::ComponentTypeId<PositionComponent>()] = false;

        typeList[anax::ComponentTypeId<PlayerComponent>()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
