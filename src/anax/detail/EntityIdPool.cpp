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