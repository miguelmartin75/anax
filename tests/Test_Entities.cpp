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
    CASE("Valid entity handles")
    {
        anax::World world;
        auto e = world.createEntity();
        EXPECT(e.isValid() == true);
    },

    CASE("Invalid entity handles (killing entities)")
    {
        anax::World world;

        auto e = world.createEntity();
        e.kill();

        EXPECT(e.isValid()); // should only be invalid after a refresh

        world.refresh();
        EXPECT(e.isValid() == false);
    },

    CASE("Invalid entity handles (clearing world)")
    {
        anax::World world;

        auto e = world.createEntity();
        world.clear();

        EXPECT(e.isValid() == false);
    },

    CASE("Duplicate invalid (killed) entity handles")
    {
        anax::World world;

        auto e1 = world.createEntity(); 
        e1.kill();

        // refresh the world (so that the ID will be invalid)
        world.refresh();
        EXPECT(e1.isValid() == false);

        // create another handle, that is the same as the previous
        anax::Entity e2 = e1;

        // this handle should also be invalid
        EXPECT(e2.isValid() == false);
    },

    CASE("Activating and deactivating entities")
    {
        anax::World world;

        auto e = world.createEntity();

        e.activate();
        EXPECT(!e.isActivated());  // should not be activated
        world.refresh();
        EXPECT(e.isActivated());   // should be activated after a refresh

        e.deactivate();
        EXPECT(e.isActivated());  // should be still activated
        world.refresh();
        EXPECT(!e.isActivated()); // should not be activated after a refresh
    },

    CASE("Activating an entity multiple times")
    {
        anax::World world;
        MovementSystem movementSystem;
        world.addSystem(movementSystem);

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();
        e.addComponent<VelocityComponent>();
        e.activate();
        e.activate();

        world.refresh();

        {
            auto entities = movementSystem.getEntities();
            EXPECT(entities.size() == 1);
        }

        // try to add it again
        e.activate();
        world.refresh();

        {
            auto entities = movementSystem.getEntities();
            EXPECT(entities.size() == 1);
        }
    },

    CASE("Adding components")
    {
        anax::World world;

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();

        EXPECT(e.hasComponent<PositionComponent>() == true);
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

        EXPECT(e.hasComponent<PositionComponent>() == true);
        EXPECT(e.hasComponent<VelocityComponent>() == true);

        e.removeAllComponents();

        EXPECT(e.hasComponent<PositionComponent>() == false);
        EXPECT(e.hasComponent<VelocityComponent>() == false);
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
