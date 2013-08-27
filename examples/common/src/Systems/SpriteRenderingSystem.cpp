#include <Systems/SpriteRenderingSystem.hpp>

#include <cassert>

#include <Components/SpriteComponent.hpp>
#include <Components/TransformComponent.hpp>

SpriteRenderingSystem::SpriteRenderingSystem()
	: Base(anax::ComponentFilter().requires<SpriteComponent, TransformComponent>())
{
}

SpriteRenderingSystem::SpriteRenderingSystem(sf::RenderTarget& renderTarget)
	: Base(anax::ComponentFilter().requires<SpriteComponent, TransformComponent>()), 
	  _renderTarget(&renderTarget)
{
}

void SpriteRenderingSystem::render()
{
	auto entities = getEntities();
	for(auto& entity : entities)
	{
		auto& sprite = entity.getComponent<SpriteComponent>().sprite;
		auto& transform = entity.getComponent<TransformComponent>().transform;
		
		_renderTarget->draw(sprite, transform.getTransform());
	}
}

void SpriteRenderingSystem::setRenderTarget(sf::RenderTarget& renderTarget)
{
	_renderTarget = &renderTarget;
}

sf::RenderTarget& SpriteRenderingSystem::getRenderTarget() const
{
	assert(isValid() && "Render system is not valid");
	return *_renderTarget;
}

bool SpriteRenderingSystem::isValid() const
{
	return _renderTarget == nullptr;
}