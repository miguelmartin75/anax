# Change Log - Anax
The change log was not tracked before version 0.2.3.

## 0.2.x

### 0.2.4

2013-03-25 Miguel Martin <miguel.martin7.5@hotmail.com>

- Renamed to anax
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