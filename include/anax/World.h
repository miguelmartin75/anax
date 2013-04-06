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


#ifndef __ANAX_SCENE_H__
#define __ANAX_SCENE_H__

#include <vector>

#include "EntityFactory.h"
#include "ComponentStorage.h"
#include "EntityContainer.h"
#include "EntitySystemContainer.h"


namespace anax
{
	/// \brief The World class; contains entities and systems
	///
	/// The World class
	///
	///
	/// \author Miguel Martin
	class World
	{
		friend class EntityFactory;
		
	public:
		
		/// Default Constructor
		World();
		
		/// Destructor
		~World();
		
		/// Updates the World
		/// \note
		/// Call this BEFORE using your systems attached to the World
		void update();
		
		/// Clears the World
		void clear();
		
		/// Creates an Entity and adds it automatically to the Scene
		/// \return A created Entity, for you to freely use
		/// \note You should store the return value in a variable, unless you want the Entity to do nothing,
		/// which doesn't really make any sense.
		/// TODO: Remove
		EntityPtr createEntity();
		
		/// Inserts an Entity to the Scene
		/// \param entity The Entity you wish to add to the Scene
		void addEntity(EntityPtr entity);
		
		/// Destroys an Entity
		/// \param entity The Entity you wish to destroy
		/// \note
		/// The Entity will be deleted from memory after
		/// the next call to update(), or clean()
		void removeEntity(EntityPtr entity);
		
		/// Acitvates an Entity. Call this method if you change your Entity.
		/// \param entity The Entity you wish to add
		void activateEntity(EntityPtr entity);
		
		/// Deactivates an Entity. Call this method if you wish to make sure an
		/// Entity does not get processed by an EntitySystem.
		/// \param entity The Entity you wish to deactivate
		void deactivateEntity(EntityPtr entity);
		
		/// Determines whether an Entity is activated
		/// \return true if it is, false otherwise
		bool isEntityActivated(ConstEntityPtr entity) const;
		
		/// Determines if an Entity is alive
		///	(i.e. if destroyEntity(EntityPtr) has not been called
		/// \param entityId The Entity'd Id you wish to check for
		/// \return true if the Entity is alive, false otherwise
		bool isEntityAlive(EntityId entityId) const;
		
		/// Determines if an Entity is alive
		///	(i.e. if destroyEntity(EntityPtr) has not been called
		/// \param entity The Entity you wish to check for
		/// \return true if the Entity is alive, false otherwise
		bool isEntityAlive(ConstEntityPtr entity) const { return isEntityAlive(entity->getId()); }
		
		/// Inserts an EntitySytem to the Scene
		/// \tparam T Must be derived from the EntitySystem class
		/// \param entitySystem The EntitySystem you wish to insert
		/// \note The EntitySystem will BELONG to the Scene, and therefore
		/// if a Scene is destructed, the EntitySystems in the Scene will also be destructed
		void addEntitySystem(EntitySystemPtr entitySystem)
		{
			_entitySystemContainer.insert(entitySystem);
		}
		
		/// Erases an EntitySystem from the Scene
		/// \tparam T Must be derived from the EntitySystem class
		template <typename T>
		void removeEntitySystem()
		{
			_entitySystemContainer.erase<T>();
		}
		
		/// Erases an EntitySystem from the Scene
		/// \tparam T Must be derived from the EntitySystem class
		/// \param entitySystem The EntitySystem you wish to erase from the Scene
		template <typename T>
		void removeEntitySystem(T* entitySystem)
		{
			_entitySystemContainer.erase(entitySystem);
		}
		
		/// Determines if the Scene contains an EntitySystem
		/// \tparam T Must be derived from the EntitySystem class
		/// \return true if the Scene does contain the EntitySystem, false otherwise
		template <typename T>
		bool containsEntitySystem() const
		{
			return _entitySystemContainer.contains<T>();
		}
		
		/// Determines if the Scene contains an EntitySystem
		/// \tparam T Must be derived from the EntitySystem class
		/// \param entitySystem The EntitySystem you wish to check for
		/// \return true if the Scene does contain the EntitySystem, false otherwise
		template <typename T>
		bool containsEntitySystem(T* entitySystem) const
		{
			return _entitySystemContainer.contains<T>(entitySystem);
		}
		
		/// \return The EntityContainer object that is connected with the Scene
		const EntityContainer& getEntityContainer() const				{ return _entityContainer; }
		
		/// \return The EntitySystemContainer object that contains all EntitySystem objects within the Scene
		const EntitySystemContainer& getEntitySystemContainer() const	{ return _entitySystemContainer; }
		
		/// \return The EntityFactory attached to the Scene
		const EntityFactory& getEntityFactory() const					{ return _entityFactory; }
		
		/// \return The anax::World that is attached to the Scene
		ComponentStorage& getComponentStorage()						{ return _componentStorage; }
		const ComponentStorage& getComponentStorage() const			{ return _componentStorage; }
		
	private:
		
		// UTILITY FUNCTIONS
		
		/// Cleans the World from any build-up cache, this method
		/// should be used when you wish to make sure that all
		/// Entity objects within the Scene have been succesfully
		/// destroyed and so on.
		void clean();
		
		/// Processes the Entity objects that have been activated
		void processActivatedEntityCache();
		
		/// Processes the Entity objects that have been deactivated
		void processDeactivatedEntityCache();
		
		/// Processes the Entity objects that have been added to the Scene
		void processAddedEntityCache();
		
		/// Processes the Entity objects that have been removed from the Scene
		void processRemovedEntityCache();
		
		/// Clears all the Entity cache(s) in the Scene
		void clearEntityCache();
		
		
		
		/// The class that creates Entity objects within the Scene
		EntityFactory _entityFactory;
		
		/// The object that contains all the Entity objects within the Scene
		EntityContainer _entityContainer;
		
		/// The object that contains all Component objects for Entity
		/// objects within the Scene
		ComponentStorage _componentStorage;
		
		/// The object that contains all the EntitySystems within the Scene
		EntitySystemContainer _entitySystemContainer;
		
		// CACHE
		
		/// Holds Entity objects that have been activated
		EntityArray _entityActivatedCache;
		
		/// Holds Entity objects that have been deactivated
		EntityArray _entityDeactivatedCache;
		
		/// Holds Entity objects that have been added to the Scene
		EntityArray _entityAddedCache;
		
		/// Holds Entity objects that have been removed from the Scene
		EntityArray _entityRemovedCache;
		
		
		
		
		// Prevent from copying; purposely not defined
		World(const World&);
		const World& operator=(const World&);
	};
}

#endif // __ANAX_SCENE_H__