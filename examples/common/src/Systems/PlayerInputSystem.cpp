///
/// Example1
/// Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)
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

#include <Systems/PlayerInputSystem.hpp>

#include <algorithm>

#include <SFML/Window/Keyboard.hpp>

#include <Components/VelocityComponent.hpp>


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
            setPlayerState(e, playerComp, shootKeyPressed ? PlayerComponent::State::MOVE_LEFT_SHOOT : PlayerComponent::State::MOVE_LEFT);
        }
        else if(sf::Keyboard::isKeyPressed(playerComp.controls.right))
        {
            velocity.x = playerComp.baseSpeed;
            setPlayerState(e, playerComp, shootKeyPressed ? PlayerComponent::State::MOVE_RIGHT_SHOOT : PlayerComponent::State::MOVE_RIGHT);
        }
        else
        {
            velocity.x = 0;
            if(shootKeyPressed) 
            {
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
    // pointless if you are going to reassign
    if(p.state == state)
        return;

    p.state = state;
    for(auto& l : m_listeners)
    {
        l->onPlayerStateChanged(e, state);
    }
}
