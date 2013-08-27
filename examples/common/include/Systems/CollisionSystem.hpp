#ifndef __COLLISIONSYSTEM_HPP__
#define __COLLISIONSYSTEM_HPP__

#include <anax/System.hpp>

/// \brief A system that handles collisions
///
/// This system handles collisions. It uses entities with the following components:
///		- Transform
///		- Collision
///
/// \author Miguel Martin
struct CollisionSystem : anax::System<CollisionSystem>
{
public:
	
	/// Default constructor
	CollisionSystem();
	
	/// Updates the collision system
	/// \param deltaTime The change in time
	void update(float deltaTime);
	
	
	// TODO: call backs
};

#endif // __COLLISIONSYSTEM_HPP__