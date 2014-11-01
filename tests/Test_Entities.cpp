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

#include <lest.hpp>

#include <anax/Entity.hpp>
#include <anax/World.hpp>

#include "Components.hpp"
#include "Systems.hpp"

const lest::test specification[] =
{
    CASE("Invalid entity handles (killing entities)")
    {
        anax::World world;

        auto e1 = world.createEntity(); 
        e1.kill();

        EXPECT(e1.isValid());

        world.refresh();
        EXPECT(!e1.isValid());
    },

    CASE("Invalid entity handles (clearing world)")
    {
        anax::World world;

        auto e1 = world.createEntity();
        world.clear();

        EXPECT(!e1.isValid());
    },

    CASE("Duplicate invalid (killed) entity handles")
    {
        anax::World world;

        auto e1 = world.createEntity(); 
        e1.kill();

        // refresh the world (so that the ID will be invalid)
        world.refresh();

        // create another handle, that is the same as the previous
        anax::Entity e2 = e1;

        EXPECT(!e2.isValid()); // should be invalid
    },

    CASE("Activating and deactivating entities")
    {
        anax::World world;

        auto e = world.createEntity();

        e.activate();
        EXPECT(!e.isActivated());  // should not be activated

        world.refresh();
        EXPECT(e.isActivated());   // should be activated

        e.deactivate();
        EXPECT(e1.isActivated());  // should be still activated

        world.refresh();
        EXPECT(!e1.isActivated()); // should not be activated
    },

    CASE("Adding components")
    {
        anax::World world;

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();

        EXPECT(e.hasComponent<PositionComponent>());
    },

    CASE("Removing components")
    {
        anax::World world;

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();
        e.removeComponent<PositionComponent>();

        EXPECT(e.hasComponent<PositionComponent>() == false);
    },

    CASE("Removing all components")
    {
        anax::World world;

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();
        e.addComponent<VelocityComponent>();

        e.removeAllComponents();

        EXPECT(e.hasComponent<PositionComponent>() == false);
        EXPECT(e.hasComponent<VelocityComponent>() == false);
    },

    CASE("Attempt to add an Entity that does not confine to a system's filter")
    {
        anax::World world;
        MovementSystem movementSystem;
        auto e = world.createEntity();

        e.addComponent<PositionComponent>();
        e.addComponent<VelocityComponent>();
        e.addComponent<NPCComponent>();
        e.activate();

        world.addSystem(movementSystem);
        world.refresh();
    }

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

    CASE("Retrieving an Entity via ID index")
    {
        anax::World world;

        auto e1 = world.createEntity();
        auto e2 = world.getEntity(e1.getId().index);

        EXPECT(e1.isValid());
        EXPECT(e2.isValid());
        EXPECT(e1 == e2);
    }
};

int main()
{
    return lest::run(specification);
}
