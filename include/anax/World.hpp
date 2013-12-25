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

#ifndef __ANAX_WORLD_HPP__
#define __ANAX_WORLD_HPP__

#include <vector>
#include <unordered_map>
#include <type_traits>

#include <boost/dynamic_bitset.hpp>

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
        
		/// Describes an array of Systems for storage within the world
		/// The index is the type ID of the system,
		/// thus systems of the same type can not be stored
		/// in the same World object.
		typedef std::unordered_map<detail::TypeId, BaseSystem*> SystemArray;
		
	public:
		
		/// Describes an array of Entities
		typedef std::vector<Entity> EntityArray;
         
		static const std::size_t DEFAULT_ENTITY_POOL_SIZE = 1000;
		
		/// Default Constructor
		World();
		
		/// Constructs the world with a custom entity pool size
		/// \param entityPoolSize The amount of entities you wish to have pooled ready to use by default
		World(std::size_t entityPoolSize);
		
		World(const World& world) = delete;
		World(World&& world) = delete;
		World& operator=(const World&) = delete;
		World& operator=(World&&) = delete;
		
		
		/// Adds a system to the World
		/// \tparam TSystem The type of system you wish to add
		/// \param system The system you wish to add
		template <typename TSystem>
		void addSystem(TSystem& system)
        { static_assert(std::is_base_of<BaseSystem, TSystem>(), "Template argument does not inherit from BaseSystem"); addSystem(system, TSystem::GetTypeId()); }
		
		/// Removes a system from the World
		/// \tparam TSystem The type of system you wish to remove
		template <typename TSystem>
		void removeSystem() 
        { static_assert(std::is_base_of<BaseSystem, TSystem>(), "Template argument does not inherit from BaseSystem"); removeSystem(TSystem::GetTypeId()); }
		
		/// Removes all the systems from the world
		void removeAllSystems();
		
		/// Creates an Entity
		/// \return A new entity for which you can use.
		Entity createEntity();
		
		/// Creates a specific amount of entities
		/// \param amount The amount of entities you wish to create
		/// \return The entities you created
		EntityArray createEntities(std::size_t amount);
		
		/// Kills and decativates an Entity
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

        /// Instantiously clears the world, by removing
        /// all systems and entities from the world.
        void clear();

		/// \return The amount of entities that are alive (attached to the world)
		/// \note This count includes the deactivated entities
		std::size_t getEntityCount() const;
		
        /// \return All the entities within the world
        const EntityArray& getEntities() const;
        
	private:
		
		/// Systems attached with the world.
		SystemArray _systems;
		
		/// A pool storage of the IDs for the entities within the world
		detail::EntityIdPool _entityIdPool;
		
		struct EntityAttributes
		{
			EntityAttributes(std::size_t amountOfEntities)
                : componentStorage(amountOfEntities), 
                  activated(amountOfEntities)
            {
            }
			
			/// A storage of all components that an entity has
			detail::EntityComponentStorage componentStorage;
			
			/// A bitset of activated entities
            /// Used to determine whether an entity is activated or not
			boost::dynamic_bitset<> activated;
			
            /// Used on resize to allow room
            /// for more entities that require to be allocated
            /// \param amountOfEntities The amount of entities to resize for
			void resize(std::size_t amountOfEntities) 
            { 
                componentStorage.resize(amountOfEntities); 
                activated.resize(amountOfEntities);
            }

            /// Clears the attributes for all entities
            void clear()
            {
                componentStorage.clear();
                activated.clear();
            }
		}
		
		/// The attributes of the entities attached to this world
		_entityAttributes;
		
		
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
		_entityCache;
		
		
		void checkForResize(std::size_t amountOfEntitiesToBeAllocated);
		void resize(std::size_t amount);
		
		void addSystem(BaseSystem& system, detail::TypeId systemTypeId);
		void removeSystem(detail::TypeId systemTypeId);		
		
		
		// to access components
		friend class Entity;
	};
}

#endif // __ANAX_WORLD_HPP__
