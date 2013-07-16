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

#ifndef __ANAX_WORLD_H__
#define __ANAX_WORLD_H__

#include <vector>
#include <unordered_map>

#include "Component.hpp"
#include "Entity.hpp"
#include "System.hpp"

namespace anax
{
	class World
	{
	public:
		
		World();
		
		/// Creates an Entity
		/// \return A new entity for which you can use.
		Entity createEntity();
		
		/// Kills an Entity
		/// \param entity The Entity you wish to kill
		void killEntity(Entity& entity);
		
		/// Determines if an Entity is valid.
		/// \note If the entity is valid it may have components attached to it.
		/// If the entity is not valid and a component is attempted to be attached
		/// to the entity, there will be a run-time error (an assertion).
		/// \return true if the Entity is valid within the World
		bool isValid(const Entity& entity) const;
		
		/// Refreshes the World
		void refresh();
		
	private:
		
		class EntityIdPool
		{
		public:
			
			/// Creates an Entity ID
			/// \return The newly created Entity ID
			Entity::Id create();
			
			/// Removes an ID from the pool
			/// \param id The ID you wish to remove
			void remove(Entity::Id id);
			
			/// \param The index you wish to access the Entity::Id at
			/// \return An Entity::Id at index
			Entity::Id get(std::size_t index) const;
			
			/// Determines if an Entity ID is valid
			/// \return true if the ID is valid
			bool isValid(Entity::Id id) const;
			
		private:
			
			/// The entities ids that are avaliable to be used 
			std::vector<Entity::Id> _freeList;
			
			/// The Entities that are within the pool
			std::vector<Entity::Id> _entities;
		} _entityIdPool;
		
		class EntityAttributes
		{
			
		} _entityAttributes;
		
		std::vector<BaseSystem*> _systems;
	};
}

#endif // __ANAX_WORLD_H__
