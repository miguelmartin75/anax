#include "lest.hpp"

#include <anax/Entity.hpp>
#include <anax/World.hpp>

#include "Components.hpp"

const lest::test specification[] =
{
	"Invalid entity handles (killing entities)", []
	{
		anax::World world;
		
		auto e1 = world.createEntity(); // create an entity
		e1.kill(); // kill it
		
		EXPECT(e1.isValid());
	},
	
	"Duplicate invalid (killed) entity handles", []
	{
		anax::World world;

		auto e1 = world.createEntity(); // create an entity
		e1.kill(); // kill it
		
		// refresh the world (so that the ID will be invalid)
		world.refresh();
		
		// create another handle,
		// that is the same as the previous
		anax::Entity e2 = e1;
		
		EXPECT(!e2.isValid()); // should be invalid
	},
	
	"Activating and deactivating entities", []
	{
		anax::World world;
		
		auto e1 = world.createEntity();
		e1.activate();
		
		EXPECT(!e1.isActivated()); // should not be activated
		
		world.refresh();
		
		EXPECT(e1.isActivated()); // should be activated
		
		e1.deactivate();
		
		EXPECT(e1.isActivated()); // should be still activated

		world.refresh();
		
		EXPECT(!e1.isActivated()); // should not be activated
	},
	
	"Adding components", []
	{
		anax::World world;
		
		auto e = world.createEntity();
		e.addComponent<PositionComponent>();
		
		EXPECT(e.hasComponent<PositionComponent>());
	},
	
	"Removing components", []
	{
		anax::World world;
		
		auto e = world.createEntity();
		e.addComponent<PositionComponent>();
		e.removeComponent<PositionComponent>();
		
		EXPECT(!e.hasComponent<PositionComponent>());
	},
	
	"Removing all components", []
	{
		anax::World world;
		
		auto e = world.createEntity();
		e.addComponent<PositionComponent>();
		e.addComponent<VelocityComponent>();
		
		e.removeAllComponents();
		
		EXPECT(!e.hasComponent<PositionComponent>() && !e.hasComponent<VelocityComponent>());
	}
};

int main()
{
	return lest::run(specification);
}