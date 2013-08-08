#include <iostream>
#include <vector>
#include <memory>

#include <anax/anax.hpp>
using namespace anax;

const int ENTIIES_TO_CREATE = 3;

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

class MovementSystem
	: public System<MovementSystem>
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
			std::cout << "Moving entity " << e.getId().index() << '\n';
			
			auto position = e.getComponent<PositionComponent>();
			auto velocity = e.getComponent<VelocityComponent>();
			std::cout << "From: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
			
			position.x += velocity.x;
			position.y += velocity.y;
			position.z += velocity.z;
			
			std::cout << "To: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
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

void createMoveableEntities(World& world)
{
	const int MAX_POSITION_COMPONENT = 100;
	const int MAX_VELOCITY_COMPONENT = 10;
	
	std::vector<Entity> entities = world.createEntities(ENTIIES_TO_CREATE);
	for(auto& e : entities)
	{
		e.activate();
		e.addComponent<PositionComponent>(rand() % MAX_POSITION_COMPONENT, rand() % MAX_POSITION_COMPONENT, rand() % MAX_POSITION_COMPONENT);
		e.addComponent<VelocityComponent>(rand() % MAX_VELOCITY_COMPONENT, rand() % MAX_VELOCITY_COMPONENT, rand() % MAX_VELOCITY_COMPONENT);
	}
}

int main(int argc, const char * argv[])
{
	World world;
	createMoveableEntities(world);
	
	MovementSystem movementSystem;
	world.addSystem(movementSystem);
	
	for(int i = 0; i < 5; ++i)
	{
		world.refresh();
		movementSystem.update();
	}
	
    return 0;
}