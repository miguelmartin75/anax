#ifndef __MOVEMENTSYSTEM_HPP__
#define __MOVEMENTSYSTEM_HPP__

#include <anax/System.hpp>

/// \brief A system that moves entities
///
/// This system moves entities. It uses entities with the following components:
///		- Transform
///		- Velocity
///
/// \author Miguel Martin
struct MovementSystem : anax::System<MovementSystem>
{
public:
	
	/// Default constructor
	MovementSystem();
	
	/// Updates the MovementSystem
	/// \param deltaTime The change in time
	void update(float deltaTime);
};

#endif // __MOVEMENTSYSTEM_HPP__