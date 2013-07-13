# anax v1.0

anax is an open source C++ entity system designed to be portable, lightweight and easy to use. It is aimed toward Game Development, however it would be possible to use it for other projects.

# What's an Entity System?

An entity system, or entity component system is a pattern for building complex extensible projects (typically games). It seperates funcality into three major parts: components, systems and entities. Where entities are used to describe an object within the game, components are used to store data for the entities to describe them, and systems are used to contain game logic.

You can read about them further [here](https://github.com/miguelishawt/anax/wiki/What-is-an-Entity-System%3F).

# Inspiration

This entity system is originally inspired from the Java Framework, [Artemis], which provides an Entity System for the Java programming language. Further inspiration was recieved from [entityx]. Although those two frameworks are good, I felt it was necessary to alter and change them to my liking, mainly for performance reasons and just the right "feel".

# Getting Started

## Downloading the Library

There are multiple ways to download the library. Here are your options:

- [clone] the repo: `git clone https://github.com/miguelishawt/anax.git`
- Download the library ([zip]/[tar-gz])

## Dependices

To compile, install, and use anax, the following libraries and C++ support is required:

- [`boost::dynamic_bitset`](http://www.boost.org/doc/libs/1_54_0/libs/dynamic_bitset/dynamic_bitset.html)
- [`boost::shared_ptr`](http://www.boost.org/doc/libs/1_54_0/libs/smart_ptr/shared_ptr.htm) or [`std::shared_ptr`](http://en.cppreference.com/w/cpp/memory/shared_ptr) support
- C++11 variadic templates (this is optional, but is reccomended)

Unfortunately, at this time, this library does _not_ use [CMake](http://www.cmake.org/), since I currently do not know how to use it. Therefore you currently have these options:

1. Build the project with your own method (i.e. makefile, project files)
2. Include the source files (under the `include/` and `src/` directories) into your project

Either of these methods should work. Please note for the second method, you must have a search path to the `include/` directory.

### **NOTES**
> 
> 1. It is worth mentioning that I do have an Xcode project (since I develop with a Mac) within the repo at this current time of Version 0.2, you could use that. However I must mention that build settings may not work. If it doesn't check the build settings and look at the include/library search file paths settings, and change them to the directory in which boost library is located on your machine.
> 2. I __will__ add support for CMake, or an alternative automatic building system for this library

## Installation

Unfortunately, at this time, this library does _not_ use [CMake](http://www.cmake.org/), since I currently do not know how to use it. Therefore you currently have these options:

1. Build the project with your own method (i.e. makefile, project files)
2. Include the source files (under the `include/` and `src/` directories) into your project

Either of these methods should work. Please note for the second method, you must have a search path to the `include/` directory.

> #### **NOTES**
> 1. It is worth mentioning that I do have an Xcode project (since I develop with a Mac) within the repo at this current time of Version 0.2, you could use that. However I must mention that build settings may not work. If it doesn't check the build settings and look at the include/library search file paths settings, and change them to the directory in which boost library is located on your machine.
> 2. I ***will*** add support for CMake, or an alternative automatic building system for this library

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

There is no problem with that. To destroy/kill an entity, you can either call `World::killEntity` or `Entity::kill`. Once you have killed an entity, other copies of your entity handles will automatically be invalidated and will not be of use. e.g.

```c++
Entity entity = world.createEntity();
	
entity.kill();
// or
world.killEntity(entity);
```
	
### Components

A Component is used to describe data for an Entity, for example: the position, velocity, etc. To define your own component, you simply inherit from `Component<T>` where `T` is the type of component you are defining.


```c++
class PositionComponent
	: public anax::Component<PositionComponent>
{
};
```

You may add/remove/get components to entities through the public methods defined in the entity class.

e.g.

```c++
// adding components
entity.addComponent<PositionComponent(2, 3, 5);
entity.addComponent(std::make_shard<PositionComponent>(3, 5, 6));

// removing components
entity.removeComponent<PositionComponent>();
entity.removeComponent(myPositionComponent);

// getting components
auto pos = entity.getComponent<PositionComponent>();
```

### Systems

A System is used to contain entities with specific components. It usually is used to update/render these entities. You define a system much like you define a component, you inherit `System<T>` where `T` is the type of system you are defining.

```c++
class MovementSystem
	: public anax::System<MovementSystem>
{
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
};
```

That is, a movement system requires entities with a `PositionComponent` and `VelocityComponent`. You may determine if an entity is removed/added to the system via these two overrideable (virtual) methods:

- onEntityAdded(Entity&)
- onEntityRemoved(Entity&)

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
	- Create video/written tutorials (be add any links to the [wiki], or write it up on the wiki)
    - Fix spelling/grammar errors
	- Add examples to the [examples] repo

If you do help out, [email] me and I'll put your name in the contributers file.


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
[wiki-basic-tutorial]: https://github.com/miguelishawt/anax/wiki/Tutorial-Using-the-Library
[examples]: https://github.com/miguelishawt/anax-examples
[Entity Systems]:http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/)
[Artemis]: http://gamadu.com/artemis/
[entityx]: https://github.com/alecthomas/entityx
[boost]: http://boost.org/
[email]: mailto:miguel.martin7.5@hotmail.com
[clone]: github-mac://openRepo/https://github.com/miguelishawt/anax
[zip]: https://api.github.com/repos/miguelishawt/anax/zipball
[tar-gz]: https://api.github.com/repos/miguelishawt/anax/tarball