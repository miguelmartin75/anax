///
/// anax
/// Copyright (C) 2013 Anax Creations. All rights reserved.
///
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is hereby granted, free of charge, to any person
/// obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// 1. The origin of this software must not be misrepresented;
///    you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment
///    in the product documentation would be appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such,
///	   and must not be misrepresented as being the original software.
///
/// 3. The above copyright notice and this permission notice shall be included in
///    all copies or substantial portions of the Software.
///

#ifndef __ANAX_TYPES_H__
#define __ANAX_TYPES_H__

// TODO: remove

#include <vector>
#include <boost/dynamic_bitset.hpp>

namespace anax
{
	class Scene;
	class BaseComponent;
	class BaseEntitySystem;
	class BaseEntityManager;
	class Entity;
	
	/// A pointer to a Scene object
	typedef Scene* ScenePtr;
	
	/// A pointer to a Component object
	typedef BaseComponent* ComponentPtr;
	/// An array of ComponentPtr objects
	typedef std::vector<ComponentPtr> ComponentArray;
	
	
	
	/// Defines the ID for an Entity
	typedef size_t EntityId;
	
	/// A pointer to an Entity object
	typedef Entity* EntityPtr;
	/// A const pointer to an Entity object
	typedef const Entity* const ConstEntityPtr;
	/// An array of EntityPtr object
	typedef std::vector<EntityPtr> EntityArray;
	
	/// A pointer to an EntitySystem
	typedef BaseEntitySystem* EntitySystemPtr;
	/// An array of EntitySystemPtr objects
	typedef std::vector<EntitySystemPtr> EntitySystemArray;
	
	/// A pointer to an Entity Manager
	typedef BaseEntityManager* EntityManagerPtr;
	
	/// change this to float if double precision concerns you
	typedef double Seconds;
	
	/// A dynamic bit set
	typedef boost::dynamic_bitset<> DynamicBitSet;
}

#endif // __ANAX_TYPES_H__