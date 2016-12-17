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

#include <anax/World.hpp>

#include <algorithm>

#include <anax/Config.hpp>

#include <anax/detail/AnaxAssert.hpp>
#include <anax/util/ContainerUtils.hpp>

namespace anax
{
    void World::SystemDeleter::operator() (detail::BaseSystem* system) const
    {
        system->m_world = nullptr;
        system->m_entities.clear();
    }

    World::World() : 
        World(DEFAULT_ENTITY_POOL_SIZE)
    {
    }

    World::World(std::size_t entityPoolSize) : 
        m_entityIdPool(entityPoolSize),
        m_entityAttributes(entityPoolSize)
    {
    }

    void World::removeAllSystems()
    {
        m_systems.clear();
    }

    Entity World::createEntity()
    {
        checkForResize(1);

        m_entityCache.alive.emplace_back(*this, m_entityIdPool.create());
        return m_entityCache.alive.back();
    }

    std::vector<Entity> World::createEntities(std::size_t amount)
    {
        std::vector<Entity> temp;
        temp.reserve(amount);

        checkForResize(amount);

        for(decltype(amount) i = 0; i < amount; ++i)
        {
            Entity e{*this, m_entityIdPool.create()};
            m_entityCache.alive.push_back(e);
            temp.push_back(e);
        }

        return temp;
    }

    void World::killEntity(Entity& entity)
    {
        // deactivate the entity
        deactivateEntity(entity);

        // now kill the entity (add it to the killed cache)
        m_entityCache.killed.push_back(entity);
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
        ANAX_ASSERT(isValid(entity), "invalid entity tried to be activated");

        m_entityCache.activated.push_back(entity);
    }

    void World::deactivateEntity(Entity& entity)
    {
        ANAX_ASSERT(isValid(entity), "invalid entity tried to be deactivated");

        m_entityCache.deactivated.push_back(entity);
    }

    bool World::isActivated(const Entity& entity) const
    {
        if(isValid(entity))
            return m_entityAttributes.attributes[entity.getId().index].activated;
        else
            return false;
    }

    bool World::isValid(const anax::Entity &entity) const
    {
        return m_entityIdPool.isValid(entity.getId());
    }

    void World::refresh()
    {
        // go through all the activated entities from last call to refresh
        for(auto& entity : m_entityCache.activated)
        {
            auto& attribute = m_entityAttributes.attributes[entity.getId().index]; 
            attribute.activated = true;

            // loop through all the systems within the world
            for(auto& i : m_systems)
            {
                auto systemIndex = i.first;

                // if the entity passes the filter the system has and is not already part of the system
                if(i.second->getFilter().doesPassFilter(m_entityAttributes.componentStorage.getComponentTypeList(entity)))
                {
                    if(attribute.systems.size() <= systemIndex || !attribute.systems[systemIndex])
                    {
                        i.second->add(entity); // add it to the system

                        util::EnsureCapacity(attribute.systems, systemIndex); 
                        attribute.systems[systemIndex] = true;
                    }
                }
                // otherwise if the entity is within the system 
                // and is not relevant to the system anymore...
                // note: the entity has already failed the filter
                else if(attribute.systems.size() > systemIndex && attribute.systems[systemIndex])
                {
                    // duplicate code (1)
                    i.second->remove(entity); 
                    attribute.systems[systemIndex] = false;
                }
            }
        }


        // go through all the deactivated entities from last call to refresh
        for(auto& entity : m_entityCache.deactivated)
        {
            auto& attribute = m_entityAttributes.attributes[entity.getId().index]; 
            attribute.activated = false;

            // loop through all the systems within the world
            for(auto& i : m_systems)
            {
                auto systemIndex = i.first;
                if(attribute.systems.size() <= systemIndex) continue;

                if(attribute.systems[systemIndex])
                {
                    // duplicate code ...(1)
                    i.second->remove(entity); 
                    attribute.systems[systemIndex] = false;
                }
            }
        }

        // go through all the killed entities from last call to refresh
        for(auto& entity : m_entityCache.killed)
        {
            // remove the entity from the alive array
            m_entityCache.alive.erase(std::remove(m_entityCache.alive.begin(), m_entityCache.alive.end(), entity), m_entityCache.alive.end()); 

            // destroy all the components it has
            m_entityAttributes.componentStorage.removeAllComponents(entity);

            // remove it from the id pool
            m_entityIdPool.remove(entity.getId());
        }

        // clear the temp cache
        m_entityCache.clearTemp();
    }

    void World::clear()
    {
        removeAllSystems(); // remove the systems

        // clear the attributes for all the entities
        m_entityAttributes.clear();

        // clear the entity cache
        m_entityCache.clear();

        // clear the id pool
        m_entityIdPool.clear();
    }

    std::size_t World::getEntityCount() const
    {
        return m_entityCache.alive.size();
    }

    const World::EntityArray& World::getEntities() const
    {
        return m_entityCache.alive;
    }

    void World::checkForResize(std::size_t amountOfEntitiesToBeAllocated)
    {
        auto newSize = getEntityCount() + amountOfEntitiesToBeAllocated;
        if(newSize > m_entityIdPool.getSize())
        {
            resize(newSize);
        }
    }

    void World::resize(std::size_t amount)
    {
        m_entityIdPool.resize(amount);
        m_entityAttributes.resize(amount);
    }

    void World::addSystem(detail::BaseSystem& system, detail::TypeId systemTypeId)
    {
        ANAX_ASSERT(!system.m_world, "System is already contained within a World");
        ANAX_ASSERT(m_systems.count(systemTypeId) == 0, "System of this type is already contained within the world");

        m_systems[systemTypeId].reset(&system);

        system.m_world = this;
        system.initialize();
    }

    void World::removeSystem(detail::TypeId systemTypeId)
    {
        ANAX_ASSERT(doesSystemExist(systemTypeId), "System does not exist in world");
        m_systems.erase(systemTypeId);
    }

    bool World::doesSystemExist(detail::TypeId systemTypeId) const
    {
        return m_systems.find(systemTypeId) != m_systems.end();
    }

    Entity World::getEntity(std::size_t index)
    {
        return Entity{*this, m_entityIdPool.get(index)};
    }
}
