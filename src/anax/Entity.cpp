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

#include "Entity.hpp"

#include "World.hpp"

namespace anax
{
	Entity::Entity()
		: _world(nullptr)
	{
	}
	
	Entity::Entity(World& world, Entity::Id id)
		: _world(&world),
		  _id(id)
	{
	}
	
	World& Entity::getWorld() const
	{
		return *_world;
	}
	
	const Entity::Id& Entity::getId() const
	{
		return _id;
	}
	
	bool Entity::isValid() const
	{
		return getWorld().isValid(*this);
	}
	
	bool Entity::isActivated() const
	{
		return getWorld().isActivated(*this);
	}
	
	void Entity::activate()
	{
		getWorld().activateEntity(*this);
	}
	
	void Entity::deactivate()
	{
		getWorld().deactivateEntity(*this);
	}
	
	void Entity::kill()
	{
		getWorld().killEntity(*this);
	}
	
	void Entity::removeAllComponents()
	{
		getWorld()._entityAttributes.componentStorage.removeAllComponents(*this);
	}
	
	ComponentArray Entity::getComponents() const
	{
		return getWorld()._entityAttributes.componentStorage.getComponents(*this);
	}
	
	ComponentTypeList Entity::getComponentTypeList() const
	{
		return getWorld()._entityAttributes.componentStorage.getComponentTypeList(*this);
	}
	
	bool Entity::operator==(const anax::Entity &entity) const
	{
		return _id == entity._id && entity._world == _world;
	}
	
	
	
	void Entity::addComponent(BaseComponent* component, detail::TypeId componentTypeId)
	{
		getWorld()._entityAttributes.componentStorage.addComponent(*this, component, componentTypeId);
	}
	
	void Entity::removeComponent(detail::TypeId componentTypeId)
	{
		getWorld()._entityAttributes.componentStorage.removeComponent(*this, componentTypeId);
	}
	
	BaseComponent& Entity::getComponent(detail::TypeId componentTypeId) const
	{
		return getWorld()._entityAttributes.componentStorage.getComponent(*this, componentTypeId);
	}
	
	bool Entity::hasComponent(detail::TypeId componentTypeId) const
	{
		return getWorld()._entityAttributes.componentStorage.hasComponent(*this, componentTypeId);
	}
}

