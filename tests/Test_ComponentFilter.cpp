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

#include <anax/ComponentFilter.hpp>

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
        anax::ComponentFilter filter;
        filter.requires<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = true;
        typeList[PositionComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("requires (fail)")
    {
        anax::ComponentFilter filter;
        filter.requires<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requiesOneOf (pass with one)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PositionComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("requiesOneOf (pass with all)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },


    CASE("requiesOneOf (fail)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = false;
        typeList[VelocityComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("excludes (pass)")
    {
        anax::ComponentFilter filter;
        filter.excludes<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = false;
        typeList[VelocityComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("excludes (fail via one)")
    {
        anax::ComponentFilter filter;
        filter.excludes<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PositionComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("excludes (fail via all)")
    {
        anax::ComponentFilter filter;
        filter.excludes<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requiresOneOf and excludes (pass)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PositionComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = false;
        typeList[PlayerComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("requiresOneOf and excludes (fail)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PositionComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = false;
        typeList[PlayerComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires and requiresOneOf (pass)")
    {
        anax::ComponentFilter filter;
        filter.requires<PlayerComponent>();
        filter.requiresOneOf<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PositionComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = false;

        typeList[PlayerComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("requires and requiresOneOf (fail via requiresment)")
    {
        anax::ComponentFilter filter;
        filter.requires<PlayerComponent>();
        filter.requiresOneOf<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[VelocityComponent::GetTypeId()] = true;
        typeList[PositionComponent::GetTypeId()] = true;

        typeList[PlayerComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires and requiresOneOf (fail via requiresOneOf)")
    {
        anax::ComponentFilter filter;
        filter.requires<PlayerComponent>();
        filter.requiresOneOf<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[VelocityComponent::GetTypeId()] = false;
        typeList[PositionComponent::GetTypeId()] = false;

        typeList[PlayerComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires and requiresOneOf (fail via all)")
    {
        anax::ComponentFilter filter;
        filter.requires<PlayerComponent>();
        filter.requiresOneOf<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[VelocityComponent::GetTypeId()] = false;
        typeList[PositionComponent::GetTypeId()] = false;

        typeList[PlayerComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requiresOneOf and excludes (pass)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[VelocityComponent::GetTypeId()] = true;

        typeList[VelocityComponent::GetTypeId()] = true;
        typeList[PositionComponent::GetTypeId()] = false;

        typeList[PlayerComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("requiresOneOf and excludes (fail via requiresOneOf)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[VelocityComponent::GetTypeId()] = true;

        typeList[VelocityComponent::GetTypeId()] = false;
        typeList[PositionComponent::GetTypeId()] = false;

        typeList[PlayerComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requiresOneOf and excludes (fail via excludes)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[VelocityComponent::GetTypeId()] = true;

        typeList[VelocityComponent::GetTypeId()] = true;
        typeList[PositionComponent::GetTypeId()] = false;

        typeList[PlayerComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requiresOneOf and excludes (fail via all)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[VelocityComponent::GetTypeId()] = true;

        typeList[VelocityComponent::GetTypeId()] = false;
        typeList[PositionComponent::GetTypeId()] = false;

        typeList[PlayerComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires, requiresOneOf and excludes (pass)")
    {
        anax::ComponentFilter filter;
        filter.requires<NPCComponent>();
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[NPCComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = true;
        typeList[PositionComponent::GetTypeId()] = false;
        typeList[PlayerComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == true);
    },

    CASE("requires, requiresOneOf and excludes (fail via requires)")
    {
        anax::ComponentFilter filter;
        filter.requires<NPCComponent>();
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[NPCComponent::GetTypeId()] = false;
        typeList[VelocityComponent::GetTypeId()] = true;
        typeList[PositionComponent::GetTypeId()] = false;
        typeList[PlayerComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires, requiresOneOf and excludes (fail via requiresOneOf)")
    {
        anax::ComponentFilter filter;
        filter.requires<NPCComponent>();
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[NPCComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = false;
        typeList[PositionComponent::GetTypeId()] = false;
        typeList[PlayerComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires, requiresOneOf and excludes (fail via excludes)")
    {
        anax::ComponentFilter filter;
        filter.requires<NPCComponent>();
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[NPCComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = true;
        typeList[PositionComponent::GetTypeId()] = false;
        typeList[PlayerComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("requires, requiresOneOf and excludes (fail via all)")
    {
        anax::ComponentFilter filter;
        filter.requires<NPCComponent>();
        filter.requiresOneOf<PositionComponent, VelocityComponent>();
        filter.excludes<PlayerComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[NPCComponent::GetTypeId()] = false;
        typeList[VelocityComponent::GetTypeId()] = false;
        typeList[PositionComponent::GetTypeId()] = false;
        typeList[PlayerComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    }
};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
