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

#include <anax/World.hpp>
#include <anax/config.hpp>

#include <cassert>


namespace anax
{
    void World::SystemDeleter::operator() (BaseSystem* system) const
    {
        system->_world = nullptr;
        system->_entities.clear();
    }

    World::World()
        : World(DEFAULT_ENTITY_POOL_SIZE)
    {
    }

    World::World(std::size_t entityPoolSize)
        : _entityIdPool(entityPoolSize),
        _entityAttributes(entityPoolSize)
    {
    }

    void World::removeAllSystems()
    {
        _systems.clear();
    }

    Entity World::createEntity()
    {
        checkForResize(1);

        _entityCache.alive.emplace_back(*this, _entityIdPool.create());
        return _entityCache.alive.back();
    }

    std::vector<Entity> World::createEntities(std::size_t amount)
    {
        std::vector<Entity> temp;
        temp.reserve(amount);

        checkForResize(amount);

        for(decltype(amount) i = 0; i < amount; ++i)
        {
            Entity e{*this, _entityIdPool.create()};
            _entityCache.alive.push_back(e);
            temp.push_back(e);
        }

        return temp;
    }

    void World::killEntity(Entity& entity)
    {
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
            // remove the entity from the alive array
            _entityCache.alive.erase(std::remove(_entityCache.alive.begin(), _entityCache.alive.end(), i), _entityCache.alive.end()); 

            // destroy all the components it has
            _entityAttributes.componentStorage.removeAllComponents(i);

            // remove it from the id pool
            _entityIdPool.remove(i.getId());
        }

        // clear the temp cache
        _entityCache.clearTemp();
    }

    void World::clear()
    {
        removeAllSystems(); // remove the systems

        // clear the attributes for all the entities
        _entityAttributes.clear();

        // clear the entity cache
        _entityCache.clear();

        // clear the id pool
        _entityIdPool.clear();
    }

    std::size_t World::getEntityCount() const
    {
        return _entityCache.alive.size();
    }

    const World::EntityArray& World::getEntities() const
    {
        return _entityCache.alive;
    }

    void World::checkForResize(std::size_t amountOfEntitiesToBeAllocated)
    {
        auto newSize = getEntityCount() + amountOfEntitiesToBeAllocated;
        if(newSize > _entityIdPool.getSize())
        {
            resize(newSize);
        }
    }

    void World::resize(std::size_t amount)
    {
        _entityIdPool.resize(amount);
        _entityAttributes.resize(amount);
    }

    void World::addSystem(BaseSystem& system, detail::TypeId systemTypeId)
    {
        assert(!system._world && "System is already contained within a World");

        _systems[systemTypeId].reset(&system);

        system._world = this;
        system.initialize();
    }

    void World::removeSystem(detail::TypeId systemTypeId)
    {
        assert(doesSystemExist(systemTypeId) && "System does not exist in world");
        _systems.erase(systemTypeId);
    }

    bool World::doesSystemExist(detail::TypeId systemTypeId) const
    {
        return _systems.find(systemTypeId) != _systems.end();
    }

    Entity World::getEntity(std::size_t index)
    {
        return Entity{*this, _entityIdPool.get(index)};
    }
}
