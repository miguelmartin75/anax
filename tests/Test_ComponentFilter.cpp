#include "lest.hpp"

#include <anax/ComponentFilter.hpp>

#include "Components.hpp"

const lest::test specification[] =
{
	"Using require (succeed)" []
	{
		anax::ComponentFilter filter;
		filter.requires<PositionComponent, VelocityComponent>();
		
		ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES);
		
		typeList[PlayerComponent::GetTypeId()] = true;
		typeList[PositionComponent::GetTypeId()] = true;
		typeList[VelocityComponent::GetTypeId()] = true;

		EXPECT(filter.doesPassFilter(typeList));
	}
	
	"Using require (fail)" []
	{
		anax::ComponentFilter filter;
		filter.requires<PositionComponent, VelocityComponent>();
		
		ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES);
		
		typeList[PlayerComponent::GetTypeId()] = true;
		typeList[VelocityComponent::GetTypeId()] = true;
		
		EXPECT(filter.doesPassFilter(typeList));
	}
	
	"Using require and optional (succeed)" []
	{
		anax::ComponentFilter filter;
		filter.optional<PositionComponent, VelocityComponent>();
		
		ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES);
		
		typeList[PlayerComponent::GetTypeId()] = true;
		typeList[VelocityComponent::GetTypeId()] = true;
		
		EXPECT(filter.doesPassFilter(typeList));
	}
	
	"Using exclude (succeed)" []
	{
		anax::ComponentFilter filter;
		filter.exclude<PositionComponent, VelocityComponent>();
		
		ComponentTypeList typeList(MAXIMUM_AMOUNT_OF_COMPONENT_TYPES);
		
		typeList[PlayerComponent::GetTypeId()] = true;
		typeList[VelocityComponent::GetTypeId()] = true;
		
		EXPECT(filter.doesPassFilter(typeList));
	}
};

int main()
{
	return lest::run(specification);
}