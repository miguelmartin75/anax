#ifndef ANAX_EXAMPLES_COLLISION_GAME_HPP
#define ANAX_EXAMPLES_COLLISION_GAME_HPP

#include <map>

#include <SFML/Graphics.hpp>
#include <anax/anax.hpp>

#include <BaseGame.hpp>
#include <Systems/SpriteRenderingSystem.hpp>

class Game
	: public BaseGame
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
	/// Window for game to render to
	sf::RenderTarget* mRenderTarget;
		
	/// A texture cache
	std::map<std::string, sf::Texture> mTextureCache;

	/// An anax entity world
	anax::World mWorld;

	SpriteRenderingSystem mSpriteRenderingSystem;
};

#endif
