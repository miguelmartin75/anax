#ifndef __COLLISIONSYSTEM_HPP__
#define __COLLISIONSYSTEM_HPP__

#include <vector>

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
	
	struct Listener
	{
		virtual ~Listener() = 0;
		
		/// Occurs when an Entity has collided with another entity
		/// \param e1 One of the entities the collision occured with
		/// \param e2 The other entity the collision occured with
		virtual void onCollisionOccured(anax::Entity& e1, anax::Entity& e2) {}
	};
	
	/// Default constructor
	CollisionSystem();
	
	/// Updates the collision system
	/// \param deltaTime The change in time
	void update(float deltaTime);
	
	/// Adds a Listener to the CollisionSystem
	/// \param listener The Listener you wish to add
	void addListener(Listener& listener);
	
	/// Removes a Listener from the CollisionSystem
	/// \param listener The Listener you wish to remove
	void removeListener(Listener& listener);
	
private:
	
	/// The listeners apart of the CollisionSystem
	std::vector<Listener*> _listeners;
};

#endif // __COLLISIONSYSTEM_HPP__