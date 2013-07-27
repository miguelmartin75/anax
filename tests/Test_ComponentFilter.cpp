#include "catch.hpp"
#define CATCH_CONFIG_MAIN

#include "anax/ComponentFilter.hpp"


class PositionComponent
	: public anax::Component<PositionComponent>
{
public:
};

class VelocityComponent
	: public anax::Component<AnotherComponent>
{
public:
	float x, y, z;
};

class PlayerComponent
	: public anax::Component<ExcludeComponent>
{
public:
};



TEST_CASE("Using require", "[ComponentFilter]")
{
	anax::ComponentFilter filter;
	filter.requires<PositionComponent, AnotherComponent>();
	
	REQUIRE(filter.doesPassFilter());
}

TEST_CASE("Using require and optional", "")