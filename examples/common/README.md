This directory is a common directory that is shared between all examples.

# Design

This describes the common components and systems that are within this directory.

## Components

- `TransformComponent`
	- A component which describes the transform (position/rotation/scale) of an entity
- `AnimationComponent`
	- A component which describes 2d frame-by-frame animation
- `VelocityComponent`
	- A component which describes the velocity of an entity
- `SpriteComponent`
	- A component which describes a sprite for an entity
- `ColliderComponent`
	- A component which describes collision information about the entity
	
## Systems

- `SpriteRenderingSystem`
	- A system to handle sprite rendering
- `AnimationSystem`
	- A system which handles animation
- `CollisionSystem`
	- A system to handle collisions
- `MovementSystem`
	- A system to handle movement