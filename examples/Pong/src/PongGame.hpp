#include <anax/anax.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <Systems/SpriteRenderingSystem.hpp>
#include <Systems/CollisionSystem.hpp>
#include <Systems/MovementSystem.hpp>
#include <Systems/AISystem.hpp>
#include <Systems/PlayerControllerSystem.hpp>

class PongGame
{
public:
	
	/// Default constructor
	PongGame();
	
	/// Sets the render target once constructed
	/// \param renderTarget The target you wish to render the game to
	PongGame(sf::RenderTarget& renderTarget);
	
	/// Destructor
	~PongGame();
	
	/// Initializes the game
	void init();
	
	/// Initializes the game
	/// \param renderTarget The target you wish to render the game to
	void init(sf::RenderTarget& renderTarget) { setRenderTarget(renderTarget); init(); }
	
	/// Resets the game
	void reset();
	
	/// Updates the game
	/// \param deltaTime The change in time
	void update(float deltaTime);
	
	/// Renders the game
	void render();
	
	/// Handles all appropriate events
	/// \param event The event object you wish to handle
	void handleEvents(const sf::Event& event);
	
	/// Sets the render target
	/// \param renderTarget The target you wish to render the game to
	void setRenderTarget(sf::RenderTarget& renderTarget) { _renderTarget = &renderTarget; }
	
	/// \return The render target associated with the game
	sf::RenderTarget& getRenderTarget() const { return *_renderTarget; }
	
	void exit() { _isRunning = false; }
	
	bool isRunning() const { return _isRunning; }
	
private:
	
	/// Determines if the game is running or not
	bool _isRunning;
	
	/// The target to render the game to
	sf::RenderTarget* _renderTarget;
	
	/// The entity system world the game uses
	anax::World _world;
	
	struct
	{
		SpriteRenderingSystem spriteRendering;
		CollisionSystem collision;
		MovementSystem movement;
		AISystem ai;
		PlayerControllerSystem playerController;
	} _systems;
};