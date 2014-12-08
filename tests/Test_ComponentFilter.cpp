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

#include "lest.hpp"

#include <anax/ComponentFilter.hpp>

#include "Components.hpp"

constexpr const int MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST = 3;

// All posibilities (with fail or pass):
// require 
// requiresOneOf
// exclude
// require and exclude
// require and requiresOneOf 
// requiresOneOf and exclude
// require, requiresOneOf, and exclude
const lest::test specification[] =
{
    CASE("Using require (pass)")
    {
        anax::ComponentFilter filter;
        filter.requires<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = true;
        typeList[PositionComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList));
    },

    CASE("Using require (fail)")
    {
        anax::ComponentFilter filter;
        filter.requires<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("Using requiesOneOf (pass)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList));
    },

    CASE("Using requiesOneOf (fail)")
    {
        anax::ComponentFilter filter;
        filter.requiresOneOf<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = false;
        typeList[VelocityComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("Using exclude (pass)")
    {
        anax::ComponentFilter filter;
        filter.excludes<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = false;
        typeList[VelocityComponent::GetTypeId()] = false;

        EXPECT(filter.doesPassFilter(typeList) == false);
    },

    CASE("Using exclude (fail)")
    {
        anax::ComponentFilter filter;
        filter.excludes<PositionComponent, VelocityComponent>();

        anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);

        typeList[PlayerComponent::GetTypeId()] = true;
        typeList[VelocityComponent::GetTypeId()] = true;

        EXPECT(filter.doesPassFilter(typeList) == false);
    }

    CASE("Using requiresOneOf and exclude (pass)")
    {

    },

    CASE("Using requiresOneOf and exclude (fail)")
    {
    },

    CASE("Using require and requiresOneOf (pass)")
    {
    },

    CASE("Using require and requiresOneOf (fail)")
    {
    },

    CASE("Using requiresOneOf and exclude (pass)")
    {
    },

    CASE("Using requiresOneOf and exclude (fail)")
    {
    }

    CASE("Using require, requiresOneOf and exclude (pass)")
    {
    },

    CASE("Using require, requiresOneOf and exclude (fail)")
    {
    }
};

int main()
{
    return lest::run(specification);
}
