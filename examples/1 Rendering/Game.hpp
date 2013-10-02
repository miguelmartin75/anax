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
	
	Game(sf::RenderTarget&);
	
	void init();
	
	void update(float deltaTime);
	
	void render();
	
	void handleEvents(sf::Event event);
	
	void loadResources();
	
private:
	
	std::map<std::string, sf::Texture> _textureCache;
	
	anax::World _world;
	
	SpriteRenderingSystem _spriteRenderingSystem;
	
	sf::RenderTarget* _renderTarget;
};



#endif // __GAME_HPP__