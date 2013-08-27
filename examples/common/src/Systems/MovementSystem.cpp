#include <Systems/MovementSystem.hpp>

#include <Components/VelocityComponent.hpp>
#include <Components/TransformComponent.hpp>

MovementSystem::MovementSystem()
	: Base(anax::ComponentFilter().requires<VelocityComponent, TransformComponent>())
{
}

void MovementSystem::update(float deltaTime)
{
	auto entities = getEntities();
	for(auto& entity : entities)
	{
		auto& transform = entity.getComponent<TransformComponent>().transform;
		auto& velocity = entity.getComponent<VelocityComponent>().velocity;
		
		transform.move(velocity * deltaTime);
	}
}