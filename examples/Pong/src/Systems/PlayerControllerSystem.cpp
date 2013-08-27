#include <Systems/PlayerControllerSystem.hpp>

#include <Components/PlayerComponent.hpp>
#include <Components/VelocityComponent.hpp>

#include <SFML/Window/Keyboard.hpp>

PlayerControllerSystem::PlayerControllerSystem()
	: Base(anax::ComponentFilter().requires<PlayerComponent, VelocityComponent>())
{
}

void PlayerControllerSystem::update(float deltaTime)
{
	auto entities = getEntities();
	
	for(auto& entity : entities)
	{
		auto& velocity = entity.getComponent<VelocityComponent>().velocity;
		auto& controls = entity.getComponent<PlayerComponent>().controls;
		auto& baseSpeed = entity.getComponent<PlayerComponent>().baseSpeed;
		
		if(sf::Keyboard::isKeyPressed(controls.up))
		{
			// set velocity to be vertically up (one unit)
			velocity.y = baseSpeed;
		}
		else if(sf::Keyboard::isKeyPressed(controls.down))
		{
			// set velocity to be vertically down (one unit)
			velocity.y = -baseSpeed;
		}
		else
		{
			// reset velocity
			velocity.x = 0;
			velocity.y = 0;
		}
	}
}