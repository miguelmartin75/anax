#ifndef __AISYSTEM_HPP__
#define __AISYSTEM_HPP__

#include <anax/System.hpp>

/// \brief A system which handles the artificial intelligence for Pong
/// \author Miguel Martin
struct AISystem : anax::System<AISystem>
{
    /// Default constructor
    AISystem();

    /// Updates the system
    /// \param deltaTime The change in time
    void update(float deltaTime);
};

#endif // __AISYSTEM_HPP__