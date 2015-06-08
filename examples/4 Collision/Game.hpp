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

#ifndef ANAX_EXAMPLES_COLLISION_GAME_HPP
#define ANAX_EXAMPLES_COLLISION_GAME_HPP

#include <map>

#include <SFML/Graphics.hpp>
#include <anax/anax.hpp>

#include <BaseGame.hpp>

#include <Systems/AnimationSystem.hpp>
#include <Systems/SpriteRenderingSystem.hpp>
#include <Systems/MovementSystem.hpp>
#include <Systems/CollisionSystem.hpp>
#include <Systems/PlayerInputSystem.hpp>

class Game : 
    public BaseGame,
    public PlayerInputSystem::Listener,
    public CollisionSystem::Listener
{
public:
    /// Constructs Game with sf::RenderTarget
    Game(sf::RenderTarget& renderTarget);

    void init();

    void update(float deltaTime);

    void render();

    void handleEvents(sf::Event event);

    void loadResources();

private:

    virtual void onPlayerStateChanged(anax::Entity& e, PlayerComponent::State state) override;

    virtual void onCollisionOccured(anax::Entity& e1, anax::Entity& e2) override;

    /// Window for game to render to
    sf::RenderTarget* m_renderTarget;

    /// A texture cache
    std::map<std::string, sf::Texture> m_textureCache;

    /// An anax entity world
    anax::World m_world;

    SpriteRenderingSystem m_spriteRenderingSystem;
    AnimationSystem m_animationSystem;
    MovementSystem m_movementSystem;
    PlayerInputSystem m_playerInputSystem;
    CollisionSystem m_collisionSystem;

    anax::Entity m_player;
    anax::Entity m_wall;
};

#endif
