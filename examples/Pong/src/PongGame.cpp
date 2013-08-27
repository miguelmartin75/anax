#include "PongGame.hpp"

PongGame::PongGame()
	: _isRunning(true)
{
	
}

PongGame::PongGame(sf::RenderTarget& renderTarget)
	: _isRunning(true),
      _renderTarget(&renderTarget)
{
}


PongGame::~PongGame()
{
	
}


void PongGame::init()
{
	
}

void PongGame::reset()
{
	
}

void PongGame::update(float deltaTime)
{
	// refresh the world
	_world.refresh();
	
	// now update the systems
	_systems.playerController.update(deltaTime);
	_systems.ai.update(deltaTime);
	_systems.movement.update(deltaTime);
	_systems.collision.update(deltaTime);
}

void PongGame::render()
{
	_systems.spriteRendering.render();
}

void PongGame::handleEvents(const sf::Event &event)
{
	if(event.type == sf::Event::Closed)
	{
		exit();
	}
}
