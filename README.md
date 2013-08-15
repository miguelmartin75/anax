# anax v1.0

anax is an open source C++ entity system designed to be portable, lightweight and easy to use. It is aimed toward Game Development, however it would be possible to use it for other projects.

# What's an Entity System?

An entity system, or entity component system is a pattern for building complex extensible projects (typically games). It seperates funcality into three major parts: components, systems and entities. Where entities are used to describe an object within the game, components are used to store data for the entities to describe them, and systems are used to contain game logic.

You can read about them further [here](https://github.com/miguelishawt/anax/wiki/What-is-an-Entity-System%3F).

# Inspiration

Multiple blog posts/articles about entity systems inspired me to create my own C++ entity system library. Such as:

- [Entity Systems are the Future of MMORPG](http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/)
- [Entity Systems](http://www.tomseysdavies.com/2011/01/23/entity-systems/)

The [Artemis] Framework and [entityx] helped drag this project to what it is at the current moment.

# Getting Started

## Downloading the Library

There are multiple ways to download the library. Here are your options:

- [clone] the repo: `git clone https://github.com/miguelishawt/anax.git`
- Download the library ([zip]/[tar-gz])

## Dependencies

To compile, install, and use anax, the following libraries and C++ support is required:

- [`boost::dynamic_bitset`](http://www.boost.org/doc/libs/1_54_0/libs/dynamic_bitset/dynamic_bitset.html)
- [`std::unique_ptr`](http://en.cppreference.com/w/cpp/memory/unique_ptr)
- C++11 variadic templates (this is optional, but is reccomended)


## Installation

To install and build the library, you can use [CMake] or your own method of installation. However, it is recommended that you do use [CMake].

To build using CMake, use the following commands:

	mkdir build
	cd build
	cmake ..
	sudo make install

Where the directory build can be anything you wish, it just contains all temporary files CMake creates. 

> #### **NOTES:**
> 1. This will be different to Windows, as instead of using sudo
> you just have to run the command line as an administrator.
> 2. For Windows, you may also have to use the Visual Studio command line in order for it to build.
> 3. This is just a simple way to install/build the library, you can use the GUI of [CMake], pass arguments to `cmake` or use the command `ccmake` if you wish.
> 4. A more detailed tutorial on how to install will be avaliable on the [wiki](wiki-getting-started).

# Quick Tutorial

This section will explain how to use the library, but it will not go into much specific detail. If you want a more detailed guide, please refer to this [page](wiki-basic-tutorial) on the [wiki].

> #### **NOTE:**
> It is assumed you know what an Entity System is.

### The World

A World is used to decsribe you game world. You must always have at least one World object allocated in order to use anax.

You create World objects like any other object:

```c++
World world;
// or
World* world = new World;
```

### Entities

An entity is what you use to describe an object in your game. e.g. a player, a gun, etc. To create entities, you must have a World object allocated, and call `createEntity()` on the World object.

```c++
World world;
// ... 
Entity entity = world.createEntity();
```
	
Entities are implemented as an identifier (32 or 64 bits). The Entity objects have a reference to the World object, and may be accessed through the getter `getWorld()`. The `Entity` class acts as a handle to entities, you can think of it as a pointer. You may have multiple `Entity` handles to represent the same entity, e.g.

```c++
Entity entity1 = world.createEntity();
Entity entity2 = entity1;
```

There is no problem with that. To destroy/kill an entity, you can either call `World::killEntity` or `Entity::kill`. e.g.

```c++
Entity entity = world.createEntity();
	
entity.kill();
// or
world.killEntity(entity);
```

Once you have killed an entity, other copies of your entity handles will automatically be invalidated and will not be of use (a run-time error will occur (an assertion), in DEBUG builds). e.g.

```c++
Entity entity1 = world.createEntity();
Entity entity2 = entity1;

entity1.kill();

// This will cause a run-time error
entity2.addComponent<Position>(0, 3, 5); // see below for details about this method
``` 
	
### Components

A Component is used to describe data for an Entity, for example: the position, velocity, etc. To define your own component, you simply inherit from `Component<T>` where `T` is the type of component you are defining.


```c++
class PositionComponent
	: public anax::Component<PositionComponent>
{
	// ...
};
```

You may add/remove/get components to entities through the public methods defined in the entity class.

- `addComponent`
- `removeComponent`
- `getComponent`

e.g.

```c++
// adding components
entity.addComponent<PositionComponent>(2, 3, 5);
entity.addComponent(new PositionComponent(2, 3, 5));

// removing components
entity.removeComponent<PositionComponent>();

// getting components
auto pos = entity.getComponent<PositionComponent>();
```

### Systems

A System is used to contain entities with specific components. It usually is used to update/render these entities. You define a system much like you define a component, you inherit `System<T>` where `T` is the type of system you are defining.

```c++
class MovementSystem
	: public anax::System<MovementSystem>
{
	// ...
};
```

In order to filter out entities, you must use create a `ComponentFilter` and hand it to the base class's ctor. There is a handy `Base` typedef defined in the `System<T>` class for you to use.

e.g.

```c++
class MovementSystem
	: public anax::System<MovementSystem>
{
public:
	
	MovementSystem()
		: Base(ComponentFilter().requires<PositionComponent, VelocityComponent>())
	{
	}
	
	// ...
};
```

That is, a movement system requires entities with a `PositionComponent` and `VelocityComponent`. You may determine if an entity is removed/added to the system via these two overrideable (virtual) methods:

- `onEntityAdded(Entity&)`
- `onEntityRemoved(Entity&)`

That's basically it, you can pretty go and code. If you want more detail, check the documentation or [this](wiki-basic-tutorial) getting started guide on the [wiki].


# Get Involved

Want to get involved with the project? You are free to help out on the project, here are the possible methods to help out:

- The Code
	- Implement requested features
	- Implement new features
    - Optimise code
    - Fix bugs
    - Help create/fix documentation
- The [wiki]
	- Create video/written tutorials; this can be done by:
		- Adding links to tutorials on the [wiki]
		- Writing a tutorial on the [wiki]

If you do help out, [email] me and I'll put your name in the contributers list.

# License
Copyright (C) 2013 Miguel Martin ([miguel.martin7.5@hotmail.com](email))

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment
   in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.

3. The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.


[wiki]: https://github.com/miguelishawt/anax/wiki
[wiki-getting-started]: https://github.com/miguelishawt/anax/wiki/Getting-Started
[wiki-basic-tutorial]: https://github.com/miguelishawt/anax/wiki/Using-the-Library
[CMake]: http://www.cmake.org/
[Entity Systems]:http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/)
[Artemis]: http://gamadu.com/artemis/
[entityx]: https://github.com/alecthomas/entityx
[boost]: http://boost.org/
[email]: mailto:miguel.martin7.5@hotmail.com
[clone]: github-mac://openRepo/https://github.com/miguelishawt/anax
[zip]: https://api.github.com/repos/miguelishawt/anax/zipball
[tar-gz]: https://api.github.com/repos/miguelishawt/anax/tarball
