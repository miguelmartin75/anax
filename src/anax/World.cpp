///
/// anax
/// Copyright (C) 2013 Anax Creations. All rights reserved.
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

#include "World.h"

namespace anax
{
	World::World()
	{
	}
	
	
	World::~World()
	{
		clear();
	}
	
	
	void World::update()
	{
		// clean the World
		clean();
	}
	
	void World::clear()
	{
		// clean the World
		clean();
		
		// clear all da classes
		_entitySystemContainer.clear();
		_entityContainer.clear();
		_componentStorage.clear();
		_entityFactory.clearCountData();
	}
	
	void World::clean()
	{
		// process the cache
		processAddedEntityCache();
		processActivatedEntityCache();
		processDeactivatedEntityCache();
		processRemovedEntityCache();
		
		// clear the cache
		clearEntityCache();
	}
	
	
	
	EntityPtr World::createEntity()
	{
		EntityPtr entity = _entityFactory.createEntity(*this);
		addEntity(entity); // insert the Entity
		return entity;
	}
	
	void World::addEntity(EntityPtr entity)
	{
		// insert it to the world
		_entityContainer.insert(entity);
		
		// add it to the cache, we'll process it later
		_entityAddedCache.push_back(entity);
	}
	
	void World::removeEntity(EntityPtr entity)
	{
		// add it temporarily to a cache, we'll delete  it later
		_entityRemovedCache.push_back(entity);
	}
	
	void World::activateEntity(EntityPtr entity)
	{
		// if the Entity is already activated
		if(isEntityActivated(entity))
			return;
		
		// activate it in the Container
		_entityContainer.activate(entity);
		
		// add it temporarily to a cache, we'll activate it later
		_entityActivatedCache.push_back(entity);
	}
	
	void World::deactivateEntity(EntityPtr entity)
	{
		// if the Entity is not activated
		if(!isEntityActivated(entity))
			return;
		
		// activate it in the Container
		_entityContainer.deactivate(entity);
		
		// add it temporarily to a cache, we'll deactivate it later
		_entityDeactivatedCache.push_back(entity);
	}
	
	bool World::isEntityActivated(ConstEntityPtr entity) const
	{
		return _entityContainer.isActivated(entity);
	}
	
	bool World::isEntityAlive(EntityId entityId) const
	{
		return _entityContainer.contains(entityId);
	}
	
	
	
	// UTILITY METHODS
	
	void World::processActivatedEntityCache()
	{
		EntityPtr entity = NULL;
		
		for(EntityArray::iterator i = _entityActivatedCache.begin(); i != _entityActivatedCache.end(); ++i)
		{
			entity = *i;
			
			// check the Entity with ALL the EntitySystem objects within the EntitySystemContainer
			for(EntitySystemContainer::iterator i = _entitySystemContainer.begin(); i != _entitySystemContainer.end(); ++i)
			{
				// is the pointer null?
				if(*i == NULL)
					continue;
				
				(*i)->check(entity);
			}
		}
	}
	
	void World::processDeactivatedEntityCache()
	{
		EntityPtr entity = NULL;
		
		for(EntityArray::iterator i = _entityDeactivatedCache.begin(); i != _entityDeactivatedCache.end(); ++i)
		{
			entity = *i;
			
			// check the Entity with ALL the EntitySystem objects within the EntitySystemContainer
			for(EntitySystemContainer::iterator i = _entitySystemContainer.begin(); i != _entitySystemContainer.end(); ++i)
			{
				// is the pointer null?
				if(*i == NULL)
					continue;
				
				(*i)->check(entity);
			}
		}
	}
	
	void World::processAddedEntityCache()
	{
		EntityPtr entity = NULL;
		
		for(EntityArray::iterator i = _entityAddedCache.begin(); i != _entityAddedCache.end(); ++i)
		{
			entity = *i;
			
			// check the Entity with ALL the EntitySystem objects within the EntitySystemContainer
			for(EntitySystemContainer::iterator i = _entitySystemContainer.begin(); i != _entitySystemContainer.end(); ++i)
			{
				// is the pointer null?
				if(*i == NULL)
					continue;
				
				(*i)->check(entity);
			}
		}
	}
	
	void World::processRemovedEntityCache()
	{
		EntityPtr entity = NULL;
		
		for(EntityArray::iterator i = _entityRemovedCache.begin(); i != _entityRemovedCache.end(); ++i)
		{
			entity = *i;
			
			// check the Entity with ALL the EntitySystem objects within the EntitySystemContainer
			for(EntitySystemContainer::iterator i = _entitySystemContainer.begin(); i != _entitySystemContainer.end(); ++i)
			{
				// is the pointer null?
				if(*i == NULL)
					continue;
				
				(*i)->onRemovedFromScene(entity);
			}
			
			// delete components
			_componentStorage.destroyAllComponents(*entity);
			
			// erase it from the container
			_entityContainer.erase(entity);
		}
	}
	
	void World::clearEntityCache()
	{
		_entityActivatedCache.clear();
		_entityDeactivatedCache.clear();
		_entityAddedCache.clear();
		_entityRemovedCache.clear();
	}
}