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

#ifndef __ANAX_ENTITYCONTAINER_H__
#define __ANAX_ENTITYCONTAINER_H__

// TODO: remove

#include <vector>
#include <memory>

#include "anax/IdentifierPool.h"
#include "anax/Entity.h"

namespace anax
{
	class World;
	
	/// \class EntityContainer
	/// \brief A specialized container that it used to contain Entity objects attached to the same Scene
	///
	/// This class contains multiple entities and contains information relative to an Entity
	/// You may enable or disable them and determine whether one is alive or not.
	///
	/// \author Miguel Martin
	class EntityContainer
	{
		friend class World;
		
		typedef std::unique_ptr<Entity> SmartEntityPtr;
		typedef std::vector<SmartEntityPtr> ImplEntityArray;
		
	public:
		
		typedef ImplEntityArray::const_iterator iterator;
		typedef ImplEntityArray::const_reverse_iterator reverse_iterator;
		typedef ImplEntityArray::const_iterator const_iterator;
		typedef ImplEntityArray::const_reverse_iterator const_reverse_iterator;
		typedef ImplEntityArray::value_type value_type;
		typedef ImplEntityArray::const_reference reference;
		typedef ImplEntityArray::const_reference const_reference;
		typedef ImplEntityArray::const_pointer pointer;
		typedef ImplEntityArray::const_pointer const_pointer;
		typedef ImplEntityArray::size_type size_type;
		
		
		/// Default constructor
		EntityContainer();
		
		/// Destructor
		~EntityContainer();
		
		
		
		/// Inserts an Entity to the EntityContainer
		/// \param entity The Entity you wish to add
		void insert(EntityPtr entity);
		
		/// Erases an Entity
		/// \param entity The Entity you wish to remove
		void erase(EntityPtr entity) { erase(entity->getId()); }
		
		/// Erases an Entity
		/// \param entityId The ID of the Entity you wish to erase
		void erase(EntityId entityId);
		
		/// Determines whether an Entity does exist
		/// within this EntityContainer object
		/// \param e The Entity you wish to check for
		/// \return true if the EntityContainer contains the Entity
		bool contains(ConstEntityPtr e) const;
		
		/// Determines whether an Entity does exist
		/// within this EntityContainer object
		/// \param entityId The Entity's ID that you wish to check for
		/// \return true if the Entity does exist, false otherwise
		bool contains(EntityId entityId) const;
		
		/// Retrieves an Entity via an ID
		/// \param id The ID of the Entity
		/// \return The Entity that you requested, or NULL if the Entity does not exist
		EntityPtr getEntity(EntityId id);
		
		/// Clears the EntityContainer
		void clear();
		
		iterator begin()						{ return _registeredEntities.begin(); }
		const_iterator begin() const			{ return _registeredEntities.begin(); }
		
		iterator end()							{ return _registeredEntities.end(); }
		const_iterator end() const				{ return _registeredEntities.end(); }
		
		reverse_iterator rbegin()				{ return _registeredEntities.rbegin(); }
		const_reverse_iterator rbegin() const	{ return _registeredEntities.rbegin(); }
		
		reverse_iterator rend()					{ return _registeredEntities.rend(); }
		const_reverse_iterator rend() const		{ return _registeredEntities.rend(); }
		
		size_type size() const { return _registeredEntities.size(); }
		
		void resize(size_type n) { _registeredEntities.resize(n); }
		
		
		/// Activates an Entity
		/// \param entity The Entity you wish to activate
		void activate(EntityPtr entity);
		
		/// Deactivates an Entity
		/// \param entity The Entity you wish to deactivate
		void deactivate(EntityPtr entity);
		
		/// Sets the flag to determine whether an Entity is enabled or not
		/// \param entity The Entity you wish to set the isEnabled flag on
		/// \param isEnabled true if you wish to disable the Entity,
		///				     false if you wish to enable it
		void setIsActivated(EntityPtr entity, bool isActivated);
		
		/// Determines whether an Entity is enabled
		/// \param e The Entity you wish to check for
		/// \return true if the Entity is activated, false if it is not
		bool isActivated(ConstEntityPtr e) const;
		
	private:
		
		/// Contains all the entities that are registered in the manager
		ImplEntityArray _registeredEntities;
		
		/// The activated Entities within the container
		DynamicBitSet _activatedEntities;
		
		/// The object that assigns IDs to Entity objects
		IdentifierPool<EntityId> _idPool;
		
		
		
		// Prevent from copying; purposely not defined
		EntityContainer(const EntityContainer&);
		const EntityContainer& operator=(const EntityContainer&);
	};
}

#endif // __AC_ES_ENTITYCONTAINER_H__