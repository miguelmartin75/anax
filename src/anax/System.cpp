///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
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

#include <anax/System.hpp>

#include <algorithm>

namespace anax
{
	BaseSystem::BaseSystem()
		: m_world(nullptr)
	{
	}
	
	BaseSystem::BaseSystem(const ComponentFilter& componentFilter)
		: m_componentFilter(componentFilter), m_world(nullptr)
	{
	}
	
	BaseSystem::~BaseSystem()
	{
	}
	
	const ComponentFilter& BaseSystem::getComponentFilter() const
	{
		return m_componentFilter;
	}
	
	World& BaseSystem::getWorld() const
	{
		return *m_world;
	}
	
	std::vector<Entity> BaseSystem::getEntities() const
	{
		return m_entities;
	}
	
	
	void BaseSystem::add(anax::Entity &entity)
	{
		m_entities.push_back(entity);
		onEntityAdded(entity);
	}
	
	void BaseSystem::remove(anax::Entity &entity)
	{
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
		
		onEntityRemoved(entity);
	}
	
	void BaseSystem::setWorld(anax::World &world)
	{
		m_world = &world;
		initialize();
	}
}
