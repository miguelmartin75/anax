#ifndef ANAX_EXAMPLES_MOVEMENT_PLAYERCOMPONENT_HPP
#define ANAX_EXAMPLES_MOVEMENT_PLAYERCOMPONENT_HPP

#include <anax/Component.hpp>

#include <SFML/Window/Keyboard.hpp>

struct PlayerComponent : anax::Component<PlayerComponent>
{
	PlayerComponent()
		: state(State::NO_STATE)
	{
	}

	//base speed
	float baseSpeed;

	//players' state
	enum class State
	{
		NO_STATE = -1,
		DEFAULT_STATE = 0,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_LEFT_SHOOT,
		MOVE_RIGHT_SHOOT,
		JUMP,
		SHOOT,
		JUMP_SHOOT	
	} state;

	//controls for player
	struct Controls
	{
		typedef sf::Keyboard::Key Key;
		
		Controls()
			: left(sf::Keyboard::Key::A),
			  right(sf::Keyboard::Key::D),
			  jump(sf::Keyboard::Key::W),
		      shoot(sf::Keyboard::Key::Space)
		{
		}

		Controls(Key Left, Key Right, Key Jump, Key Shoot)
			: left(Left),
			  right(Right),
			  jump(Jump),
			  shoot(Shoot)
		{
		}
	
		Key left, right, jump, shoot;
	} controls;
};

#endif
