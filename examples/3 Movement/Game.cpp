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
#include <Components/VelocityComponent.hpp>

const std::string PLAYER_TEXTURE_ID{"player"};
const sf::Color CLEAR_COLOR{60, 60, 60};

Game::Game(sf::RenderTarget& renderTarget) : 
    m_renderTarget(&renderTarget),
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
    m_world.addSystem(m_playerInputSystem);
    m_world.addSystem(m_movementSystem);

    m_playerInputSystem.addListener(this);

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
    auto& playerTransform = m_player.addComponent<TransformComponent>().transform;
    playerTransform.setPosition(m_renderTarget->getView().getSize().x / 2 - playerAnimaton.frameSize.x / 2, m_renderTarget->getView().getSize().y / 2 - playerAnimaton.frameSize.y / 2);

    m_player.addComponent<VelocityComponent>();

    auto& playerComp = m_player.addComponent<PlayerComponent>();
    playerComp.baseSpeed = 100;

    // activate the player
    m_player.activate();
}

void Game::update(float deltaTime)
{
    m_world.refresh();

    m_movementSystem.update(deltaTime);
    m_playerInputSystem.update(deltaTime);
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

void Game::onPlayerStateChanged(anax::Entity& e, PlayerComponent::State state)
{
    static const std::string stateNames[] = { "idle", "run", "run", "shoot_run", "shoot_run", "jump", "shoot", "shoot_jump" };

    auto& spriteComp = e.getComponent<SpriteComponent>();

    if(e.hasComponent<AnimationComponent>())
    {
        auto& animationComp = e.getComponent<AnimationComponent>();
        auto& stateName = stateNames[static_cast<unsigned>(state)];

        auto width = animationComp.frameSize.x;
        auto height = animationComp.frameSize.y;

        spriteComp.sprite.setOrigin(static_cast<unsigned>(0.5 * width), static_cast<unsigned>(0.5 * height)); 

        animationComp.play(stateName);  
        if(state == PlayerComponent::State::JUMP || state == PlayerComponent::State::JUMP_SHOOT || state == PlayerComponent::State::SHOOT)
        {
            // don't repeat animation for jumping
            // or shooting
            animationComp.repeat = false; 
        }
        else
        {
            animationComp.repeat = true;
        }
    }

    // flip the sprite if necessary
    // or do anything else specific for a state
    switch(state)
    {
        case PlayerComponent::State::MOVE_LEFT:
        case PlayerComponent::State::MOVE_LEFT_SHOOT:
            spriteComp.sprite.setScale(1, 1);
            break;
        case PlayerComponent::State::MOVE_RIGHT:
        case PlayerComponent::State::MOVE_RIGHT_SHOOT:
            spriteComp.sprite.setScale(-1, 1);
            break;
        default:
            break;
    }
}
