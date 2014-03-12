#include "Game.hpp"

#include <iostream>

#include <Components/TransformComponent.hpp>
#include <Components/SpriteComponent.hpp>

const std::string PLAYER_TEXTURE_ID{"player"};
const sf::Color CLEAR_COLOR{ 60, 60, 60 };

Game::Game(sf::RenderTarget& renderTarget)
	: mRenderTarget(&renderTarget),
	  mSpriteRenderingSystem(renderTarget)
{
}

void Game::init()
{
	loadResources();
	
	//create player
	auto player = mWorld.createEntity();
	
	auto& playerSprite = player.addComponent<SpriteComponent>().sprite;
	
	//set sprite texture
	playerSprite.setTexture(mTextureCache[PLAYER_TEXTURE_ID]);

	auto& playerTransform = player.addComponent<TransformComponent>().transform;
	
	//set player position to be in middle of screen
	playerTransform.setPosition(mRenderTarget->getView().getSize().x / 2 - playerSprite.getLocalBounds().width / 2, mRenderTarget->getView().getSize().y / 2 - playerSprite.getLocalBounds().height / 2);

	//activate player	
	player.activate();

	//add systems to world
	mWorld.addSystem(mSpriteRenderingSystem);
}

void Game::update(float deltaTime)
{
	mWorld.refresh();
}

void Game::render()
{
	//prepare screen for redraw
	mRenderTarget->clear(CLEAR_COLOR);
	
	//render all entities in mSpriteRenderingSystem
	mSpriteRenderingSystem.render();
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
			break;
		default:
			break;
	}
}

void Game::loadResources()
{
	if(!mTextureCache[PLAYER_TEXTURE_ID].loadFromFile("resources/textures/playerSpriteSheet.png"))
	{
		std::cerr << "Failed to load spritesheet\n";
		quit();
	}
}
