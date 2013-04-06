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

#include "EntitySystem.h"

#include <cassert>

#include "anax/util/DynamicArrayUtils.h"


namespace anax
{
	BaseEntitySystem::BaseEntitySystem()
	: _isEnabled(true),
	_isPassive(false)
	{
	}
	
	BaseEntitySystem::BaseEntitySystem(const ComponentFilter& componentFilter)
	: _isEnabled(true),
	_isPassive(false),
	_componentFilter(componentFilter)
	{
		/* do nothing */
	}
	
	BaseEntitySystem::~BaseEntitySystem()
	{
		/* do nothing */
	}
	
	
	bool BaseEntitySystem::contains(ConstEntityPtr e) const
	{
		assert(e != NULL);
		
		EntitySystemType::Id BaseEntitySystemId = getClass().getId();
		return e->getSystemBits().size() > BaseEntitySystemId && e->getSystemBits()[BaseEntitySystemId];
	}
	
	bool BaseEntitySystem::isInterested(ConstEntityPtr e) const
	{
		// if then entity is NOT activated
		if(!e->isActivated())
			return false; // return false indicating we don't want it
		
		// if the REQUIRED bitset is not empty
		if(!_componentFilter.requiredComponentsBitSet.empty())
		{
			// loop through all the ComponentBits in the Entity
			DynamicBitSet::size_type index = _componentFilter.requiredComponentsBitSet.find_first();
			for(; index != DynamicBitSet::npos; index = _componentFilter.requiredComponentsBitSet.find_next(index))
			{
				// if the Entity doesn't contain the Component
				if(index >= e->getComponentBits().size() || e->getComponentBits()[index] == false)
				{
					return false;
				}
			}
		}
		
		// if the OPTIONAL bitset is not empty
		if(!_componentFilter.oneComponentBits.empty())
		{
			// if the Entity does not contain at least one of the components in the "one" bits
			if(!_componentFilter.oneComponentBits.intersects(e->getComponentBits()))
			{
				// we'll return false
				return false;
			}
		}
		
		// however if we got this far...
		// then...
		// check if the EXCLUDE bitset is not empty
		if(!_componentFilter.excludeComponentBitSet.empty())
		{
			// if there is AT LEAST one bit that interesects the excludeBitSet
			// then we shall set returnValue to false, indicating that it is NOT
			// interested in the Entity
			if(_componentFilter.excludeComponentBitSet.intersects(e->getComponentBits()))
			{
				return false;
			}
		}
		
		// otherwise, everything passed the test, so we will return true
		return true;
	}
	
	void BaseEntitySystem::check(EntityPtr e)
	{
		assert(e != NULL);
		
		bool doesContain = contains(e);
		bool isInterestedInEntity = isInterested(e);
		
		// If the BaseEntitySystem IS interested in the component
		// and DOES NOT contain the Entity already
		if (isInterestedInEntity && !doesContain)
		{
			// add it to the system
			insert(e);
		}
		// otherwise if the BaseEntitySystem isn't interested in the component
		// and it does contain the Entity, remove it.
		// i.e. this BaseEntitySystem no longer wants the Entity
		else if (!isInterestedInEntity && doesContain)
		{
			// remove it from the system
			remove(e);
		}
	}
	
	void BaseEntitySystem::insert(EntityPtr e)
	{
		assert(e != NULL);
		
		// add the entity to process
		_entitiesToProcess.push_back(e);
		
		// set the Entity's bit for this system
		util::AssignBitsetIndexWithAutoResize(e->_systemBits, getClass().getId(), true);
		
		onEntityAdded(e);
	}
	
	void BaseEntitySystem::remove(EntityPtr e)
	{
		EntityArray::iterator i = std::find(_entitiesToProcess.begin(), _entitiesToProcess.end(), e);
		
		// if the entity doesn't exist in the BaseEntitySystem
		if(i == _entitiesToProcess.end())
		{
			return;
		}
		
		// otherwise, if it does...
		
		_entitiesToProcess.erase(i); // erase it
		
		// assign the ES's bit for the Entity to false
		e->_systemBits[getClass().getId()] = false;
		
		onEntityAdded(e);
	}
	
	void BaseEntitySystem::onRemovedFromScene(EntityPtr e)
	{
		if(contains(e))
		{
			remove(e);
		}
	}
}