#ifndef __SYSTEMS_HPP__
#define __SYSTEMS_HPP__

#include <exception>

#include <anax/System.hpp>

#include "Components.hpp"

class MovementSystem
	: public anax::System<MovementSystem>
{
public:
	
	MovementSystem()
		: Base(anax::ComponentFilter().requires<PositionComponent, VelocityComponent>())
	{
	}
	
	void update()
	{
		auto entities = getEntities();
		for(auto& e : entities)
		{			
			auto position = e.getComponent<PositionComponent>();
			auto velocity = e.getComponent<VelocityComponent>();
			
			position.x += velocity.x;
			position.y += velocity.y;
			position.z += velocity.z;
		}
	}
	
private:
	
	virtual void onEntityAdded(Entity& e) override
	{
		std::cout << "Entity added to MovementSystem: " << e.getId().index << '\n';
		if(e.doesContain<NPCComponent>())
		{
			throw std::logic_error("Player contains NPCComponent :(");
		}
	}
	
	virtual void onEntityRemoved(Entity& e) override
	{
		std::cout << "Entity removed from MovementSystem: " << e.getId().index << '\n';
	}
};

// note: this is a useless system, but I just made it for testing
// purposes
class PlayerSystem
	: public anax::System<PlayerSystem>
{
public:
	
	PlayerSystem()
		: Base(anax::ComponentFilter().requires<PlayerSystem>().excludes<NPCComponent>())
	{
	}
	
private:
	
	virtual void onEntityAdded(Entity& e) override
	{
		std::cout << "Player added: " << e.getComponent<PlayerComponent>().name << '\n';
	}
	
	
	virtual void onEntityRemoved(Entity& e) override
	{
		std::cout << "Player removed: " << e.getComponent<PlayerComponent>().name << '\n';
	}
};

#endif // __SYSTEMS_HPP__