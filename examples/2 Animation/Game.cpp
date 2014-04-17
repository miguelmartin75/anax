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
#include <Components/AnimationComponent.hpp>

const std::string PLAYER_TEXTURE_ID{"player"};
const sf::Color CLEAR_COLOR{60, 60, 60};
const unsigned int ANIMATION_FPS = 5;

std::vector<std::string> animationStateNames;

    Game::Game(sf::RenderTarget& renderTarget)
: m_renderTarget(&renderTarget),
    m_spriteRenderingSystem(renderTarget)
{
}

void Game::init()
{
    // load any resources we may require
    loadResources();

    // add the necessary systems to the world
    m_world.addSystem(m_spriteRenderingSystem);
    m_world.addSystem(m_animationSystem);

    m_animationSystem.setFps(ANIMATION_FPS);

    // create the player
    m_player = m_world.createEntity();

    auto& playerSprite = m_player.addComponent<SpriteComponent>().sprite;
    playerSprite.setTexture(m_textureCache[PLAYER_TEXTURE_ID]);

    // load the animations
    if(!m_player.addComponent<AnimationComponent>().loadData("resources/meta/playerSpriteSheetFrames.txt"))
    {
        std::cerr << "Failed to load animation data\n";
        quit();
    }

    auto& playerAnimaton = m_player.getComponent<AnimationComponent>();
    playerAnimaton.repeat = true;
    playerAnimaton.isPlaying = true;

    auto& playerTransform = m_player.addComponent<TransformComponent>().transform;
    playerTransform.setPosition(m_renderTarget->getView().getSize().x / 2 - playerAnimaton.frameSize.x / 2, m_renderTarget->getView().getSize().y / 2 - playerAnimaton.frameSize.y / 2);

    animationStateNames.reserve(m_player.getComponent<AnimationComponent>().states.size());
    for(auto& state : m_player.getComponent<AnimationComponent>().states)
    {
        animationStateNames.emplace_back(state.first);
    }

    // activate the player
    m_player.activate();

    playerAnimaton.playingState = animationStateNames[0];
}

void Game::update(float deltaTime)
{
    m_world.refresh();

    m_animationSystem.update(deltaTime);
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
                case sf::Keyboard::Key::Space:
                    {
                        // pause/play animation
                        bool isPlaying = m_player.getComponent<AnimationComponent>().isPlaying = !m_player.getComponent<AnimationComponent>().isPlaying;
                        std::cout << (isPlaying ? "Playing" : "Paused") << " animation\n";					
                    }
                    break;
                case sf::Keyboard::Key::S:
                    {
                        std::cout << "Stopped animation\n";
                        m_player.getComponent<AnimationComponent>().stop();
                    }
                    break;
                case sf::Keyboard::Key::R:
                    {
                        // toggle repeat
                        bool repeat = m_player.getComponent<AnimationComponent>().repeat = !m_player.getComponent<AnimationComponent>().repeat;
                        std::cout << "Turned repeat " << (repeat ? "on" : "off") << '\n';
                    }
                    break;
                    // max of 10 animations to choose from
                case sf::Keyboard::Key::Num0:
                case sf::Keyboard::Key::Num1:
                case sf::Keyboard::Key::Num2:
                case sf::Keyboard::Key::Num3:
                case sf::Keyboard::Key::Num4:
                case sf::Keyboard::Key::Num5:
                case sf::Keyboard::Key::Num6:
                case sf::Keyboard::Key::Num7:
                case sf::Keyboard::Key::Num8:
                case sf::Keyboard::Key::Num9:
                    unsigned int index = event.key.code - sf::Keyboard::Key::Num0;

                    if(index >= animationStateNames.size()) index = animationStateNames.size() - 1;
                    std::cout << "Set animation: " << index <<  " - " << animationStateNames[index] << '\n';

                    m_player.getComponent<AnimationComponent>().playingState = animationStateNames[index];
                    m_player.getComponent<AnimationComponent>().reset();
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
