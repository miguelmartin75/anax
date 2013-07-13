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

#ifndef __ANAX_WORLD_H__
#define __ANAX_WORLD_H__

#include <vector>

#include "Component.h"
#include "Entity.h"
#include "System.h"

namespace anax
{
	class World
	{
	public:
		
		World()
		{
		}
		
		Entity createEntity()
		{
			return Entity(*this, _entityIdPool.create());
		}
		
		void killEntity(Entity& entity)
		{
			// todo:
			// delay the deletion of an entity
			_entityIdPool.remove(entity.getId());
		}
		
		bool isValid(const Entity& entity) const
		{
			return _entityIdPool.isValid(entity.getId());
		}
		
		/// Refreshes the World
		void refresh();
		
	private:
		
		
		class EntityIdPool
		{
		public:
			
			bool isValid(Entity::Id id) const
			{
				return id.counter == _entities[id.index].counter;
			}
			
			Entity::Id create()
			{
				Entity::Id id;
				
				// if we need to add more entities to the pool
				if(_freeList.empty())
				{
					// create a new entity, and assign it the new index
					id.index = _entities.size();
					id.counter = 1; // start it off with an initial counter of 1 reference
					_entities.emplace_back(id);
					
					return id;
				}
				
				id = _freeList.front();
				_freeList.pop_back();
				
				return id;
			}
			
			void remove(Entity::Id id)
			{
				++_entities[id.index].counter; // increment the counter in the cache
				_freeList.push_back(id); // add the ID to the freeList
			}
			
			Entity::Id get(std::size_t index) const
			{
				return _entities[index];
			}
			
		private:
			
			std::vector<Entity::Id> _freeList;
			std::vector<Entity::Id> _entities;
		};
		
		EntityIdPool _entityIdPool;
	};
}

#endif // __ANAX_WORLD_H__
