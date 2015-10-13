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

#include "Game.hpp"

#include <iostream>

#include <Components/TransformComponent.hpp>
#include <Components/SpriteComponent.hpp>

const std::string PLAYER_TEXTURE_ID{"player"};
const sf::Color CLEAR_COLOR{60, 60, 60};


Game::Game(sf::RenderTarget& renderTarget) :
    m_renderTarget(&renderTarget),
    m_spriteRenderingSystem(renderTarget)
{
}

void Game::init()
{
    loadResources();

    // create the player
    auto player = m_world.createEntity();

    auto& playerSprite = player.addComponent<SpriteComponent>().sprite;
    playerSprite.setTexture(m_textureCache[PLAYER_TEXTURE_ID]);

    auto& playerTransform = player.addComponent<TransformComponent>().transform;
    playerTransform.setPosition(m_renderTarget->getView().getSize().x / 2 - playerSprite.getLocalBounds().width / 2, m_renderTarget->getView().getSize().y / 2 - playerSprite.getLocalBounds().height / 2);

    // activate the player
    player.activate();

    // Add the systems to the world
    m_world.addSystem(m_spriteRenderingSystem);
}

void Game::update(float deltaTime)
{
    m_world.refresh();
}

void Game::render()
{
    m_renderTarget->clear(CLEAR_COLOR);
    m_spriteRenderingSystem.render();
}

void Game::handleEvents(sf::Event event)
{
    switch(event.type)
    {
        case sf::Event::Closed:
            quit();
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
                case sf::Keyboard::Key::Escape:
                    quit();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Game::loadResources()
{
    if(!m_textureCache[PLAYER_TEXTURE_ID].loadFromFile("resources/textures/playerSpriteSheet.png"))
    {
        std::cerr << "Failed to load spritesheet\n";
        quit();
    }
}
