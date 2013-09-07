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
	BaseSystem::~BaseSystem()
	{
	}
	
	const ComponentFilter& BaseSystem::getComponentFilter() const
	{
		return _componentFilter;
	}
	
	World& BaseSystem::getWorld() const
	{
		return *_world;
	}
	
	std::vector<Entity> BaseSystem::getEntities() const
	{
		return _entities;
	}
	
	
	void BaseSystem::add(anax::Entity &entity)
	{
		_entities.push_back(entity);
		onEntityAdded(entity);
	}
	
	void BaseSystem::remove(anax::Entity &entity)
	{
		_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
		
		onEntityRemoved(entity);
	}
	
	void BaseSystem::setWorld(anax::World &world)
	{
		_world = &world;
		initialize();
	}
}