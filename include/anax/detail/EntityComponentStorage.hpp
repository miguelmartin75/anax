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

#ifndef __ANAX_ENTITYCOMPONENTSTORAGE_HPP__
#define __ANAX_ENTITYCOMPONENTSTORAGE_HPP__

#include <memory>
#include <vector>

#include "../config.hpp"
#include "../Entity.hpp"
#include "../Component.hpp"
#include "../ComponentTypeList.hpp"

#include "ClassTypeId.hpp"

namespace anax
{
	namespace detail
	{
		/// \brief A class to store components for entities within a world
		///
		///
		/// Used to store the components 
		///
		///
		/// \author Miguel Martin
		class EntityComponentStorage
		{
		public:
			
			EntityComponentStorage(std::size_t entityAmount);
			
			EntityComponentStorage(const EntityComponentStorage&) = delete;
			EntityComponentStorage(EntityComponentStorage&&) = delete;
			EntityComponentStorage& operator=(const EntityComponentStorage&) = delete;
			EntityComponentStorage& operator=(EntityComponentStorage&&) = delete;
			
			
			
			void addComponent(Entity& entity, BaseComponent* component, TypeId componentTypeId);
			
			void removeComponent(Entity& entity, TypeId componentTypeId);
			
			void removeAllComponents(Entity& entity);
			
			BaseComponent& getComponent(const Entity& entity, TypeId componentTypeId) const;
			
			ComponentTypeList getComponentTypeList(const Entity& entity) const;
			
			std::vector<BaseComponent*> getComponents(const Entity& entity) const;
			
			bool hasComponent(const Entity& entity, TypeId componentTypeId) const;
			
			void resize(std::size_t entityAmount);
			
		private:
			
			/// \brief A data structure to describe the components
			/// within an entity
			/// 
			/// \author Miguel Martin
			struct EntityComponents
			{
				EntityComponents() = default;
				
				// bug in clang? won't work w/o this
				// http://stackoverflow.com/questions/8560994/stdmake-shared-stdunique-ptr-and-move-constructors
				// I think it's due to ComponentTypeList (may have to update boost)
				EntityComponents(EntityComponents&& e)
					: components(std::move(e.components)),
					componentTypeList(std::move(e.componentTypeList))
				{
				}

				/// The components of an entity. The
				/// index of this array is the same as the TypeId
				/// of the component.
				std::vector<std::unique_ptr<BaseComponent> > components;
				
				/// A list of component types, which resembles
				/// what components an entity has
				ComponentTypeList componentTypeList;
			};
			
			/// All the components for every entity, which has
			/// an entity. The indices of this array is the same
			/// as the index component of an entity's ID.
			std::vector<EntityComponents> _componentEntries;
		};
	}
}


#endif // __ANAX_ENTITYATTRIBUTES_HPP__