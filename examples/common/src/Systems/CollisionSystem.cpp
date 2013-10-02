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

#include <Systems/CollisionSystem.hpp>

#include <algorithm>

#include <Components/TransformComponent.hpp>
#include <Components/CollisionComponent.hpp>

CollisionSystem::Listener::~Listener()
{
}

static sf::FloatRect getBBoxRectFor(const sf::Transformable& transformable, const sf::FloatRect& bbox)
{
	return sf::FloatRect(transformable.getPosition().x, transformable.getPosition().y, bbox.width, bbox.height);
}

static sf::FloatRect getBBoxRectFor(const anax::Entity& entity)
{
	auto& collision = entity.getComponent<CollisionComponent>();
	auto& transform = entity.getComponent<TransformComponent>().transform;
	auto& bbox = collision.BBox;
	return getBBoxRectFor(transform, bbox);
}

CollisionSystem::CollisionSystem()
	: Base(anax::ComponentFilter().requires<TransformComponent, CollisionComponent>())
{
}

void CollisionSystem::update(float deltaTime)
{
	auto colliders = getEntities();
	
	// Temporary values for rectangles (to check collision)
	sf::FloatRect rect1;
	sf::FloatRect rect2;
	
	
	// NOTES:
	// 1. This is quite inefficent, however this is just a simple example.
	// 2. This does NOT check for collision with rotation
	for(std::size_t i = 0; i < colliders.size(); ++i)
	{
		auto& e1 = colliders[i];
		rect1 = getBBoxRectFor(e1);
		
		if(!e1.getComponent<CollisionComponent>().causesEvents)
		{
			continue;
		}
		
		for(std::size_t j = i; j < colliders.size(); ++j)
		{
			auto& e2 = colliders[j];
			rect2 = getBBoxRectFor(e2);
			
			// Check for the collision
			if(rect1.intersects(rect2))
			{
				for(auto& listener : _listeners)
					listener->onCollisionOccured(e1, e2);
			}
		}
	}
	
	/*
	auto colliders = _colliderSystem.getEntities();
	auto collideables = _collideableSystem.getEntities();
		
	// Temporary values for rectangles (to check collision)
	sf::FloatRect rect1;
	sf::FloatRect rect2;
	
	// Loop through all the colliders in the system
	// (the entities that cause collision events)
	for(std::size_t i = 0; i < colliders.size(); ++i)
	{
		auto& e1 = colliders[i];
		auto& transform1 = e1.getComponent<TransformComponent>().transform;
		auto& bbox1 = e1.getComponent<ColliderComponent>().BBox;
		rect1 = getBBoxRectFor(transform1, bbox1);

		// check for the other colliders
		for(std::size_t j = i; j < colliders.size(); ++j)
		{
			auto& e2 = colliders[j];
			auto& transform2 = e2.getComponent<TransformComponent>().transform;
			auto& bbox2 = e2.getComponent<ColliderComponent>().BBox;
			
			rect2 = getBBoxRectFor(transform2, bbox2);
			if(rect1.intersects(rect2))
			{
				for(auto& listener : _listeners)
					listener->onColliderCollisionOccured(e1, e2);
			}
		}
		
		// check the collideables
		for(auto& e2 : collideables)
		{
			auto& transform2 = e2.getComponent<TransformComponent>().transform;
			auto& bbox2 = e2.getComponent<CollideableComponent>().BBox;
			
			rect2 = getBBoxRectFor(transform2, bbox2);
			if(rect1.intersects(rect2))
			{
				for(auto& listener : _listeners)
					listener->onCollideableCollisionOccured(e1, e2);
			}
		}
	}
	 */
}

void CollisionSystem::addListener(Listener &listener)
{
	_listeners.push_back(&listener);
}

void CollisionSystem::removeListener(Listener &listener)
{
	_listeners.erase(std::remove(_listeners.begin(), _listeners.end(), &listener), _listeners.end());
}