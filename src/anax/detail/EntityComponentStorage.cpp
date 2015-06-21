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

#include <anax/detail/EntityComponentStorage.hpp>

#include <anax/util/ContainerUtils.hpp>
#include <anax/detail/AnaxAssert.hpp>

namespace anax
{
    namespace detail
    {
        EntityComponentStorage::EntityComponentStorage(std::size_t entityAmount) : 
            m_componentEntries(entityAmount)
        {
        }

        void EntityComponentStorage::addComponent(Entity& entity, Component* component, TypeId componentTypeId)
        {
            ANAX_ASSERT(entity.isValid(), "invalid entity cannot have components added to it");

            auto index = entity.getId().index;
            auto& componentDataForEntity = m_componentEntries[index];

            componentDataForEntity.components[componentTypeId].reset(component);
            componentDataForEntity.componentTypeList[componentTypeId] = true;
        }

        void EntityComponentStorage::removeComponent(Entity& entity, TypeId componentTypeId)
        {
            ANAX_ASSERT(entity.isValid(), "invalid entity cannot remove components");

            auto index = entity.getId().index;
            auto& componentDataForEntity = m_componentEntries[index];

            componentDataForEntity.components[componentTypeId].reset();
            componentDataForEntity.componentTypeList[componentTypeId] = false;
        }

        void EntityComponentStorage::removeAllComponents(Entity &entity)
        {
            auto index = entity.getId().index;
            auto& componentDataForEntity = m_componentEntries[index];

            for(auto& c : componentDataForEntity.components) c.reset();
            componentDataForEntity.componentTypeList.reset();
        }

        Component& EntityComponentStorage::getComponent(const Entity& entity, TypeId componentTypeId) const
        {
            ANAX_ASSERT(entity.isValid() && hasComponent(entity, componentTypeId), "Entity is not valid or does not contain component");

            return *getComponentsImpl(entity)[componentTypeId];
        }

        ComponentTypeList EntityComponentStorage::getComponentTypeList(const Entity& entity) const
        {
            ANAX_ASSERT(entity.isValid(), "invalid entity cannot retrieve the component list");

            return m_componentEntries[entity.getId().index].componentTypeList;
        }

        ComponentArray EntityComponentStorage::getComponents(const Entity& entity)  const
        {
            ANAX_ASSERT(entity.isValid(), "invalid entity cannot retrieve components, as it has none");

            auto& componentsToConvert = getComponentsImpl(entity);

            ComponentArray temp;
            temp.reserve(componentsToConvert.size());

            for(auto& i : componentsToConvert)
                temp.emplace_back(i.get());

            return temp;
        }

        bool EntityComponentStorage::hasComponent(const Entity& entity, TypeId componentTypeId) const
        {
            ANAX_ASSERT(entity.isValid(), "invalid entity cannot check if it has components");

            auto& components = getComponentsImpl(entity);

            return components.size() > componentTypeId && components[componentTypeId] != nullptr;
        }

        void EntityComponentStorage::resize(std::size_t entityAmount)
        {
            m_componentEntries.resize(entityAmount);
        }

        void EntityComponentStorage::clear()
        {
            m_componentEntries.clear();
        }

        EntityComponentStorage::ImplComponentArray& EntityComponentStorage::getComponentsImpl(const Entity &e)
        {
            return m_componentEntries[e.getId().index].components;
        }

        const EntityComponentStorage::ImplComponentArray& EntityComponentStorage::getComponentsImpl(const Entity &e) const
        {
            return m_componentEntries[e.getId().index].components;
        }
    }
}
