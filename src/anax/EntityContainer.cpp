///
/// anax
/// Copyright (C) 2012-2013 Anax Creations. All rights reserved.
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

#include "EntityContainer.h"

#include <cassert>

#include "Entity.h"
#include "World.h"



namespace anax
{
	EntityContainer::EntityContainer()
	{
	}
	
	EntityContainer::~EntityContainer()
	{
	}
	
	
	
	void EntityContainer::insert(EntityPtr entity)
	{
		assert(entity != NULL);
		
		EntityId index = _idPool.next();
		
		util::EnsureCapacity(_registeredEntities, index);
		util::EnsureCapacity(_activatedEntities, index);
		
		_registeredEntities[index] = SmartEntityPtr(entity);
		_activatedEntities[index] = false;
		
		entity->_id = index; // assign the ID
	}
	
	void EntityContainer::erase(EntityId entityId)
	{
		assert(entityId <= _registeredEntities.size());
		
		_activatedEntities[entityId] = false;
		_registeredEntities[entityId] = NULL;
	}
	
	void EntityContainer::activate(EntityPtr entity)
	{
		setIsActivated(entity, true);
	}
	
	void EntityContainer::deactivate(EntityPtr entity)
	{
		setIsActivated(entity, false);
	}
	
	void EntityContainer::setIsActivated(EntityPtr entity, bool isActivated)
	{
		assert(entity != NULL && entity->getId() <= _registeredEntities.size());
		
		util::AssignBitsetIndexWithAutoResize(_activatedEntities, entity->getId(), isActivated);
	}
	
	bool EntityContainer::isActivated(ConstEntityPtr e) const
	{
		assert(e != NULL);
		
		if(_activatedEntities.size() <= e->getId()) return false; // bounds check
		return _activatedEntities[e->getId()];
	}
	
	bool EntityContainer::contains(ConstEntityPtr e) const
	{
		return contains(e->getId());
	}
	
	bool EntityContainer::contains(EntityId entityId) const
	{
		return (entityId < _registeredEntities.size()) && (_registeredEntities[entityId] != NULL);
	}
	
	EntityPtr EntityContainer::getEntity(EntityId id)
	{
		assert(id < _registeredEntities.size());
		return _registeredEntities[id].get();
	}
	
	void EntityContainer::clear()
	{
		_registeredEntities.clear();
		_activatedEntities.clear();
	}
}