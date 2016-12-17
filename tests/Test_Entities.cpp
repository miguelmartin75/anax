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

#include <algorithm>

#include <anax/Entity.hpp>
#include <anax/World.hpp>
#include <anax/detail/AnaxAssert.hpp>

#include "Components.hpp"
#include "Systems.hpp"

using namespace anax;

// Since entities are heavily tied to a World, we are essentially also testing
// the world.
//
// Here are the possible test cases we need to test for:
//
// 1. Valid/invalid entity handles
//      ✓ New entity => should be valid
//      ✓ Kill new entity => should be invalid
//      ✓ Clearing world => should be invalid
//      ✓ Copy of entity => should both be valid
//      ✓ Copy entity and:
//          ✓ kill each (original, copy and both) => both should be invalid
//          ✓ Clearing world => both should be invalid
//      ✓ Duplicate an already invalid entity => copy should be invalid
// 3. De/activating entities
//      ✓ New entity => should be deactivated
//      - Duplicate entities: each copy (separate case) => both should be valid
//      ✓ Activate entity => is activated?
//      ✓ Activate -> Deactivate => is de-activated 
//          * where appropriate (before/after world refresh)?
//      ✓ Activate -> Deactivate -> Activate => is activated?
//          * where appropriate
//      ✓ Activate entity multiple times
//      ✓ Deactivate entity multiple times
// 5. Adding and removing components
//      ✓ New entity => are no components added?
//      ✓ Adding a component => does hasComponent return true?
//      ✓ Adding multiple components => does it assert?
//      ✓ Removing a component => does hasComponent return false?
//      ✓ Removing all components => does hasComponent return false?
// 6. Retrieving an entity via index
//      ✓ Invalid index => invalid entity returned?
//      ✓  Valid index => appropriate entity returned?
//      ✓ Multiple entities added/removed => appropriate entity returned?


template <class Container>
int countNonNull(const Container& c)
{
    return std::count_if(std::begin(c), std::end(c), [](typename Container::const_reference x) { return x != nullptr; });
}


// Gross, I know, but oh well.
#define activateAndTest(w, e) \
{ \
    e.activate(); \
    EXPECT(e.isActivated() == false); \
    w.refresh(); \
    EXPECT(e.isActivated() == true); \
}

#define deactivateAndTest(w, e) \
{ \
    EXPECT(e.isActivated() == true); \
    e.deactivate(); \
    EXPECT(e.isActivated() == true); \
    w.refresh(); \
    EXPECT(e.isActivated() == false); \
}

