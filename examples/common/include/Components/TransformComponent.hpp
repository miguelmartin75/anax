#ifndef __TRANSFORMCOMPONENT_HPP__
#define __TRANSFORMCOMPONENT_HPP__

#include <anax/Component.hpp>
#include <SFML/Graphics/Transformable.hpp>

/// \brief A component used to store transform information
///
/// \author Miguel Martin
struct TransformComponent : anax::Component<TransformComponent>
{
	sf::Transformable transform;
};

#endif // __TRANSFORMCOMPONENT_HPP__