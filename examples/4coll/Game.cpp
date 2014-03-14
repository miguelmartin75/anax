#include "Game.hpp"

#include <iostream>

#include <Components/TransformComponent.hpp>
#include <Components/SpriteComponent.hpp>
#include <Components/AnimationComponent.hpp>

const std::string PLAYER_TEXTURE_ID{"player"};
const sf::Color CLEAR_COLOR{ 60, 60, 60 };
const unsigned int ANIMATION_FPS = 5;

std::vector<std::string> animationStateNames;

Game::Game(sf::RenderTarget& renderTarget)
	: mRenderTarget(&renderTarget),
	  mSpriteRenderingSystem(renderTarget)
{
}

void Game::init()
{
	loadResources();
	
	//create player
	mPlayer = mWorld.createEntity();

	//add systems to world
	mWorld.addSystem(mSpriteRenderingSystem);
	mWorld.addSystem(mAnimationSystem);

	mAnimationSystem.setFps(ANIMATION_FPS);
	
	auto& playerSprite = mPlayer.addComponent<SpriteComponent>().sprite;
	
	//set sprite texture
	playerSprite.setTexture(mTextureCache[PLAYER_TEXTURE_ID]);

	//load animations
	if(!mPlayer.addComponent<AnimationComponent>().loadData("resources/meta/playerSpriteSheetFrames.txt"))
	{	
		std::cerr < "Failed to load animation data\n";
		quit();
	}

	auto& playerAnimation = mPlayer.getComponent<AnimationComponent>();
	playerAnimation.repeat = true;
	playerAnimation.isPlaying = true;

	auto& playerTransform = mPlayer.addComponent<TransformComponent>().transform;
	
	//set player position to be in middle of screen
	playerTransform.setPosition(mRenderTarget->getView().getSize().x / 2 - playerSprite.getLocalBounds().width / 2, mRenderTarget->getView().getSize().y / 2 - playerSprite.getLocalBounds().height / 2);

	animationStateNames.reserve(mPlayer.getComponent<AnimationComponent>().states.size());
	for(auto& state : mPlayer.getComponent<AnimationComponent>().states)
	{
		animationStateNames.emplace_back(state.first);
	}

	//activate player	
	mPlayer.activate();

	playerAnimation.playingState = animationStateNames[0];
}

void Game::update(float deltaTime)
{
	mWorld.refresh();
	mAnimationSystem.update(deltaTime);
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
				case sf::Keyboard::Key::Space:
				{
					// pause or play animation
					bool isPlaying = mPlayer.getComponent<AnimationComponent>().isPlaying = !mPlayer.getComponent<AnimationComponent>().isPlaying;
					std::cout << (isPlaying ? "Playing" : "Paused") << " animation\n";
				}
					break;
				case sf::Keyboard::Key::S:
				{
					std::cout << "Stoppped animation\n";
					mPlayer.getComponent<AnimationComponent>().stop();
				}
					break;

				case sf::Keyboard::Key::R:
				{
					//toggle repeat
					bool repeat = mPlayer.getComponent<AnimationComponent>().repeat = !mPlayer.getComponent<AnimationComponent>().repeat;
					std::cout << "Turned repeat " << (repeat ? "on" : "off") << "\n";
				}
					break;

				case sf::Keyboard::Key::Num0:
				case sf::Keyboard::Key::Num1:
				case sf::Keyboard::Key::Num2:
				case sf::Keyboard::Key::Num3:
				case sf::Keyboard::Key::Num4:
				case sf::Keyboard::Key::Num5:
				case sf::Keyboard::Key::Num6:
				case sf::Keyboard::Key::Num7:			
				case sf::Keyboard::Key::Num8:
				case sf::Keyboard::Key::Num9:
					unsigned int index = event.key.code - sf::Keyboard::Key::Num0;

					if(index >= animationStateNames.size())
						index = animationStateNames.size() - 1;

					std::cout << "Set anim: " << index << " - " << animationStateNames[index] << "\n";

					mPlayer.getComponent<AnimationComponent>().playingState = animationStateNames[index];
					mPlayer.getComponent<AnimationComponent>().reset();
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
