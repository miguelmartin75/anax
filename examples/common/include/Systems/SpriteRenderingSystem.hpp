#ifndef __SPRITERENDERINGSYSTEM_HPP__
#define __SPRITERENDERINGSYSTEM_HPP__

#include <anax/System.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

/// \brief A system that renders sprites
///
/// This system renders sprites, using SFML.
/// It uses entities with the following components:
///		- Transform
///		- Sprite
///
/// \author Miguel Martin
struct SpriteRenderingSystem : anax::System<SpriteRenderingSystem>
{
	/// Construct a SpriteRenderingSystem with no render target
	SpriteRenderingSystem();
	
	/// Construct a SpriteRenderingSystem
	/// \param renderTarget The render target you wish to render to
	SpriteRenderingSystem(sf::RenderTarget& renderTarget);
	
	/// Renders the system
	void render();
	
	/// Sets the render target
	/// \param renderTarget
	void setRenderTarget(sf::RenderTarget& renderTarget);
	
	/// \return The render target this system is rendering to
	sf::RenderTarget& getRenderTarget() const;
	
	/// Determines if this system is valid or not
	/// \return true if this system is value, false otherwise
	bool isValid() const;
	
private:
	
	/// The render target to render to
	/// \note This is guarenteed to not be NULL
	sf::RenderTarget* _renderTarget;
};

#endif // __SPRITERENDERINGSYSTEM_HPP__