#ifndef ANAX_EXAMPLES_COLLISION_GAME_HPP
#define ANAX_EXAMPLES_COLLISION_GAME_HPP

#include <map>

#include <SFML/Graphics.hpp>
#include <anax/anax.hpp>

#include <BaseGame.hpp>

#include <Systems/AnimationSystem.hpp>
#include <Systems/SpriteRenderingSystem.hpp>
#include <Systems/MovementSystem.hpp>
#include <Systems/CollisionSystem.hpp>

#include "PlayerInputSystem.hpp"

class Game
	: public BaseGame,
	  public PlayerInputSystem::Listener,
	  public CollisionSystem::Listener
{
public:
	/// Constructs Game with sf::RenderTarget
	Game(sf::RenderTarget& renderTarget);

	void init();

	void update(float deltaTime);
	
	void render();

	void handleEvents(sf::Event event);
		
	void loadResources();

private:

	virtual void onPlayerStateChanged(anax::Entity& e, PlayerComponent::State state) override;

	virtual void onCollisionOccured(anax::Entity& e1, anax::Entity& e2) override;

	/// Window for game to render to
	sf::RenderTarget* mRenderTarget;
		
	/// A texture cache
	std::map<std::string, sf::Texture> mTextureCache;

	/// An anax entity world
	anax::World mWorld;

	SpriteRenderingSystem mSpriteRenderingSystem;

	AnimationSystem mAnimationSystem;

	MovementSystem mMovementSystem;

	PlayerInputSystem mPlayerInputSystem;

	CollisionSystem mCollisionSystem;

	//the player of the game
	anax::Entity mPlayer;
	
	//collidable object
	anax::Entity mWall;
};

#endif