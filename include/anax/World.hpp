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

#ifndef __ANAX_WORLD_HPP__
#define __ANAX_WORLD_HPP__

#include <vector>
#include <unordered_map>

#include "detail/EntityIdPool.hpp"
#include "detail/EntityAttributes.hpp"

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
		
		/// Kills and decativates an Entity
		/// \param entity The Entity you wish to kill
		void killEntity(Entity& entity);
		
		/// Activates an Entity
		/// \param entity The Entity you wish to activate
		void activateEntity(Entity& entity);
		
		/// Deactivates an Entity
		/// \param entity The Entity you wish to deactivate
		void deactivateEntity(Entity& entity);
		
		/// 
		bool isActivated(Entity& entity);
		
		/// Determines if an Entity is valid.
		/// \note If the entity is valid it may have components attached to it.
		/// If the entity is not valid and a component is attempted to be attached
		/// to the entity, there will be a run-time error (an assertion).
		/// \return true if the Entity is valid within the World
		bool isValid(const Entity& entity) const;
		
		/// Refreshes the World
		void refresh();
		
	private:
		
		/// Describes an array of Systems for storage within the world
		/// The index is the type ID of the system,
		/// thus systems of the same type can not be stored
		/// in the same World object.
		typedef std::unordered_map<detail::TypeId, BaseSystem*> SystemArray;
		
		/// Describes an array of Entities
		typedef std::vector<Entity> EntityArray;
		
		
		
		/// A pool storage of the IDs for the entities within the world
		detail::EntityIdPool _entityIdPool;
		
		/// The attributes of the entities attached to this world
		detail::EntityAttributes _entityAttributes;
		
		/// Systems attached with the world.
		SystemArray _systems;
		
		/// The killed entities for the world
		EntityArray _killedEntities;
		
		/// Temporary storage for activated entities within the World
		EntityArray _activatedEntities;
		
		/// Temporary storage for the deactivate entities within the World
		EntityArray _deactivatedEntities;
	};
}

#endif // __ANAX_WORLD_HPP__
