# Example: 2 Animation

<p align="center">
<img src="animation.gif" alt="Screenshot">
</div>

This example provides a basic understanding of how frame-by-frame 2D animation can be implemented in an entity system.


# Controls

- Space
	- Play/pause animation
- S
	- Stop animation
- R
	- Toggle repeat mode (by default this is off)
- 0-9
	- Set the animation

# Details

## Animation

To see the details about how animation is implemented, please see the following files:

- [`examples/common/include/Components/AnimationComponent.hpp`](../common/include/Components/AnimationComponent.hpp)
- [`examples/common/include/Systems/AnimationSystem.hpp`](../common/include/Systems/AnimationSystem.hpp)
- [`examples/common/src/Systems/AnimationSystem.cpp`](../common/src/Systems/AnimationSystem.cpp)

## Game scene

To look at the details for how the program is ran and intergrated with the anax library, please see the following files:

- [`main.cpp`](main.cpp)
- [`Game.hpp`](Game.hpp)
- [`Game.cpp`](Game.cpp)

## Animation Data

To see the animation data and frames, please see the following files:

- [`examples/resources/meta/playerSpriteSheetFrames.txt`](../resources/meta/playerSpriteSheetFrames.txt)
- [`examples/resources/textures/playerSpriteSheet.png`](../resources/textures/playerSpriteSheet.png)
