#include "lest.hpp"

#include <anax/ComponentFilter.hpp>

#include "Components.hpp"

const int MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST = 3;


const lest::test specification[] =
{
	"Using require", []
	{
		anax::ComponentFilter filter;
		filter.requires<PositionComponent, VelocityComponent>();
		
		anax::ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES_TO_TEST);
		
		typeList[PlayerComponent::GetTypeId()] = true;
		typeList[PositionComponent::GetTypeId()] = true;
		typeList[VelocityComponent::GetTypeId()] = true;

		EXPECT(filter.doesPassFilter(typeList));
	},
	
	"Using require", []
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