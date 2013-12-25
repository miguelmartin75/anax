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

#include <iostream>

#include <Components/TransformComponent.hpp>
#include <Components/SpriteComponent.hpp>
#include <Components/AnimationComponent.hpp>
#include <Components/VelocityComponent.hpp>
#include "BodyComponent.hpp"
#include "PlayerComponent.hpp"

const std::string PLAYER_TEXTURE_ID{"player"};
const sf::Color CLEAR_COLOR{60, 60, 60};

Game::Game(sf::RenderTarget& renderTarget)
	: _renderTarget(&renderTarget),
	  _spriteRenderingSystem(renderTarget)
{
}

void Game::init()
{
	// load any resources we may require
	loadResources();
	
	// add the necessary systems to the world
	_world.addSystem(_spriteRenderingSystem);
	_world.addSystem(_animationSystem);
	_world.addSystem(_playerInputSystem);
    _world.addSystem(_movementSystem);

    _playerInputSystem.addListener(this);

	// create the player
	_player = _world.createEntity();
	
	auto& playerSprite = _player.addComponent<SpriteComponent>().sprite;
	playerSprite.setTexture(_textureCache[PLAYER_TEXTURE_ID]);
	
	// load the animations
	if(!_player.addComponent<AnimationComponent>().loadData("resources/meta/playerSpriteSheetFrames.txt"))
	{
		std::cerr << "Failed to load animation data\n";
		quit();
	}
	
	auto& playerAnimaton = _player.getComponent<AnimationComponent>();
	auto& playerTransform = _player.addComponent<TransformComponent>().transform;
	playerTransform.setPosition(_renderTarget->getView().getSize().x / 2 - playerAnimaton.frameSize.x / 2, _renderTarget->getView().getSize().y / 2 - playerAnimaton.frameSize.y / 2);
	
	_player.addComponent<VelocityComponent>();
	
	auto& playerComp = _player.addComponent<PlayerComponent>();
	playerComp.baseSpeed = 10;

    _player.addComponent<BodyComponent>();
	
	// activate the player
	_player.activate();
}

void Game::update(float deltaTime)
{
	_world.refresh();

    _playerInputSystem.update(deltaTime);
	_movementSystem.update(deltaTime);
	_animationSystem.update(deltaTime);
}

void Game::render()
{
	_renderTarget->clear(CLEAR_COLOR);
	_spriteRenderingSystem.render();
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
	if(!_textureCache[PLAYER_TEXTURE_ID].loadFromFile("resources/textures/playerSpriteSheet.png"))
	{
		std::cerr << "Failed to load spritesheet\n";
		quit();
	}
}

void Game::onPlayerStateChanged(anax::Entity& e, PlayerComponent::State state)
{
    static const std::string stateNames[] = { "idle", "run", "run", "run_shoot", "run_shoot", "jump", "shoot", "jump_shoot" };
    if(e.hasComponent<AnimationComponent>())  
        e.getComponent<AnimationComponent>().playingState = stateNames[static_cast<unsigned int>(state)];
}
