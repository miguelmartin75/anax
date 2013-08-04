#include <iostream>
#include <vector>
#include <memory>

#include <anax/anax.hpp>
using namespace anax;

const int ENTIIES_TO_CREATE = 1500;

struct PositionComponent : Component<PositionComponent>
{
	PositionComponent(int X, int Y, int Z) : x(X), y(Y), z(Z) {}
	int x, y, z;
};

struct VelocityComponent : Component<VelocityComponent>
{
	VelocityComponent(int X, int Y, int Z) : x(X), y(Y), z(Z) {}
	int x, y, z;
};

struct MovementSystem : System<MovementSystem>
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
			std::cout << "Updating entity: " << e.getId().index << '\n';
			
			auto position = e.getComponent<PositionComponent>();
			auto velocity = e.getComponent<VelocityComponent>();
			
			position.x += velocity.x;
			position.y += velocity.y;
			position.z += velocity.z;
			
			if(!e.isActivated())
			{
				std::cout << "I fucked up somewhere\n";
			}
			
			e.kill();
		}
	}
	
private:
	
	virtual void onEntityAdded(Entity& e) override
	{
		std::cout << "Entity added to MovementSystem: " << e.getId().index << '\n';
	}
	
	virtual void onEntityRemoved(Entity& e) override
	{
		std::cout << "Entity removed from MovemnetSystem: " << e.getId().index << '\n';
	}
};

void createEntities(World& world)
{
	std::vector<Entity> entities = world.createEntities(ENTIIES_TO_CREATE);
	for(auto& e : entities)
	{
		e.activate();
		e.addComponent<PositionComponent>(1, 2, 3);
		e.addComponent<VelocityComponent>(3, 2, 1);
	}
	
}

int main(int argc, const char * argv[])
{
	World world;
	createEntities(world);
	
	MovementSystem movementSystem;
	world.addSystem(movementSystem);
	
	for(int i = 0; i < 5; ++i)
	{
		world.refresh();
		movementSystem.update();
	}
	
    return 0;
}