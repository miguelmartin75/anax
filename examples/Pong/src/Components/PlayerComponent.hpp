#ifndef __PLAYERCOMPONENT_HPP__
#define __PLAYERCOMPONENT_HPP__

#include <anax/Component.hpp>

#include <SFML/Window/Keyboard.hpp>

struct PlayerComponent : anax::Component<PlayerComponent>
{
	struct Controls
	{
		sf::Keyboard::Key up, down;
	}
	/// The controls of the player
	controls;
	
	
	/// Base speed of the player
	float baseSpeed;
};

#endif // __PLAYERCOMPONENT_HPP__