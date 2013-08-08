#ifndef __COMPONENTS_HPP__
#define __COMPONENTS_HPP__

#include <string>
#include <anax/Component.hpp>

const int MAXIMUM_AMOUNT_OF_COMPONENT_TYPES = 3;

class PositionComponent
	: public anax::Component<PositionComponent>
{
public:
    float x, y, z;
};

class VelocityComponent
	: public anax::Component<VelocityComponent>
{
public:
	float x, y, z;
};

class PlayerComponent
	: public anax::Component<PlayerComponent>
{
public:
    std::string name;
};

class NPCComponent
	: public anax::Component<NPCComponent>
{
public:
    std::string name;
	
	enum Type
	{
		MOVING = 0,
		STILL,
		MAGICAL
	} type;
};

#endif // __COMPONENTS_HPP__
