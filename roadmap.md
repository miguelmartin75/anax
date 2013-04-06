# Roadmap


This is a list of what features will be implemented/added in each version, and when to hopefully expect these features to be implemented by.

### NOTES:
>There may be a lot of refractoring of code, I will TAG each version, 
>so no need to worry about your code breaking (if you use my library).
>The only downfall of this is keeping the wiki up to date.


## V0.2 (current):

### STATUS:
COMPLETED

### DUE DATE:
20th January 2013

### FEATURES:
- Fix EntityManager class (still uses macros)
- *Examples!*


## V0.3:

### STATUS:
Under development

### DUE DATE:
Unspecified

### FEATURES:
- The library will be moved to a single namespace, most likely 
  	    called "anax". (no more two namespaces deep shit)
- C++11 support - the library WILL require C++11 code, unless I have an option to not use it.


## V0.4:

### STATUS
Incomplete

### DUE DATE:
Unspecified

### FEATURES:
- Possibily an an event system
	
e.g. (not actual code, just pseudo code)
	
```
#!cpp
struct CollisionEventArg : EventArg
{
	Entity *obj1, *obj2;
};
	
struct CollisionEventHandler : EventHandler<CollisionEventArg>
{
	virtual void onEvent(const CollisionEventArg& arg) override
	{
		cout << "Event occurred!\n";
	}
};
```

- OPTIMISATION - I will profile code and try to optimise it wherever I see fit


## V0.5:
---

### STATUS
Incomplete

### DUE DATE:
Unspecified

### FEATURES:
- Multi-threading support (if it is not possible to do so already)
- UUIDs in Entities (for networked games)

## MISC FEATURES:
---
Here are some miscellaneous features, which may be implemented at any time, or not at all.

- CMake build system support (this will be SO USEFUL)