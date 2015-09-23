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

#ifndef ANAX_WORLD_HPP
#define ANAX_WORLD_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include <type_traits>
#include <utility>

#include <anax/detail/EntityIdPool.hpp>
#include <anax/detail/EntityComponentStorage.hpp>

#include <anax/Component.hpp>
#include <anax/Entity.hpp>
#include <anax/System.hpp>

namespace anax
{
    class World
    {
    private:

        struct SystemDeleter
        {
            void operator() (detail::BaseSystem* system) const;
        };

        /// Describes an array of Systems for storage within the world
        /// The index is the type ID of the system,
        /// thus systems of the same type can not be stored
        /// in the same World object.
        using SystemArray = std::unordered_map<detail::TypeId, std::unique_ptr<detail::BaseSystem, SystemDeleter>>;

    public:

        /// Describes an array of Entities
        using EntityArray = std::vector<Entity>;

        /// Default Constructor
        World();

        /// Constructs the world with a custom entity pool size
        /// \param entityPoolSize The amount of entities you wish to have pooled ready to use by default
        explicit World(std::size_t entityPoolSize);

        World(const World& world) = delete;
        World(World&& world) = delete;
        World& operator=(const World&) = delete;
        World& operator=(World&&) = delete;


        /// Adds a system to the World
        /// \tparam TSystem The type of system you wish to add
        /// \param system The system you wish to add
        template <typename TSystem>
        void addSystem(TSystem& system);

        /// Removes a system from the World
        /// \tparam TSystem The type of system you wish to remove
        template <typename TSystem>
        void removeSystem();

        /// Determines whether a type of system is attached to a world
        /// \tparam TSystem The type of system you wish to check            
        template <typename TSystem>
        bool doesSystemExist() const;

        /// Determines if a specific system belongs to this world
        /// \tparam TSystem The type of system you wish to check            
        /// \param system The system you wish to check for
        /// \note This differs from doesSystemExist<TSystem>() as 
        /// doesSystemExist<TSystem>() cannot check whether the system
        /// object belongs to the same world as this.
        template <typename TSystem>
        bool doesSystemExist(const TSystem& system) const;

        /// Removes all the systems from the world
        void removeAllSystems();

        /// Creates an Entity
        /// \return A new entity for which you can use.
        Entity createEntity();

        /// Creates an entity and applies an entity template to the entity
        /// \tparam EntityTemplateFn The type of template function you wish to apply
        ///
        /// \param fn The function you wish to apply to this entity
        /// \param args The corresponding arguments to the entity template function
        template <typename EntityTemplateFn, typename... Args>
        Entity createEntity(EntityTemplateFn fn, Args&&... args)
        {
            Entity e = createEntity();
            fn(e, std::forward<Args>(args)...);
            return e;
        }

        /// Creates a specific amount of entities
        /// \param amount The amount of entities you wish to create
        /// \return The entities you created
        EntityArray createEntities(std::size_t amount);

        /// Kills and deactivates an Entity
        /// \param entity The Entity you wish to kill
        void killEntity(Entity& entity);

        /// Kills and deactivates an array of entities
        /// \param entities The entities you wish to kill
        void killEntities(std::vector<Entity>& entities);

        /// Activates an Entity
        /// \param entity The Entity you wish to activate
        void activateEntity(Entity& entity);

        /// Deactivates an Entity
        /// \param entity The Entity you wish to deactivate
        void deactivateEntity(Entity& entity);

        /// Determines if the Entity is activated
        /// \param entity The Entity you wish to check
        /// \return true if entity is activated
        bool isActivated(const Entity& entity) const;

        /// Determines if an Entity is valid.
        /// \note If the entity is valid it may have components attached to it.
        /// If the entity is not valid and a component is attempted to be attached
        /// to the entity, there will be a run-time error (an assertion).
        /// \return true if the Entity is valid within the World
        bool isValid(const Entity& entity) const;

        /// Refreshes the World
        void refresh();

        /// Instantaneously clears the world, by removing
        /// all systems and entities from the world.
        /// \note It is no guarantee that the entities from the world
        /// will be invalidated, as the counter of the entity may still be
        /// set to the same counter in the pool. However, it is expected
        /// that the entity will not have the same counter as long as you have not
        /// created another entity.
        void clear();