const lest::test specification[] =
{
    /// Valid/invalid for one unique entity
    
    CASE("Valid entity handle: new entity")
    {
        World world;
        auto e = world.createEntity();
        EXPECT(e.isValid() == true);
    },

    CASE("Invalid entity handles (killing entities)")
    {
        World world;

        auto e = world.createEntity();
        e.kill();

        // should only be invalid after a refresh
        EXPECT(e.isValid() == true);
        world.refresh();
        EXPECT(e.isValid() == false);
    },

    CASE("Invalid entity handle (clearing world)")
    {
        World world;

        auto e = world.createEntity();
        world.clear();

        EXPECT(e.isValid() == false);
    },

    /// Valid/invalid duplicate handles

    CASE("Valid entity handle (duplicate handles)")
    {
        World world;
        auto e = world.createEntity();
        auto eCopy = e;

        EXPECT(e.isValid() == true);
        EXPECT(eCopy.isValid() == true);
    },

    CASE("Invalid entity handles (duplicate and kill original)")
    {
        World world;
        auto e = world.createEntity();
        auto eCopy = e;

        e.kill();

        EXPECT(e.isValid() == true);
        EXPECT(eCopy.isValid() == true);
        world.refresh();
        EXPECT(e.isValid() == false);
        EXPECT(eCopy.isValid() == false);
    },

    CASE("Invalid entity handles (duplicate and kill clone)")
    {
        World world;
        auto e = world.createEntity();
        auto eCopy = e;

        eCopy.kill();

        EXPECT(e.isValid() == true);
        EXPECT(eCopy.isValid() == true);
        world.refresh();
        EXPECT(e.isValid() == false);
        EXPECT(eCopy.isValid() == false);
    },

    CASE("Invalid entity handles (duplicate and kill both)")
    {
        World world;
        auto e = world.createEntity();
        auto eCopy = e;

        e.kill();
        eCopy.kill();

        EXPECT(e.isValid() == true);
        EXPECT(eCopy.isValid() == true);
        world.refresh();
        EXPECT(e.isValid() == false);
        EXPECT(eCopy.isValid() == false);
    },

    CASE("Invalid entity handles (duplicate and clear world)")
    {
        World world;
        auto e = world.createEntity();
        auto eCopy = e;

        world.clear();
        EXPECT(e.isValid() == false);
        EXPECT(eCopy.isValid() == false);
    },

    CASE("Duplicate invalid (killed) entity handle")
    {
        World world;

        auto e1 = world.createEntity(); 
        e1.kill();

        // refresh the world (so that the ID will be invalid)
        world.refresh();
        EXPECT(e1.isValid() == false);

        // create another handle, that is the same as the previous
        Entity e2 = e1;

        // this handle should also be invalid
        EXPECT(e2.isValid() == false);
    },

    // Activation/deactivation

    CASE("isActivated: new entity (false)")
    {
        World world;

        auto e = world.createEntity();
        EXPECT(e.isActivated() == false);
    },

    CASE("Activate")
    {
        World world;
        auto e = world.createEntity();

        activateAndTest(world, e);
    },

    CASE("Activate -> Deactivate")
    {
        World world;
        auto e = world.createEntity();

        activateAndTest(world, e);
        deactivateAndTest(world, e);
    },

    CASE("Activate -> Deactivate -> Activate")
    {
        World world;
        auto e = world.createEntity();

        activateAndTest(world, e);
        deactivateAndTest(world, e);
        activateAndTest(world, e);
    },

    CASE("Activating an entity multiple times")
    {
        World world;
        MovementSystem movementSystem;
        world.addSystem(movementSystem);

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();
        e.addComponent<VelocityComponent>();

        auto activate = [&]() 
        { 
            for(int i = 0; i < 100; ++i)
            {
                e.activate();
            }
            world.refresh();
        };

        activate();

        EXPECT(e.isActivated() == true);
        EXPECT(movementSystem.getEntities().size() == 1);

        activate();

        EXPECT(e.isActivated() == true);
        EXPECT(countNonNull(e.getComponents()) == 2);
    },

    // Duplicate code of above (refactor pls)
    CASE("De-activating an entity multiple times")
    {
        World world;
        MovementSystem movementSystem;
        world.addSystem(movementSystem);

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();
        e.addComponent<VelocityComponent>();

        e.activate();
        world.refresh();

        EXPECT(e.isActivated() == true);
        EXPECT(movementSystem.getEntities().size() == 1);

        auto deactivate = [&]() 
        { 
            for(int i = 0; i < 100; ++i)
            {
                e.deactivate();
            }
            world.refresh();
        };

        deactivate();

        EXPECT(e.isActivated() == false);
        EXPECT(movementSystem.getEntities().size() == 0);

        deactivate();

        EXPECT(e.isActivated() == false);
        EXPECT(countNonNull(e.getComponents()) == 2);
    },

    CASE("New entity: no components added")
    {
        anax::World world;

        auto e = world.createEntity();

        EXPECT(countNonNull(e.getComponents()) == 0);
        EXPECT(e.hasComponent<PositionComponent>() == false);
        EXPECT_THROWS_AS(e.getComponent<PositionComponent>(), anax::TestException);
    },

    CASE("Adding components")
    {
        anax::World world;

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();

        EXPECT(e.hasComponent<PositionComponent>() == true);
        EXPECT_NO_THROW(e.getComponent<PositionComponent>());
        EXPECT(countNonNull(e.getComponents()) == 1);
    },

    CASE("Removing components")
    {
        anax::World world;

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();
        e.removeComponent<PositionComponent>();

        EXPECT(e.hasComponent<PositionComponent>() == false);
        EXPECT(countNonNull(e.getComponents()) == 0);
        EXPECT_THROWS_AS(e.getComponent<PositionComponent>(), anax::TestException);
    },

    CASE("Removing all components")
    {
        anax::World world;

        auto e = world.createEntity();
        e.addComponent<PositionComponent>();
        e.addComponent<VelocityComponent>();

        EXPECT(e.hasComponent<PositionComponent>() == true);
        EXPECT(e.hasComponent<VelocityComponent>() == true);
        EXPECT_NO_THROW(e.getComponent<PositionComponent>());
        EXPECT_NO_THROW(e.getComponent<VelocityComponent>());

        e.removeAllComponents();

        EXPECT(countNonNull(e.getComponents()) == 0);
        EXPECT(e.hasComponent<PositionComponent>() == false);
        EXPECT(e.hasComponent<VelocityComponent>() == false);
        EXPECT_THROWS_AS(e.getComponent<PositionComponent>(), anax::TestException);
        EXPECT_THROWS_AS(e.getComponent<VelocityComponent>(), anax::TestException);
    },

    CASE("Retrieving an Entity via ID index (VALID index)")
    {
        anax::World world;

        auto e1 = world.createEntity();
        auto e2 = world.getEntity(e1.getId().index);

        EXPECT(e1.isValid());
        EXPECT(e2.isValid());
        EXPECT(e1 == e2);
    },

    CASE("Retrieving an Entity via ID index (VALID index; multiple entities created)")
    {
        anax::World world;

        auto e1 = world.createEntity();

        world.createEntities(1000);
        for(int i = 0; i < 1000; ++i)
            world.createEntity();

        auto e2 = world.getEntity(e1.getId().index);

        EXPECT(e1.isValid());
        EXPECT(e2.isValid());
        EXPECT(e1 == e2);
    },

    CASE("Retrieving an Entity via ID index (INVALID index)")
    {
        anax::World world;

        auto e = world.createEntity();
        EXPECT(!(world.getEntity(-1).isValid()));
    }
};

int main()
{
    return lest::run(specification);
}
