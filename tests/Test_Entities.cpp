#include "lest.hpp"

#include "anax/Entity.hpp"
#include "anax/World.hpp"

const lest::test specification[] =
{
	"Invalid entity handles", []
	{
		anax::World world;
		
		anax::Entity e1 = world.createEntity(); // create an entity
		e1.kill(); // kill it
		
		EXPECT(e1.isValid());
	}
	
	"Duplicate entity handles", []
	{
		anax::World world;

		anax::Entity e1 = world.createEntity(); // create an entity
		e1.kill(); // kill it
		
		// refresh the world (so that the ID will be invalid)
		world.refresh();
		
		// create another handle,
		// that is the same as the previous
		anax::Entity e2 = e1;
		
		EXPECT(!e2.isValid()); // should be invalid
	}
	
	"Activating and deactivating entities", []
	{
		anax::World world;
		
		anax::Entity e1 = world.createEntity();
		e1.activate();
		
		EXPECT(e1.isActivated());
		
		world.refresh();
		
		EXPECT(e1.isActivated());
	}
	
	"Adding and removing components" []
	{
		
	}
};

int main()
{
	return lest::run(specification);
}