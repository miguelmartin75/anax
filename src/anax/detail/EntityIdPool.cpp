///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)
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
        EntityIdPool::EntityIdPool(std::size_t poolSize) : 
            m_defaultPoolSize(poolSize),
            m_nextId(0),
            m_entities(poolSize)
        {
        }

        Entity::Id EntityIdPool::create()
        {
            Entity::Id id;

            // if we need to add more entities to the pool
            if(!m_freeList.empty())
            {
                id = m_freeList.back();
                m_freeList.pop_back();

                // Update the ID counter before issuing
                //id.counter = m_entities[id.index];
            }
            else
            {
                id.index = m_nextId++;
                // an ID given out cannot have a counter of 0. 
                // 0 is an "invalid" counter, thus we must update
                // the counter within the pool for the corresponding
                // entity
                m_entities[id.index] = id.counter = 1; 
            }

            return id;
        }

        void EntityIdPool::remove(Entity::Id id)
        {
            auto& counter = m_entities[id.index];
            ++counter; // increment the counter in the cache
            m_freeList.emplace_back(static_cast<Entity::Id::int_type>(id.index), counter); // add the ID to the freeList
        }

        Entity::Id EntityIdPool::get(std::size_t index) const
        {
            assert(!(m_entities[index] == 0) && "Entity ID does not exist");
            return Entity::Id{index, m_entities[index]};
        }

        bool EntityIdPool::isValid(Entity::Id id) const
        {
            return id.counter == m_entities[id.index];
        }

        std::size_t EntityIdPool::getSize() const
        {
            return m_entities.size(); 
        }

        void EntityIdPool::resize(std::size_t amount)
        {
            m_entities.resize(amount);
        }

        void EntityIdPool::clear()
        {
            m_entities.clear();
            m_freeList.clear();
            m_nextId = 0;

            m_entities.resize(m_defaultPoolSize);
        }
    }
}
