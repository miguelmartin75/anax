#ifndef __PLAYERCONTROLLERSYSTEM_HPP__
#define __PLAYERCONTROLLERSYSTEM_HPP__

#include <anax/System.hpp>

/// \brief A system that controls the player
///
/// \author Miguel Martin
struct PlayerControllerSystem : anax::System<PlayerControllerSystem>
{
public:
	
	/// Default constructor
	PlayerControllerSystem();
    
    /// Updates the PlayerControllerSystem
    void update(float deltaTime);
};

#endif // __PLAYERCONTROLLERSYSTEM_HPP__