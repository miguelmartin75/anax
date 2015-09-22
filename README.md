# anax [![Build Status](https://travis-ci.org/miguelmartin75/anax.svg?branch=master)](https://travis-ci.org/miguelmartin75/anax)

anax is an open source C++ entity system designed to be portable, lightweight and easy to use. It is aimed toward Game Development, however it would be possible to use it for other projects.

# What's an Entity System?

An entity system, or entity component system is a pattern for building complex extensible projects (typically games). It separates functionality into three major parts: components, systems and entities. Where entities are used to describe an object within the game, components are used to store data for the entities to describe them, and systems are used to contain game logic.

You can read about them further [here](https://github.com/miguelmartin75/anax/wiki/What-is-an-Entity-System%3F).

# Getting Started

## Dependencies
To compile, install, and use anax, a C++11 compliant compiler is required.

## Installation

```
(mkdir -p build && cmake .. && make install)
```

A more detailed tutorial on how to install is available on the [wiki](https://github.com/miguelmartin75/anax/wiki/Getting-Started).

# Quick Tutorial

This section will explain how to use the library, but it will not go into much specific detail. If you want a more detailed guide, please refer to this [page](https://github.com/miguelmartin75/anax/wiki/Using-the-Library) on the [wiki].

> #### **NOTE:**
> It is assumed you know what an [Entity System](https://github.com/miguelmartin75/anax/wiki/What-is-an-Entity-System%3F) is.

### The World

A World is used to describe you game world or 'entity system' if you will. You must always have at least have one World object in order to use anax. e.g.

```c++
World world;
```

### Entities

An entity is what you use to describe an object in your game. e.g. a player, a gun, etc. To create entities, you must have a World object, and call `createEntity()` on the World object.

```c++
World world;
// ... 
Entity entity = world.createEntity();
```

Entities are implemented as an identifier (32 or 64 bits). The Entity objects have a reference to the World object, and may be accessed via `getWorld()`. The `Entity` class acts as a handle to entities, you can think of it as a pointer. You may have multiple `Entity` handles to represent the same entity, e.g.

```c++
Entity entity1 = world.createEntity();
Entity entity2 = entity1; // entity2 and entity1 "point" to the same entity
```

To destroy/kill an entity, you can either call `World::killEntity` or `Entity::kill`. e.g.

```c++
entity.kill();
// or
world.killEntity(entity);
```

Once you have killed an entity, other copies of your entity handles will automatically be invalidated and will not be of use (an assertion will occur if you attempt to use an invalidated entity). e.g.

```c++
Entity entity1 = world.createEntity();
Entity entity2 = entity1;

entity1.kill();

// This will cause an assertion
// see below for details about this member function
entity2.addComponent<Position>(0, 3, 5);
``` 
	
### Components

A Component is used to describe data for an Entity, for example: the position, velocity, etc. To define your own component, you simply inherit from `Component`.

```c++
struct PositionComponent : anax::Component
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

// removing components
entity.removeComponent<PositionComponent>();

// getting components
auto pos = entity.getComponent<PositionComponent>();
```

### Systems

A System is used to contain on entities with specific components (require or exclude a set of component types). It is typically used to update, render or perform some logic these entities. 

```c++
struct MovementSystem : anax::System<anax::Requires<PositionComponent, VelocityComponent>>
{
	// ...
};
```

That is, a movement system requires entities with a `PositionComponent` and `VelocityComponent`. You may determine if an entity is removed/added to the system via these two override-able (virtual) methods:

- `onEntityAdded(Entity&)`
- `onEntityRemoved(Entity&)`

That's basically it, you can pretty much go and code. If you want more details, check the documentation or [this](https://github.com/miguelmartin75/anax/wiki/Using-the-Library) getting started guide on the [wiki].

# Get Involved

Want to get involved with the project? You are free to help out on the project, but please see the `CONTRIBUTING.md` file before doing so.

Also, don't be afraid to send pull requests, especially for those that fix bugs ([email] me if you're unsure)!

# License

See [LICENSE](LICENSE).

[wiki]: https://github.com/miguelmartin75/anax/wiki
[CMake]: http://www.cmake.org/
[Entity Systems]:http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/)
[Artemis]: http://gamadu.com/artemis/
[boost]: http://boost.org/
[email]: mailto:miguel@miguel-martin.com
