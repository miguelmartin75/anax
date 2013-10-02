///
/// Example1
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
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

#include <Components/TransformComponent.hpp>
#include <Components/SpriteComponent.hpp>

Game::Game(sf::RenderTarget& renderTarget)
	: _renderTarget(&renderTarget),
	  _spriteRenderingSystem(renderTarget)
{
}

void Game::init()
{
	loadResources();
	
	_world.addSystem(_spriteRenderingSystem);
	
	auto player = _world.createEntity();
	
	auto& playerSprite = player.addComponent<SpriteComponent>().sprite;
	playerSprite.setTexture(_textureCache["player"]);
	
	auto& playerTransform = player.addComponent<TransformComponent>().transform;
	playerTransform.setPosition(_renderTarget->getView().getSize().x / 2 - playerSprite.getLocalBounds().width / 2, _renderTarget->getView().getSize().y / 2 - playerSprite.getLocalBounds().height / 2);
	
	player.activate();
}

void Game::update(float deltaTime)
{
	_world.refresh();
}

void Game::render()
{
	_renderTarget->clear(sf::Color(94, 63, 107));
	_spriteRenderingSystem.render();
}

void Game::handleEvents(sf::Event event)
{
	if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		exit();
	}
}

void Game::loadResources()
{
	_textureCache["player"].loadFromFile("resources/textures/player.png");
}