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

#include "EntityComponentStorage.hpp"

#include "ContainerUtils.hpp"

namespace anax
{
	namespace detail
	{
		EntityComponentStorage::EntityComponentStorage()
		{
		}
		
		void EntityComponentStorage::addComponent(Entity &entity, BaseComponent* component, TypeId componentTypeId)
		{
			assert(entity.isValid());
			
			auto index = entity.getId().index;
			auto& componentDataForEntity = _componentEntries[index];
			
			detail::EnsureCapacity(componentDataForEntity.components, componentTypeId);
			componentDataForEntity.components[componentTypeId] = std::unique_ptr<BaseComponent>(component);
			
			detail::EnsureCapacity(componentDataForEntity.componentTypeList, componentTypeId);
			componentDataForEntity.componentTypeList[componentTypeId] = true;
		}
		
		void EntityComponentStorage::removeComponent(Entity& entity, TypeId componentTypeId)
		{
			assert(entity.isValid());
			
			auto index = entity.getId().index;
			auto& componentDataForEntity = _componentEntries[index];
			
			componentDataForEntity.components[componentTypeId].reset();
			componentDataForEntity.componentTypeList[componentTypeId] = false;
		}
		
		BaseComponent* EntityComponentStorage::getComponent(const Entity& entity, TypeId componentTypeId) const
		{
			assert(entity.isValid());
			
			return getComponents(entity)[componentTypeId];
		}
		
		ComponentTypeList EntityComponentStorage::getComponentTypeList(const Entity& entity) const
		{
			assert(entity.isValid());
			
			return _componentEntries[entity.getId().index].componentTypeList;
		}
		
		std::vector<BaseComponent*> EntityComponentStorage::getComponents(const Entity& entity)  const
		{
			assert(entity.isValid());
			
			auto& componentsToConvert = _componentEntries[entity.getId().index].components;
			
			std::vector<BaseComponent*> temp;
			temp.reserve(componentsToConvert.size());
			
			for(auto& i : componentsToConvert)
				temp.push_back(i.get());
			
			return temp;
		}
		
		bool EntityComponentStorage::hasComponent(const Entity& entity, TypeId componentTypeId) const
		{
			assert(entity.isValid());

			auto components = getComponents(entity);
			
			return components.size() > componentTypeId && components[componentTypeId] != nullptr;
		}
	}
}