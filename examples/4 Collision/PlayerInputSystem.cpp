///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///

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

    for(auto& l : m_Listeners)
    {
        l->onPlayerStateChanged(e, state);
    }
}
