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

#ifndef __SYSTEMS_HPP__
#define __SYSTEMS_HPP__

#include <exception>

#include <anax/System.hpp>

#include "Components.hpp"

class MovementSystem
	: public anax::System<MovementSystem>
{
public:
	
	MovementSystem()
		: Base(anax::ComponentFilter().requires<PositionComponent, VelocityComponent>())
	{
	}
	
	void update()
	{
		auto entities = getEntities();
		for(auto& e : entities)
		{			
			auto position = e.getComponent<PositionComponent>();
			auto velocity = e.getComponent<VelocityComponent>();
			
			position.x += velocity.x;
			position.y += velocity.y;
			position.z += velocity.z;
		}
	}
	
private:
	
	virtual void onEntityAdded(Entity& e) override
	{
		std::cout << "Entity added to MovementSystem: " << e.getId().index << '\n';
		if(e.hasComponent<NPCComponent>())
		{
			throw std::logic_error("Player contains NPCComponent :(");
		}
	}
	
	virtual void onEntityRemoved(Entity& e) override
	{
		std::cout << "Entity removed from MovementSystem: " << e.getId().index << '\n';
	}
};

// note: this is a useless system, but I just made it for testing
// purposes
class PlayerSystem
	: public anax::System<PlayerSystem>
{
public:
	
	PlayerSystem()
		: Base(anax::ComponentFilter().requires<PlayerComponent>().excludes<NPCComponent>())
	{
	}
	
private:
	
	virtual void onEntityAdded(Entity& e) override
	{
		std::cout << "Player added: " << e.getComponent<PlayerComponent>().name << '\n';
	}
	
	
	virtual void onEntityRemoved(Entity& e) override
	{
		std::cout << "Player removed: " << e.getComponent<PlayerComponent>().name << '\n';
	}
};

#endif // __SYSTEMS_HPP__