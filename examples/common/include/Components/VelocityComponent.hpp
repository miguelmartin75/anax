#ifndef __VELOCITYCOMPONENT_HPP__
#define __VELOCITYCOMPONENT_HPP__

#include <anax/Component.hpp>
#include <SFML/System/Vector2.hpp>

/// \brief A component used to describe the velocity of an entity
///
/// \author Miguel Martin
struct VelocityComponent : anax::Component<VelocityComponent>
{
	sf::Vector2f velocity;
};

#endif // __VELOCITYCOMPONENT_HPP__