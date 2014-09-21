# anax

anax is an open source C++ entity system designed to be portable, lightweight and easy to use. It is aimed toward Game Development, however it would be possible to use it for other projects.

# What's an Entity System?

An entity system, or entity component system is a pattern for building complex extensible projects (typically games). It seperates funcality into three major parts: components, systems and entities. Where entities are used to describe an object within the game, components are used to store data for the entities to describe them, and systems are used to contain game logic.

You can read about them further [here](https://github.com/miguelmartin75/anax/wiki/What-is-an-Entity-System%3F).

# Getting Started

## Downloading the Library

There are multiple ways to download the library. Here are your options:

- clone the repo: `git clone https://github.com/miguelmartin75/anax.git`
- Download the library ([zip]/[tar-gz])

## Dependencies
To compile, install, and use anax, a C++11 compiliant compiler is required.

and:

- [`boost::dynamic_bitset`](http://www.boost.org/doc/libs/1_54_0/libs/dynamic_bitset/dynamic_bitset.html)

## Installation

To install and build the library, you can use CMake or your own method of installation. However, it is recommended that you do use CMake. If you're on Mac/Linux or another Unix variation, then you can install the library quite simply via the [scripts](https://github.com/miguelmartin75/clean_install) provided in the repository.

### Step 1: cd

Ensure that the current directory is the repository's directory (i.e. `cd` into the repo). 

### Step 2: Clean

Run the `clean.sh` script.

### Step 3: Configure

Configure the libary via CMake. Whether this be via the command line (`cmake`), the command line GUI (`ccmake`), or the actual CMake GUI.

### Step 4: Install

Run the `install.sh` script to install the library automatically. The install script will build the library four times (two release and debug builds; both static and dynamic binaries) and install the header files once.

> #### **NOTES:**
> 1. For Windows, you may have to use the Visual Studio command line in order for it to build.
> 2. In Windows, unless you have a bash command line, you cannot run the scripts provided in the repository (sorry; if someone wants to add batch scripts to do what I have done above, that would be appreciated).

A more detailed tutorial on how to install is avaliable on the [wiki](https://github.com/miguelmartin75/anax/wiki/Getting-Started).

# Quick Tutorial

This section will explain how to use the library, but it will not go into much specific detail. If you want a more detailed guide, please refer to this [page](https://github.com/miguelmartin75/anax/wiki/Using-the-Library) on the [wiki].

> #### **NOTE:**
> It is assumed you know what an [Entity System](https://github.com/miguelmartin75/anax/wiki/What-is-an-Entity-System%3F) is.

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

That's basically it, you can pretty go and code. If you want more details, check the documentation or [this](https://github.com/miguelmartin75/anax/wiki/Using-the-Library) getting started guide on the [wiki].


# Get Involved

Want to get involved with the project? You are free to help out on the project, but please see the `CONTRIBUTING.md` file before doing so.

Also, don't be afraid to send pull requests, especially for those that fix bugs ([email] me if you're unsure)!

# License

See [[LICENSE]].

[wiki]: https://github.com/miguelmartin75/anax/wiki
[CMake]: http://www.cmake.org/
[Entity Systems]:http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/)
[Artemis]: http://gamadu.com/artemis/
[entityx]: https://github.com/alecthomas/entityx
[boost]: http://boost.org/
[email]: mailto:miguel@miguel-martin.com
[zip]: https://api.github.com/repos/miguelmartin75/anax/zipball
[tar-gz]: https://api.github.com/repos/miguelmartin75/anax/tarball
