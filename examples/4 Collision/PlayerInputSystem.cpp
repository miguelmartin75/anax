#include "PlayerInputSystem.hpp"

#include <algorithm>

#include <SFML/Window/Keyboard.hpp>

#include <Components/VelocityComponent.hpp>
#include "PlayerComponent.hpp"

#include <iostream>

PlayerInputSystem::PlayerInputSystem()
	: Base(anax::ComponentFilter().requires<PlayerComponent, VelocityComponent>())
{
}

void PlayerInputSystem::update(double deltaTime)
{
	auto entities = getEntities();
	for(auto e : entities)
	{
		auto& playerComp = e.getComponent<PlayerComponent>();
		auto& velocity = e.getComponent<VelocityComponent>().velocity;

		bool shootKeyPressed = sf::Keyboard::isKeyPressed(playerComp.controls.shoot);

		if(sf::Keyboard::isKeyPressed(playerComp.controls.left))
		{
			std::cout << "Left key pressed\n";
			velocity.x = -playerComp.baseSpeed;
			setPlayerState(e, playerComp, shootKeyPressed ? PlayerComponent::State::MOVE_LEFT_SHOOT : PlayerComponent::State::MOVE_LEFT);
		}
	
		else if(sf::Keyboard::isKeyPressed(playerComp.controls.right))
		{
			std::cout << "Right key pressed\n";
			velocity.x = playerComp.baseSpeed;
			setPlayerState(e, playerComp, shootKeyPressed ? PlayerComponent::State::MOVE_RIGHT_SHOOT : PlayerComponent::State::MOVE_RIGHT);
		}

		else
		{
			velocity.x = 0;
			if(shootKeyPressed)
			{
				std::cout << "Shoot key pressed\n";
				setPlayerState(e, playerComp, PlayerComponent::State::SHOOT);
			}

			else
			{
				setPlayerState(e, playerComp, PlayerComponent::State::DEFAULT_STATE);
			}
		}
	}
}

void PlayerInputSystem::setPlayerState(anax::Entity& e, PlayerComponent& p, PlayerComponent::State state)
{
	if(p.state == state)
		return;

	p.state = state;

	for(auto& l : mListeners)
	{
		l->onPlayerStateChanged(e, state);
	}
}
