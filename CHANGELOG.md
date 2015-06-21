## 1.x

### 1.1
2014-03-17 Miguel Martin <miguel@miguel-martin.com>

- Added `World::getEntities()`
- Added `World::clear()`
- Added Movement example
- Added Collision example (thanks to [johnmarinelli](https://github.com/johnmarinelli))
- Various bug fixes (thanks to [jabza](https://github.com/jabza) helping with these)
	- Fixed Entity::Id's being re-cycled incorrectly.
	- Fixed issue where re-activating Entities caused them to be re-added to
their Systems.
	- Added the ability for an empty Entity handle to check its validity
without asserting.
    - Removing Component caused crashes

### 1.0
2013-08-04 Miguel Martin <miguel@miguel-martin.com>

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

2013-03-25 Miguel Martin <miguel@miguel-martin.com>

- Refractory ac::es to anax namespace
- Removed examples (placing them in another repository)
- Renamed Scene to World
- Removed managers, and observer classes
- Reorganised library and renamed some files in library
- Changed logo

### 0.2.3

2013-01-13 Miguel Martin <miguel@miguel-martin.com>

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
