///
/// anax
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
///
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is hereby granted, free of charge, to any person
/// obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// 1. The origin of this software must not be misrepresented;
///    you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment
///    in the product documentation would be appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such,
///	   and must not be misrepresented as being the original software.
///
/// 3. The above copyright notice and this permission notice shall be included in
///    all copies or substantial portions of the Software.
///

#include <anax/World.hpp>

#include <cassert>

namespace anax
{
	World::World()
		: World(DEFAULT_ENTITY_POOL_SIZE)
	{
	}
	
	World::World(std::size_t entityPoolSize)
		: _entityIdPool(entityPoolSize),
	      _entityAttributes(entityPoolSize),
	      _aliveEntityCount(0)
	{
	}
	
	Entity World::createEntity()
	{
		++_aliveEntityCount;
		checkForResize();
		
		return Entity(*this, _entityIdPool.create());
	}
	
	std::vector<Entity> World::createEntities(std::size_t amount)
	{
		std::vector<Entity> temp;
		temp.reserve(amount);
		
		_aliveEntityCount += amount;
		checkForResize();
		
		for(decltype(amount) i = 0; i < amount; ++i)
		{
			temp.emplace_back(*this, _entityIdPool.create());
		}
		
		return temp;
	}
	
	void World::killEntity(Entity& entity)
	{
		--_aliveEntityCount;
		
		// deactivate the entity
		deactivateEntity(entity);
		
		// now kill the entity (add it to the killed cache)
		_entityCache.killed.push_back(entity);
	}
	
	void World::killEntities(std::vector<Entity>& entities)
	{
		for(auto& i : entities)
		{
			killEntity(i);
		}
	}
	
	void World::activateEntity(Entity& entity)
	{
		assert(isValid(entity));
		
		_entityCache.activated.push_back(entity);
	}
	
	void World::deactivateEntity(Entity& entity)
	{
		assert(isValid(entity));
		
		_entityCache.deactivated.push_back(entity);
	}
	
	bool World::isActivated(const Entity& entity) const
	{
		assert(isValid(entity));

		return _entityAttributes.activated[entity.getId().index];
	}
	
	bool World::isValid(const anax::Entity &entity) const
	{
		return _entityIdPool.isValid(entity.getId());
	}
	
	void World::refresh()
	{
		// go through all the activated entities from last call to refresh
		for(auto& i : _entityCache.activated)
		{
			_entityAttributes.activated[i.getId().index] = true;
			
			// loop through all the systems within the world
			for(auto& j : _systems)
			{
				// if the entity passes the filter the system has
				if(j.second->getComponentFilter().doesPassFilter(_entityAttributes.componentStorage.getComponentTypeList(i)))
				{
					j.second->add(i); // add it to the system
				}
			}
		}
		
		
		// go through all the deactivated entities from last call to refresh
		for(auto& i : _entityCache.deactivated)
		{
			_entityAttributes.activated[i.getId().index] = false;

			// loop through all the systems within the world
			for(auto& j : _systems)
			{
				// remove the entity from the system
				// TODO: Make this more efficent?
				// I could check if the entity is within the system
				// with a flag, but then I would require a TypeId attribtue
				// within the system class... So I may/maynot need to add this
				j.second->remove(i); 
			}
		}
		
		// go through all the killed entities from last call to refresh
		for(auto& i : _entityCache.killed)
		{
			// destroy all the components it has
			_entityAttributes.componentStorage.removeAllComponents(i);
			
			// remove it from the id pool
			_entityIdPool.remove(i.getId());
		}
		
		// clear the cache
		_entityCache.clear();
	}
	
	std::size_t World::getAliveEntityCount() const
	{
		return _aliveEntityCount;
	}
	
	
	void World::checkForResize()
	{
		if(getAliveEntityCount() > _entityIdPool.getSize())
		{
			resize(getAliveEntityCount());
		}
	}
	
	void World::resize(std::size_t amount)
	{
		_entityIdPool.resize(amount);
		_entityAttributes.resize(amount);
	}
	
	void World::addSystem(BaseSystem& system, detail::TypeId systemTypeId)
	{
		assert(_systems.find(systemTypeId) == _systems.end() && "System is already contained within the world");
		
		_systems[systemTypeId] = &system;
	}
	
	void World::removeSystem(detail::TypeId systemTypeId)
	{
		assert(_systems.find(systemTypeId) != _systems.end() && "System does not exist in world");
		_systems.erase(systemTypeId);
	}
}