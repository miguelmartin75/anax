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

#include "lest.hpp"

#include <sstream>

#include <anax/anax.hpp>
using namespace anax;

#include "Systems.hpp"

void createMoveableEntities(int amount, World& world);
void createPlayers(int amount, World& world);
void createNPCs(int amount, World& world);
void createNPCsAndPlayers(int amount, World& world);

const lest::test specification[] =
{
	"MovementSystem", []
	{
		anax::World world;
		MovementSystem movementSystem;
		world.addSystem(movementSystem);
		
		createMoveableEntities(rand() % 100 + 1, world);
		createPlayers(rand() % 100 + 1, world);
		
		for(int i = 0; i < 5; ++i)
		{
			world.refresh();
			movementSystem.update();
		}
	},
	
	"PlayerSystem", []
	{
		anax::World world;
		PlayerSystem playerSystem;
		world.addSystem(playerSystem);
		
		createNPCsAndPlayers(rand() % 100 + 1, world);
		createPlayers(rand() % 100 + 1, world);
		createNPCs(rand() % 100 + 1, world);
		
		world.refresh();
	},

    "Testing if a system exists", []
    {
        anax::World world;
        PlayerSystem playerSystem;

        EXPECT(!world.doesSystemExist<PlayerSystem>());
        EXPECT(!world.doesSystemExist(playerSystem));

        world.addSystem(playerSystem);

        EXPECT(world.doesSystemExist<PlayerSystem>());
        EXPECT(world.doesSystemExist(playerSystem));
    },
   
    "Testing if a system exists (clearing the world)", []
    {
        anax::World world;
        PlayerSystem playerSystem;
		MovementSystem movementSystem;

        EXPECT(!world.doesSystemExist<PlayerSystem>());
        EXPECT(!world.doesSystemExist(playerSystem));
        EXPECT(!world.doesSystemExist<MovementSystem>());
        EXPECT(!world.doesSystemExist(movementSystem));

        world.addSystem(playerSystem);
        world.addSystem(movementSystem);

        EXPECT(world.doesSystemExist<PlayerSystem>());
        EXPECT(world.doesSystemExist(playerSystem));
        EXPECT(world.doesSystemExist<MovementSystem>());
        EXPECT(world.doesSystemExist(movementSystem));

        world.clear();

        EXPECT(!world.doesSystemExist<PlayerSystem>());
        EXPECT(!world.doesSystemExist(playerSystem));
        EXPECT(!world.doesSystemExist<MovementSystem>());
        EXPECT(!world.doesSystemExist(movementSystem));
    }, 

    "Testing if a system exists (removing the system)", []
    {
        anax::World world;
        PlayerSystem playerSystem;

        EXPECT(!world.doesSystemExist<PlayerSystem>());
        EXPECT(!world.doesSystemExist(playerSystem));

        world.addSystem(playerSystem);

        EXPECT(world.doesSystemExist<PlayerSystem>());
        EXPECT(world.doesSystemExist(playerSystem));

        world.removeSystem<PlayerSystem>();

        EXPECT(!world.doesSystemExist<PlayerSystem>());
        EXPECT(!world.doesSystemExist(playerSystem));
    }
};

void createMoveableEntities(int amount, World& world)
{
	auto entities = world.createEntities(amount);
	for(auto e : entities)
	{
		e.addComponent<PositionComponent>();
		e.addComponent<VelocityComponent>();
		e.activate();
	}
}
void createPlayers(int amount, World& world)
{
	std::ostringstream temp;
	auto entities = world.createEntities(amount);
	for(std::size_t i = 0; i < entities.size(); ++i)
	{
		temp << "Player " << i;
		entities[i].addComponent<PlayerComponent>().name = temp.str();
		temp.clear();
		
		entities[i].activate();
	}
}
void createNPCs(int amount, World& world)
{
	auto entities = world.createEntities(amount);
	for(std::size_t i = 0; i < entities.size(); ++i)
	{
		entities[i].addComponent<NPCComponent>();
		entities[i].activate();
	}
}
void createNPCsAndPlayers(int amount, World& world)
{
	std::ostringstream temp;
	auto entities = world.createEntities(amount);
	for(std::size_t i = 0; i < entities.size(); ++i)
	{
		temp << "Player " << i;
		entities[i].addComponent<PlayerComponent>().name = temp.str();
		temp.clear();
		entities[i].addComponent<NPCComponent>();
		
		entities[i].activate();
	}
}

int main()
{
	return lest::run(specification);
}
