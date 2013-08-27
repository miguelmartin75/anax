This is just a simple example of the game pong. If you would like to read the design-specific detail about this example, please read the "Design" section.

# Features

- Single-player
- Multi-player

This has a very basic AI system, and this pong game is quite simple. Once you score 11, the game will automatically reset.

# Controls

- Press SPACE to play
- WASD for 1st player (left paddle) to move.
- Arrow keys for 2nd player (right paddle) to move (if in 2-player mode). 
- Press 1 to enter single-player mode.
- Press 2 to enter multi-player mode.



# Design

## Components

- `PaddleComponent`
	- A component which is used to identify a paddle within the game
- `BallComponent`
	- A component which is used to identify a ball within the game
- `ScoreComponent`
	- Contains the score for a player within pong
- `PlayerComponent`
	- Contains information about a player within the game (name, controls, etc.)
- `AIComponent`
	- An empty component to describe the AI

## Systems

- `PlayerControllerSystem`
	- A system which handles controlling all players within the game
- `AISystem`
	- A system which controls the AI of the game

## Entity Types

This describes the various entity types of the game.

- `Paddle`
	- `TransformComponent`
	- `SpriteComponent`
	- `VelocityComponent`
	- `ColliderComponent`
	- `ScoreComponent`
- `Player : Paddle`
	- `PlayerComponent`
- `AI : Paddle`
	- `AIComponent`
- `Ball`
	- `BallComponent`
	- `TransformComponent`
	- `SpriteComponent`
	- `ColliderComponent`
	- `VelocityComponent`
