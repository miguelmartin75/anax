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

#include "Game.hpp"

#include <iostream>

#include <Components/TransformComponent.hpp>
#include <Components/SpriteComponent.hpp>
#include <Components/AnimationComponent.hpp>
#include <Components/VelocityComponent.hpp>
#include <Components/CollisionComponent.hpp>

const std::string PLAYER_TEXTURE_ID{"player"};
const std::string WALL_TEXTURE_ID{"wall"};

const sf::Color CLEAR_COLOR{ 60, 60, 60 };
const unsigned int ANIMATION_FPS = 5;

Game::Game(sf::RenderTarget& renderTarget) : 
    m_renderTarget(&renderTarget),
    m_spriteRenderingSystem(renderTarget)
{
}

void Game::init()
{
    loadResources();

    //create player
    m_player = m_world.createEntity();

    //add systems to world
    m_world.addSystem(m_spriteRenderingSystem);
    m_world.addSystem(m_animationSystem);
    m_world.addSystem(m_playerInputSystem);
    m_world.addSystem(m_movementSystem);	
    m_world.addSystem(m_collisionSystem);

    //add this world to appropriate listener lists
    m_playerInputSystem.addListener(this);
    m_collisionSystem.addListener(*this);	

    m_animationSystem.setFps(ANIMATION_FPS);

    auto& playerSprite = m_player.addComponent<SpriteComponent>().sprite;

    playerSprite.setTexture(m_textureCache[PLAYER_TEXTURE_ID]);

    if(!m_player.addComponent<AnimationComponent>().loadData("resources/meta/playerSpriteSheetFrames.txt"))
    {
        std::cerr << "Failed to load animation data\n";
        quit();
    }

    auto& playerAnimation = m_player.getComponent<AnimationComponent>();
    auto& playerTransform = m_player.addComponent<TransformComponent>().transform;

    auto& playerCollision = m_player.addComponent<CollisionComponent>();
    playerCollision.causesEvents = true;
    // NOTE: should have this in a file, but this'll do for now
    playerSprite.setOrigin(playerAnimation.frameSize.x / 2, playerAnimation.frameSize.y / 2);
    {
        constexpr int COLLISION_WIDTH = 32;
        constexpr int COLLISION_HEIGHT = 32;

        playerCollision.boundingBox = { (playerAnimation.frameSize.x - COLLISION_WIDTH) / 2 - playerSprite.getOrigin().x, 
                                        (playerAnimation.frameSize.y - COLLISION_HEIGHT) / 2 - playerSprite.getOrigin().y, 
                                        COLLISION_WIDTH, COLLISION_HEIGHT };
    }

    //set player position to be in middle of screen
    playerTransform.setPosition(m_renderTarget->getView().getSize().x / 2 - playerAnimation.frameSize.x / 2, m_renderTarget->getView().getSize().y / 2 - playerAnimation.frameSize.y / 2);

    m_player.addComponent<VelocityComponent>();
    auto& playerComp = m_player.addComponent<PlayerComponent>();
    playerComp.baseSpeed = 100;

    m_wall = m_world.createEntity();

    // get wall sprite
    auto& wallSprite = m_wall.addComponent<SpriteComponent>().sprite;
    wallSprite.setTexture(m_textureCache[WALL_TEXTURE_ID]);

    auto& wallTransform = m_wall.addComponent<TransformComponent>().transform;

    auto& wallCollision = m_wall.addComponent<CollisionComponent>();
    wallCollision.causesEvents = false;
    wallCollision.boundingBox = { { 0, 0 }, { wallSprite.getLocalBounds().width, wallSprite.getLocalBounds().height} };

    wallTransform.setPosition(m_renderTarget->getView().getSize().x * 0.75 - wallSprite.getLocalBounds().width / 2, 
                             (m_renderTarget->getView().getSize().y / 2 - playerAnimation.frameSize.y / 2) - wallCollision.boundingBox.height / 2);

    m_player.activate();
    m_wall.activate();
}

void Game::update(float deltaTime)
{
    m_world.refresh();

    m_collisionSystem.update(deltaTime);	
    m_animationSystem.update(deltaTime);
    m_playerInputSystem.update(deltaTime);
    m_movementSystem.update(deltaTime);
}

void Game::render()
{
    // prepare screen for redraw
    m_renderTarget->clear(CLEAR_COLOR);

    // render all entities
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

    if(!m_textureCache[WALL_TEXTURE_ID].loadFromFile("resources/textures/wall.png"))
    {
        std::cerr << "Failed to load wall sprite\n";
        quit();
    }
}

void Game::onPlayerStateChanged(anax::Entity& e, PlayerComponent::State state)
{
    static const std::string stateNames[] = { "idle", "run", "run", "shoot_run", "shoot_run", "jump", "shoot", "shoot_jump" };

    auto& sprite = e.getComponent<SpriteComponent>().sprite;

    if(e.hasComponent<AnimationComponent>())
    {
        auto& animationComp = e.getComponent<AnimationComponent>();
        auto& stateName = stateNames[static_cast<unsigned>(state)];

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

    switch(state)
    {
        case PlayerComponent::State::MOVE_LEFT:
        case PlayerComponent::State::MOVE_LEFT_SHOOT:
            sprite.setScale(1, 1);
            break;
        case PlayerComponent::State::MOVE_RIGHT:
        case PlayerComponent::State::MOVE_RIGHT_SHOOT:
            sprite.setScale(-1, 1);
            break;
        default:
            break;
    }
}

void Game::onCollisionOccured(anax::Entity& e1, anax::Entity& e2)
{
    if(e1 != m_player && e2 != m_player)
    {
        return;
    }

    auto& velocity = m_player.getComponent<VelocityComponent>().velocity;
    auto& transform = m_player.getComponent<TransformComponent>().transform;
    transform.move(-velocity);
}
