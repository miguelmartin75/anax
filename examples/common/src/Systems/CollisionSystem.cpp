#include <Systems/CollisionSystem.hpp>

#include <Components/TransformComponent.hpp>
#include <Components/CollisionComponent.hpp>

static sf::FloatRect getBBoxRectFor(const sf::Transformable& transformable, const sf::FloatRect& bbox)
{
	return sf::FloatRect(transformable.getPosition().x, transformable.getPosition().y, bbox.width, bbox.height);
}

CollisionSystem::CollisionSystem()
	: Base(anax::ComponentFilter().requires<TransformComponent, CollisionComponent>())
{
}

void CollisionSystem::update(float deltaTime)
{
	auto entities = getEntities();
	
	// Used for temporary values for rectangles
	sf::FloatRect rect1;
	sf::FloatRect rect2;
	
	// Yes this is quite inefficent,
	// however this is just a simple example.
	// NOTE:
	// This does NOT check for collision with rotation
	for(std::size_t i = 0; i < entities.size(); ++i)
	{
		auto& e1 = entities[i];
		
		auto& transform1 = e1.getComponent<TransformComponent>().transform;
		auto& bbox1 = e1.getComponent<CollisionComponent>().BBox;
		rect1 = getBBoxRectFor(transform1, bbox1);
		
		for(std::size_t j = i; j < entities.size(); ++j)
		{
			auto& e2 = entities[j];
			
			auto& bbox2 = e2.getComponent<CollisionComponent>().BBox;
			auto& transform2 = e2.getComponent<TransformComponent>().transform;
			
			rect2 = getBBoxRectFor(transform2, bbox2);
			
			if(rect1.intersects(rect2))
			{
				// Collision occured
				
			}
		}
	}
}