        /// \return The amount of entities that are alive (attached to the world)
        /// \note This count includes the deactivated entities
        std::size_t getEntityCount() const;

        /// \return All the entities within the world
        const EntityArray& getEntities() const;

        /// \return The entity with the associated index
        /// \note This will cause an assertion if it does not exist
        /// \note Is non-const because Entity requires a non-const reference
        /// to the world
        Entity getEntity(std::size_t index);

    private:

        /// Systems attached with the world.
        SystemArray m_systems;

        /// A pool storage of the IDs for the entities within the world
        detail::EntityIdPool m_entityIdPool;

        struct EntityAttributes
        {
            // todo: possibly move component storage to single attribute?
            // compare performance.
            struct Attribute
            {
                /// determines if the entity is activated
                bool activated;

                /// a bitset that resembles if the entity
                /// exists in a specific system.
                /// The index specifies what system, 0 resembles
                /// it is in the system, 1 is out of the system
                std::vector<bool> systems;
            };

            explicit EntityAttributes(std::size_t amountOfEntities) :     
                componentStorage(amountOfEntities), 
                attributes(amountOfEntities)
            {
            }

            /// A storage of all components that an entity has
            detail::EntityComponentStorage componentStorage;

            /// the attributes of each entity
            std::vector<Attribute> attributes;

            /// Used on resize to allow room
            /// for more entities that require to be allocated
            /// \param amountOfEntities The amount of entities to resize for
            void resize(std::size_t amountOfEntities) 
            { 
                componentStorage.resize(amountOfEntities); 
                attributes.resize(amountOfEntities);
            }

            /// Clears the attributes for all entities
            void clear()
            {
                componentStorage.clear();
                attributes.clear();
            }
        }

        /// The attributes of the entities attached to this world
        m_entityAttributes;


        struct EntityCache
        {
            /// Contains all the alive entities
            EntityArray alive;

            /// A temporary storage for the killed entities
            /// for the world. This array gets cleared every call
            /// to refresh.
            EntityArray killed;

            /// A temporary storage for the activated entities
            /// for the world. This array gets cleared every call
            /// to refresh.
            EntityArray activated;

            /// A temporary storage for the deactivated entities
            /// for the world. This array gets cleared every call
            /// to refresh.
            EntityArray deactivated;

            /// Clears the temporary cache
            void clearTemp()
            {
                killed.clear();
                activated.clear();
                deactivated.clear();
            }

            /// Clears everything in the cache
            void clear()
            {
                alive.clear();
                clearTemp();
            }
        }

        /// A cache of entities, which stores all
        /// types of entities (killed, alive, activated, etc.)
        /// within the World.
        m_entityCache;


        void checkForResize(std::size_t amountOfEntitiesToBeAllocated);
        void resize(std::size_t amount);

        void addSystem(detail::BaseSystem& system, detail::TypeId systemTypeId);
        void removeSystem(detail::TypeId systemTypeId);     
        bool doesSystemExist(detail::TypeId systemTypeId) const;

        // to access components
        friend class Entity;
    };

    template <class TSystem>
    void World::addSystem(TSystem& system)
    { 
        static_assert(std::is_base_of<detail::BaseSystem, TSystem>(), "Template argument does not inherit from BaseSystem"); 
        addSystem(system, SystemTypeId<TSystem>()); 
    }

    template <class TSystem>
    void World::removeSystem()
    {
        static_assert(std::is_base_of<detail::BaseSystem, TSystem>(), "Template argument does not inherit from BaseSystem"); 
        removeSystem(SystemTypeId<TSystem>());
    }

    template <class TSystem>
    bool World::doesSystemExist() const
    {
        static_assert(std::is_base_of<detail::BaseSystem, TSystem>(), "Template argument does not inherit from BaseSystem"); 
        return doesSystemExist(SystemTypeId<TSystem>());
    }

    template <class TSystem>
    bool World::doesSystemExist(const TSystem& system) const
    { 
        static_assert(std::is_base_of<detail::BaseSystem, TSystem>(), "Template argument does not inherit from BaseSystem"); 
        return system.m_world == this && doesSystemExist<TSystem>();
    }
}

#endif // ANAX_WORLD_HPP
