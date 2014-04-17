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

#ifndef ANAX_EXAMPLES_RENDERING_GAME_HPP
#define ANAX_EXAMPLES_RENDERING_GAME_HPP

#include <map>

#include <SFML/Graphics.hpp>
#include <anax/anax.hpp>

#include <BaseGame.hpp>
#include <Systems/SpriteRenderingSystem.hpp>

class Game
: public BaseGame
{
public:

    /// Constructs the Game with a sf::RenderTarget
    /// \param renderTarget The sf::RenderTarget you wish to set the game up with
    Game(sf::RenderTarget&);

    /// Initializes the game
    void init();

    /// Updates the game
    /// \param deltaTime The change in time
    void update(float deltaTime);

    /// Renders the game
    void render();

    /// Handles events
    /// \param event The event that will be handled
    void handleEvents(sf::Event event);

    /// Loads game resources
    void loadResources();

private:

    /// The target the game will render to
    sf::RenderTarget* m_renderTarget;

    /// A texture cache
    std::map<std::string, sf::Texture> m_textureCache;

    /// An anax entity world
    anax::World m_world;

    /// The rendering system
    SpriteRenderingSystem m_spriteRenderingSystem;
};



#endif // ANAX_EXAMPLES_RENDERING_GAME_HPP
