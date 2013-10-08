///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
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

#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <map>

#include <SFML/Graphics.hpp>
#include <anax/anax.hpp>

#include <Systems/SpriteRenderingSystem.hpp>

#include "BaseGame.hpp"

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
	sf::RenderTarget* _renderTarget;
	
	/// A texture cache
	std::map<std::string, sf::Texture> _textureCache;
	
	/// An anax entity world
	anax::World _world;
	
	/// The rendering system
	SpriteRenderingSystem _spriteRenderingSystem;
};



#endif // __GAME_HPP__