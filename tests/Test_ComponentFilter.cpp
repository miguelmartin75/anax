///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
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

const int MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST = 3;


const lest::test specification[] =
{
	"Using require (1)", []
	{
		anax::ComponentFilter filter;
		filter.requires<PositionComponent, VelocityComponent>();
		
		anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);
		
		typeList[PlayerComponent::GetTypeId()] = true;
		typeList[PositionComponent::GetTypeId()] = true;
		typeList[VelocityComponent::GetTypeId()] = true;

		EXPECT(filter.doesPassFilter(typeList));
	},
	
	"Using require (2)", []
	{
		anax::ComponentFilter filter;
		filter.requires<PositionComponent, VelocityComponent>();
		
		anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);
		
		typeList[PlayerComponent::GetTypeId()] = true;
		typeList[VelocityComponent::GetTypeId()] = true;
		
		EXPECT(!filter.doesPassFilter(typeList));
	},
	
	"Using require and requiresOneOf", []
	{
		anax::ComponentFilter filter;
		filter.requiresOneOf<PositionComponent, VelocityComponent>();
		
		anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);
		
		typeList[PlayerComponent::GetTypeId()] = true;
		typeList[VelocityComponent::GetTypeId()] = true;
		
		EXPECT(filter.doesPassFilter(typeList));
	},
	
	"Using exclude", []
	{
		anax::ComponentFilter filter;
		filter.excludes<PositionComponent, VelocityComponent>();
		
		anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);
		
		typeList[PlayerComponent::GetTypeId()] = true;
		typeList[VelocityComponent::GetTypeId()] = true;
		
		EXPECT(!filter.doesPassFilter(typeList));
	}
};

int main()
{
	return lest::run(specification);
}
