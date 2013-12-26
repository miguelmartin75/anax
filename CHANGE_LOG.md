# CHANGE LOG - anax

## 1.x

### 1.1
2013-08-04 Miguel Martin <miguel.martin7.5@hotmail.com>

- Added `World::getEntities()`
- Added `World::clear()`
- Added Movement example

### 1.0
2013-08-04 Miguel Martin <miguel.martin7.5@hotmail.com>

- Changed how Entities are stored
- Added unit tests
- Added CMake support
- Removed virtual process/update method in System classes, as not all systems require to be updated in a particular way
- Added C++11 support where necessary, e.g. for ComponentFilter
- Library requires C++11 now - may change in the future
- Added Rendering example
- Added Animation example

## 0.x

### 0.2.4

2013-03-25 Miguel Martin <miguel.martin7.5@hotmail.com>

- Refractored ac::es to anax namespace
- Removed examples (placing them in another repository)
- Renamed Scene to World
- Removed managers, and observer classes
- Reogranised library and renamed some files in library
- Changed logo

### 0.2.3

2013-01-13 Miguel Martin <miguel.martin7.5@hotmail.com>

- Patch number increased to 3
- No more macros!
- Updated README
- Added CHANGELOG
- Added LISENSE.txt
- Added BUGS
- Added ROADMAP.md
- Updated copyright text
- Removed static functions in ComponentFilter
- Added deltaTime variable in Scene
- Added Movement example
- Fixed destruction of Components when calling Entity::kill() or Scene::kill(EntityPtr)

### 0.1 

- Initial version of the library