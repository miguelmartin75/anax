///
/// Example1
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
///
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is hereby granted, free of charge, to any person
/// obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// 1. The origin of this software must not be misrepresented;
///    you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment
///    in the product documentation would be appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such,
///	   and must not be misrepresented as being the original software.
///
/// 3. The above copyright notice and this permission notice shall be included in
///    all copies or substantial portions of the Software.
///

#include "PlayerInputSystem.hpp"

#include <algorithm>

#include <SFML/Window/Keyboard.hpp>

#include <Components/VelocityComponent.hpp>
#include "PlayerComponent.hpp"


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
            velocity.x = -playerComp.baseSpeed;
            if(shootKeyPressed)
            {
                setPlayerState(e, playerComp, PlayerComponent::State::MOVE_LEFT_SHOOT); 
            }
            else
            {
                setPlayerState(e, playerComp, PlayerComponent::State::MOVE_LEFT); 
            }
		}
		else if(sf::Keyboard::isKeyPressed(playerComp.controls.right))
		{
            velocity.x = playerComp.baseSpeed;
            if(shootKeyPressed)
            {
                setPlayerState(e, playerComp, PlayerComponent::State::MOVE_RIGHT_SHOOT); 
            }
            else
            {
                setPlayerState(e, playerComp, PlayerComponent::State::MOVE_RIGHT_SHOOT); 
            }
		}
        else
        {
            velocity.x = 0;
        }
	}
}


void PlayerInputSystem::setPlayerState(anax::Entity& e, PlayerComponent& p, PlayerComponent::State state)
{
    p.state = state;
    for(auto& l : _listeners)
    {
        l->onPlayerStateChanged(e, state);
    }
}
