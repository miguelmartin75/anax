#ifndef __SPRITECOMPONENT_HPP__
#define __SPRITECOMPONENT_HPP__

#include <anax/Component.hpp>
#include <SFML/Graphics/Sprite.hpp>

/// \brief A component used to describe a sprite
///
/// \author Miguel Martin
struct SpriteComponent : anax::Component<SpriteComponent>
{
	sf::Sprite sprite;
};

#endif // __SPRITECOMPONENT_HPP__