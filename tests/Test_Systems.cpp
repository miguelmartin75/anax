///
/// anax tests
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

#include "lest.hpp"

#include <sstream>

#include <anax/anax.hpp>
using namespace anax;

#include "Systems.hpp"

const lest::test specification[] =
{
    CASE("Adding a system to a world")
    {
        World world;
        MovementSystem system;
        world.addSystem(system);

        EXPECT(world.doesSystemExist(system) == true);
    },

    CASE("Removing a system from a world")
    {
        World world;
        MovementSystem system;
        world.addSystem(system);

        world.removeSystem<decltype(system)>();

        EXPECT(world.doesSystemExist(system) == false);
    },

    CASE("Removing all systems from the world")
    {
        World world;
        MovementSystem movementSystem;
        PlayerSystem playerSystem;
        world.addSystem(movementSystem);
        world.addSystem(playerSystem);

        world.removeAllSystems();

        EXPECT(world.doesSystemExist(movementSystem) == false);
        EXPECT(world.doesSystemExist(playerSystem) == false);
    },

    CASE("Attempt to add an Entity that does confine to a system's filter")
    {
        anax::World world;
        MovementSystem system;
        world.addSystem(system);

        auto e = world.createEntity();

        e.addComponent<PositionComponent>();
        e.addComponent<VelocityComponent>();
        e.addComponent<NPCComponent>();
        e.activate();

        world.refresh();
    },

    CASE("Attempt to add an Entity that does NOT confine to a system's filter")
    {
        anax::World world;
        PlayerSystem system;
        world.addSystem(system);
        auto e = world.createEntity();

        e.addComponent<PlayerComponent>();
        e.addComponent<NPCComponent>();
        e.activate();

        world.refresh();
    },

    CASE("Removing components with a system attached to the world")
    {
        anax::World world;
        MovementSystem moveSystem;

        world.addSystem(moveSystem);

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();
        e.addComponent<VelocityComponent>();
        e.activate();

        // make sure we don't get any exceptions
        world.refresh();
        moveSystem.update(); 

        e.removeComponent<PositionComponent>();
        e.activate();

        EXPECT(e.hasComponent<PositionComponent>() == false);

        // make sure we don't get any exceptions (again)
        world.refresh();
        moveSystem.update();
    },

    CASE("Removing all components with a system attached to the world")
    {
        anax::World world;
        MovementSystem moveSystem;

        world.addSystem(moveSystem);	

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();
        e.addComponent<VelocityComponent>();

        // make sure we don't get any exceptions
        e.activate();
        world.refresh();

        e.removeAllComponents();
        e.activate();

        EXPECT(e.hasComponent<PositionComponent>() == false);
        EXPECT(e.hasComponent<VelocityComponent>() == false);

        world.refresh();
        moveSystem.update();
    },


};

int main()
{
    return lest::run(specification);
}
