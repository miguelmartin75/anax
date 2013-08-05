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

#include <anax/detail/EntityIdPool.hpp>

namespace anax
{
	namespace detail
	{
		EntityIdPool::EntityIdPool(std::size_t poolSize)
			: _entities(poolSize),
		      _nextId(0)
		{
		}
		
		Entity::Id EntityIdPool::create()
		{
			Entity::Id id;
			
			// if we need to add more entities to the pool
			if(!_freeList.empty())
			{
				id = _freeList.front();
				_freeList.pop_back();
			}
			else
			{
				id.index = _nextId++;
			}
			
			return id;
		}
		
		void EntityIdPool::remove(Entity::Id id)
		{
			++_entities[id.index].counter; // increment the counter in the cache
			_freeList.push_back(id); // add the ID to the freeList
		}
		
		Entity::Id EntityIdPool::get(std::size_t index) const
		{
			return _entities[index];
		}
		
		bool EntityIdPool::isValid(Entity::Id id) const
		{
			return id.counter == _entities[id.index].counter;
		}
		
		void EntityIdPool::resize(std::size_t amount)
		{
			_entities.resize(amount);
		}
	}
}