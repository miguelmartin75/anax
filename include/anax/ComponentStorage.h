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

#ifndef __ANAX_COMPONENTSTORAGE_H__
#define __ANAX_COMPONENTSTORAGE_H__

/// TODO:
/// - add component/system bits storage for entities
/// - rename to "EntityAttributes"

#include <vector>
#include <memory>

#include "anax/Types.h"
#include "anax/Component.h"

namespace anax
{
	class World;
	class Entity;
	class EntityFactory;
	
	/// \class ComponentStorage
	/// \brief Contains Components for various Entities
	///
	/// Holds Components for Entites that are added to it.
	/// It holds these Components efficently, for retrieval,
	/// addition and removal.
	///
	/// \author Miguel Martin
	class ComponentStorage
	{
		friend class World;
		friend class EntityFactory;
		
	public:
		
		/// Default Constructor
		ComponentStorage();
		
		/// Destructor
		~ComponentStorage();
		
		
		
		/// Adds a Component to an Entity
		/// \param e The Entity you wish to add the component to
		/// \param component The component you wish to add to the Entity
		/// \note
		/// An Entity may only have one TYPE of a component
		void addComponent(EntityPtr e, ComponentPtr component);
		
		/// Adds a Component to an Entity
		/// \param e The Entity you wish to add the component to
		/// \param component The component you wish to add to the Entity
		/// \param componentClassType The class type that the Component is
		/// \note
		/// An Entity may only have one TYPE of a component. This method
		/// is used for efficiency, depending if you know what the ComponentType is before
		/// you add it. If you DO know the type of component you are adding,
		/// use this method instead of the other method, it will be
		/// SLIGHTLY (no virtual function calls) faster.
		void addComponent(EntityPtr e, ComponentPtr component, const ComponentType& componentType);
		
		/// Destroys a Component from an Entity
		/// \param e The Entity you wish to remove the component from
		/// \param component The component you wish to remove from the Entity
		/// \note
		/// If the component does not exsist within the Entity it will simply
		/// be ignored
		void destroyComponent(EntityPtr e, ComponentPtr component);
		
		/// Destroys a Component from an Entity
		/// \param e The Entity you wish to remove the component from
		/// \param component The component you wish to remove from the Entity
		/// \param componentType The class type that the Component is
		/// \note
		/// If the component does not exsist within the Entity it will simply
		/// be ignored
		void destroyComponent(EntityPtr e, ComponentPtr component, const ComponentType& componentType);
		
		/// Removes a Component from an Entity
		/// \param e The Entity you wish to remove the component from
		/// \param componentType The class type that the Component is
		/// \note
		/// If the type component does not exsist within the Entity it will simply
		/// be ignored. This method is used for efficiency, depending if you
		/// know what the ComponenType is before
		/// you add it. If you DO know the type of component you are adding,
		/// use this method instead of the other method, it will be
		/// SLIGHTLY (no virtual function calls) faster.
		void destroyComponent(EntityPtr e, const ComponentType& componentType);
		
		/// Removes all the components for an Entity
		/// \param e The Enitty you wish to remove all the components from
		void destroyAllComponents(EntityPtr e);
		
		/// Retrieves a Component from an Entity
		/// \param e The Entity in which the Component is located
		/// \param componentType The class type that the Component is
		/// \return The appropriate component
		ComponentPtr getComponent(ConstEntityPtr e, const ComponentType& componentType) const;
		
		/// Determines whether an Entity contains a component type
		/// \param e The Entity which contains the component
		/// \param component The component you wish to determine whether the entity has
		bool containsComponent(ConstEntityPtr e, ComponentPtr component) const;
		
		/// Determines whether an Entity contains a component type
		/// \param e The Entity which contains the component
		/// \param component The component you wish to determine whether the entity has
		bool containsComponent(ConstEntityPtr e, ComponentPtr component, const ComponentType& componentType) const;
		
		/// Determines whether an Entity contains a component
		/// \param e The Entity which contains the component
		/// \param componentType The class type that the Component is
		bool containsComponent(ConstEntityPtr e, const ComponentType& componentType) const;
		
		/// \param e The Entity you wish to retrieve the entities for
		/// \return All the components that an Entity contains
		ComponentArray getComponentsFor(ConstEntityPtr e) const;
		
		/// Clears the ComponentStorage
		/// Removes all Entities and Components that are attached to it.
		void clear();
		
	private:
		
        // TODO: Change entirely
		struct ComponentDeleterFunctor
		{
			void operator()(ComponentPtr component) const
			{
				delete component; // TODO: Change
			}
		};
		
		typedef std::unique_ptr<BaseComponent, ComponentDeleterFunctor> SmartComponentPtr;
		typedef std::vector<SmartComponentPtr> ImplComponentArray;
		typedef std::vector<ImplComponentArray> ImplComponentEntityArray;
		
		
		/// The components that the ComponentStorage manages
		/// These components are layed out as follows:
		/// components[ENTITY_ID][COMPONENT_ID]
		/// That will retrieve the appropriate component for an entity
		/// \note
		/// I decided to place the entity's ID first, since there will be less
		/// "big" calls to resize. Since there is most likely more entities
		/// in a game than there is component types.
		ImplComponentEntityArray _componentsForEntities;
		
		/// Holds the deleted entities
		EntityArray _deletedEntities;
		
		
		
		// Prevent from copying; purposely not defined
		ComponentStorage(const ComponentStorage&);
		const ComponentStorage& operator=(const ComponentStorage&);
	};
}

#endif // __ANAX_COMPONENTSTORAGE_H__
