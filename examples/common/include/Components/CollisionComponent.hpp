#ifndef __COLLISIONCOMPONENT_HPP__
#define __COLLISIONCOMPONENT_HPP__

#include <anax/Component.hpp>

/// \brief A component used to store collision information
///
/// \author Miguel Martin
struct CollisionComponent : anax::Component<CollisionComponent>
{
	sf::FloatRect BBox;
};

#endif // __COLLISIONCOMPONENT_HPP__