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
	mWorld.addSystem(mPlayerInputSystem);
	mWorld.addSystem(mMovementSystem);	
	mWorld.addSystem(mCollisionSystem);
	
	//add this world to appropriate listener lists
	mPlayerInputSystem.addListener(this);
	mCollisionSystem.addListener(*this);	

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
	auto& playerTransform = mPlayer.addComponent<TransformComponent>().transform;

	//add collision component
	auto& playerCollision = mPlayer.addComponent<CollisionComponent>();
	playerCollision.causesEvents = true;
	playerCollision.BBox.width = playerAnimation.frameSize.x;
	playerCollision.BBox.height = playerAnimation.frameSize.y;
	
	//set player position to be in middle of screen
	playerTransform.setPosition(mRenderTarget->getView().getSize().x / 2 - playerAnimation.frameSize.x / 2, mRenderTarget->getView().getSize().y / 2 - playerAnimation.frameSize.y / 2);

	mPlayer.addComponent<VelocityComponent>();
	auto& playerComp = mPlayer.addComponent<PlayerComponent>();
	playerComp.baseSpeed = 100;

	//activate player	
	mPlayer.activate();

	//create wall
	mWall = mWorld.createEntity();
	
	//get wall sprite
	auto& wallSprite = mWall.addComponent<SpriteComponent>().sprite;

	//set wall sprite texture
	wallSprite.setTexture(mTextureCache[WALL_TEXTURE_ID]);

	//create wall position component
	auto& wallTransform = mWall.addComponent<TransformComponent>().transform;
		
	//create wall collision component
	auto& wallCollision = mWall.addComponent<CollisionComponent>();
	wallCollision.causesEvents = true;
	wallCollision.BBox.width = wallSprite.getLocalBounds().width;
	wallCollision.BBox.height = wallSprite.getLocalBounds().height;

	//set wall position to be 3/4 to the right of screen
	wallTransform.setPosition(mRenderTarget->getView().getSize().x * 0.75 - wallSprite.getLocalBounds().width / 2, mRenderTarget->getView().getSize().y * 0.47 - wallSprite.getLocalBounds().height / 2);

	mWall.activate();
}

void Game::update(float deltaTime)
{
	mWorld.refresh();

	mPlayerInputSystem.update(deltaTime);
	mMovementSystem.update(deltaTime);
	mAnimationSystem.update(deltaTime);
	mCollisionSystem.update(deltaTime);	
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
			}
	}
}

void Game::loadResources()
{
	if(!mTextureCache[PLAYER_TEXTURE_ID].loadFromFile("resources/textures/playerSpriteSheet.png"))
	{
		std::cerr << "Failed to load spritesheet\n";
		quit();
	}

	if(!mTextureCache[WALL_TEXTURE_ID].loadFromFile("resources/textures/w.png"))
	{
		std::cerr < "Failed to load wall sprite\n";
		quit();
	}
}

void Game::onPlayerStateChanged(anax::Entity& e, PlayerComponent::State state)
{
	std::cout << "State change called\n";
	static const std::string stateNames[] = { "idle", "run", "run", "shoot_run", "shoot_run", "jump", "shoot", "shoot_jump" };

	auto& spriteComp = e.getComponent<SpriteComponent>();
	
	if(e.hasComponent<AnimationComponent>())
	{
		auto& animationComp = e.getComponent<AnimationComponent>();
		auto stateName = stateNames[static_cast<unsigned>(state)];
		auto& animState = animationComp.states[stateName];

		auto x = animState.startPosition.x * animationComp.currentFrame.x;
		auto y = animState.startPosition.y * animationComp.currentFrame.y;
		auto width = animationComp.frameSize.x;
		auto height = animationComp.frameSize.y;

		spriteComp.sprite.setOrigin(static_cast<unsigned>(x + 0.5 * width), static_cast<unsigned>(y + 0.5 * height));

		std::cout << "state changed to: " << stateName << "\n";
		animationComp.play(stateName);
		if(state == PlayerComponent::State::JUMP || state == PlayerComponent::State::JUMP_SHOOT || state == PlayerComponent::State::SHOOT)
		{
			//dont repeat animation
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
			spriteComp.sprite.setScale(1, 1);
			break;
		case PlayerComponent::State::MOVE_RIGHT:
		case PlayerComponent::State::MOVE_RIGHT_SHOOT:
			spriteComp.sprite.setScale(-1, 1);
			break;
		default:
			break;
	}
}

void Game::onCollisionOccured(anax::Entity& e1, anax::Entity& e2)
{
	std::cout << "Collision fired!\n";
	
	//get velocity components from each entity
	auto& velocityE1 = e1.getComponent<VelocityComponent>().velocity;

	auto xVel = velocityE1.x;
	auto yVel = velocityE1.y;
		
	auto& transformE1 = e1.getComponent<TransformComponent>().transform;
	transformE1.move(-xVel, -yVel);
}
