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

#ifndef __ANAX_ENTITYSYSTEM_H__
#define __ANAX_ENTITYSYSTEM_H__

#include <vector>

#include "anax/Identifiable.h"
#include "anax/ComponentFilter.h"
#include "anax/Entity.h"

namespace anax
{
	class World;
	
	/// \class EntitySystem
	/// \brief An abstract class that describes a system in the Entity System
	///
	/// A system in a typical Entity System describes the logic of how entities with specific components
	/// are used within a Scene. An example EntitySystem would be a MovementSystem, where Entity objects with
	/// position and velocity components would be processed.
	///
	/// \author Miguel Martin
	class BaseEntitySystem
	{
		friend class World;
		
		ANAX_IDENTIFIABLE_BASE(BaseEntitySystem) // TODO: remove
		
	public:
		
		/// Default Constructor
		BaseEntitySystem();
		
		/// Constructs an EntitySystem
		/// \param componentFilter The ComponentFilter you wish to construct the EntitySystem with
		BaseEntitySystem(const ComponentFilter& componentFilter);
		
		/// Destructor
		virtual ~BaseEntitySystem() = 0;
		
		
		
		/// Determines whether the EntitySystem contains an Entity
		/// \param e The Entity you wish to check for
		/// \return true if the EntitySystem does
		bool contains(ConstEntityPtr e) const;
		
		/// Determines whether the EntitySystem is interested in an Entity
		/// \return true if it is, false otherwise
		bool isInterested(ConstEntityPtr e) const;
		
		/// Enables the EntitySystem
		void enable() { setIsEnabled(true); }
		
		/// Disables the EntitySystem
		void disable() { setIsEnabled(false); }
		
		/// Sets the isEnabled flag
		/// \param value The value which you wish to have
		void setIsEnabled(bool value) { _isEnabled = value; }
		
		/// \return true if the EntitySystem is enabled, false otherwise
		bool isEnabled() const { return _isEnabled; }
		
		/// Sets the isPassive flag, which determines whether the EntitySystem will get updated
		/// inside an EntitySystemContainer class.
		/// \param value true if you wish to update the EntitySystem youself, false if you wish
		///				 the EntitySystem to udpate itself
		void setIsPassive(bool value) { _isPassive = value; }
		
		/// \return true if the EntitySystemContainer will update this EntitySystem
		bool isPassive() const { return _isPassive; }
		
		/// \return The entities to process
		const EntityArray& getEntitiesToProcess() const	{ return _entitiesToProcess; }
		
		/// Sets the ComponentFilter that the EntitySystem will have
		/// \param componentFilter The filter you wish to apply to the Entitysystem
		void setComponentFilter(const ComponentFilter& componentFilter) { _componentFilter = componentFilter; }
		
		/// \return The ComponentFilter that is applied to the EntitySystem
		const ComponentFilter& getComponentFilter() const				{ return _componentFilter; }
		
	private:
		
		/// TODO:
		/// Remove the following:
		/// 1. isPassive
		/// 2. isEnabled
		/// 3. 
		
		/// Initializes the EntitySystem
		virtual void initialize() {}
		
		/// An event that occurs when an Entity is added to the EntitySystem
		virtual void onEntityAdded(EntityPtr e) {}
		
		/// An event that occurs when an Entity is removed from the EntitySystem
		/// \param entity The Entity that is removed from the system
		virtual void onEntityRemoved(EntityPtr e) {}
		
		
		
		/// Checks if the Entity is viable to be added to the EntitySystem
		/// If it is, then it will be added to the EntitySystem
		void check(EntityPtr e);
		
		/// Inserts an Entity to the EntitySystem
		/// \param e The Entity you wish to insert
		void insert(EntityPtr e);
		
		/// Removes an Entity from the EntitySystem
		/// \param e The Entity you wish to remove
		void remove(EntityPtr e);
		
		/// An event that occurs when an Entity is removed from a Scene
		/// \param e The Entity that is removed from the Scene
		void onRemovedFromScene(EntityPtr e);
		
		
		
		/// Determines whether the EntitySystem will be automatically updated
		/// within an EntitySystemContainer
		bool _isPassive;
		
		/// Determines whether the EntitySystem is enabled or not
		bool _isEnabled;
		
		/// The object that is used to help filter out Component objects
		ComponentFilter _componentFilter;
		
		/// Contains all the entities to process
		EntityArray _entitiesToProcess;
		
		
		
		// Prevent from copying; purposely not defined
		BaseEntitySystem(const BaseEntitySystem&);
		BaseEntitySystem& operator=(const BaseEntitySystem&);
	};
	
	
	template <typename T>
	class EntitySystem
		: public BaseEntitySystem
	{
		ANAX_IDENTIFIABLE(EntitySystem)
		
	public:
		
		typedef EntitySystem<T> Base;
		
		
		/// Default Constructor
		EntitySystem()
		{
		}
		
		/// Constructs an EntitySystem
		/// \param componentFilter The ComponentFilter you wish to construct the EntitySystem with
		EntitySystem(const ComponentFilter& componentFilter)
			: BaseEntitySystem(componentFilter)
		{
		}
		
		virtual ~EntitySystem() = 0;
	};
	
	template <typename T>
	EntitySystem<T>::~EntitySystem() {}
	
	/// Used for readability
	typedef BaseEntitySystem::Class EntitySystemType;
}

#endif // __ANAX_ENTITYSYSTEM_H__