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
	: m_RenderTarget(&renderTarget),
	  m_SpriteRenderingSystem(renderTarget)
{
}

void Game::init()
{
	loadResources();
	
	//create player
	m_Player = m_World.createEntity();

	//add systems to world
	m_World.addSystem(m_SpriteRenderingSystem);
	m_World.addSystem(m_AnimationSystem);
	m_World.addSystem(m_PlayerInputSystem);
	m_World.addSystem(m_MovementSystem);	
	m_World.addSystem(m_CollisionSystem);
	
	//add this world to appropriate listener lists
	m_PlayerInputSystem.addListener(this);
	m_CollisionSystem.addListener(*this);	

	m_AnimationSystem.setFps(ANIMATION_FPS);
	
	auto& playerSprite = m_Player.addComponent<SpriteComponent>().sprite;
	
	//set sprite texture
	playerSprite.setTexture(m_TextureCache[PLAYER_TEXTURE_ID]);

	//load animations
	if(!m_Player.addComponent<AnimationComponent>().loadData("resources/meta/playerSpriteSheetFrames.txt"))
	{	
		std::cerr << "Failed to load animation data\n";
		quit();
	}

	auto& playerAnimation = m_Player.getComponent<AnimationComponent>();
	auto& playerTransform = m_Player.addComponent<TransformComponent>().transform;

	//add collision component
	auto& playerCollision = m_Player.addComponent<CollisionComponent>();
	playerCollision.causesEvents = true;
	playerCollision.BBox.width = playerAnimation.frameSize.x;
	playerCollision.BBox.height = playerAnimation.frameSize.y;
	
	//set player position to be in middle of screen
	playerTransform.setPosition(m_RenderTarget->getView().getSize().x / 2 - playerAnimation.frameSize.x / 2, m_RenderTarget->getView().getSize().y / 2 - playerAnimation.frameSize.y / 2);

	m_Player.addComponent<VelocityComponent>();
	auto& playerComp = m_Player.addComponent<PlayerComponent>();
	playerComp.baseSpeed = 100;

	//activate player	
	m_Player.activate();

	//create wall
	m_Wall = m_World.createEntity();
	
	//get wall sprite
	auto& wallSprite = m_Wall.addComponent<SpriteComponent>().sprite;

	//set wall sprite texture
	wallSprite.setTexture(m_TextureCache[WALL_TEXTURE_ID]);

	//create wall position component
	auto& wallTransform = m_Wall.addComponent<TransformComponent>().transform;
		
	//create wall collision component
	auto& wallCollision = m_Wall.addComponent<CollisionComponent>();
	wallCollision.causesEvents = true;
	wallCollision.BBox.width = wallSprite.getLocalBounds().width;
	wallCollision.BBox.height = wallSprite.getLocalBounds().height;

	//set wall position to be 3/4 to the right of screen, and on the same level as player
	wallTransform.setPosition(m_RenderTarget->getView().getSize().x * 0.75 - wallSprite.getLocalBounds().width / 2, (m_RenderTarget->getView().getSize().y / 2 - playerAnimation.frameSize.y / 2) - wallCollision.BBox.height / 2);

	m_Wall.activate();
}

void Game::update(float deltaTime)
{
	m_World.refresh();

	m_PlayerInputSystem.update(deltaTime);
	m_MovementSystem.update(deltaTime);
	m_AnimationSystem.update(deltaTime);
	m_CollisionSystem.update(deltaTime);	
}

void Game::render()
{
	//prepare screen for redraw
	m_RenderTarget->clear(CLEAR_COLOR);
	
	//render all entities in mSpriteRenderingSystem
	m_SpriteRenderingSystem.render();
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
	if(!m_TextureCache[PLAYER_TEXTURE_ID].loadFromFile("resources/textures/playerSpriteSheet.png"))
	{
		std::cerr << "Failed to load spritesheet\n";
		quit();
	}

	if(!m_TextureCache[WALL_TEXTURE_ID].loadFromFile("resources/textures/w.png"))
	{
		std::cerr << "Failed to load wall sprite\n";
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
	
	//get velocity component information from e1
	auto& velocityE1 = e1.getComponent<VelocityComponent>().velocity;

	auto xVel = velocityE1.x;
	auto yVel = velocityE1.y;
		
	//move backwards if a collision is detected
	auto& transformE1 = e1.getComponent<TransformComponent>().transform;
	transformE1.move(-xVel, -yVel);
}
