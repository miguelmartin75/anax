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

#ifndef __ANAX_ENTITYFACTORY_H__
#define __ANAX_ENTITYFACTORY_H__

#include "anax/IdentifierPool.h"

#include "anax/Types.h"
#include "anax/Entity.h"

namespace anax
{
	class World;
	
	/// \class EntityFactory
	/// \brief A class that creates Entities
	///
	/// This class creates Entity objects.
	///
	/// \par
	/// This class is ONLY made to CREATE and DESTROY entities, nothing else.
	///
	/// \par
	/// You should not create instances of this class, the Scene class will do it for you.
	/// As it is very tighly coupled with the Scene class.
	///
	/// \author Miguel Martin
	class EntityFactory
	{
	public:
		
		/// Constructor
		EntityFactory();
		
		/// Destructor
		~EntityFactory();
		
		
		
		/// Creates an Entity
		/// \param scene The Scene you wish to attach the Entity to
		/// \return The Entity that the EntityManager has created
		EntityPtr createEntity(World& world);
		
		/// Destroys an Entity
		/// \param e The Entity you wish to destroy
		void destroyEntity(EntityPtr e);
		
		/// \return The total amount of Entity objects that have been created, from this EntityFactory
		size_t getCreatedEntityCount() const;
		
		/// \return The total amount of Entity objects that have been destroyed, from this EntityFactory
		size_t getDestroyedEntityCount() const;
		
		/// \return The amount of Entity objects that are currently alive (not destroyed), from this EntityFactory
		size_t getAliveEntityCount() const;
		
		/// Clears all the count variables
		/// \note
		/// This does not destroy any Entity objects, as it does not keep track of them
		void clearCountData();
		
	private:
		
		/// The total amount that has been created by the EntityFactory
		size_t _totalCreatedCount;
		
		/// The total amount of Entity objects that have been destroyed by this EntityFactory
		size_t _totalDestroyedCount;
		
		/// The amount of Entity objects that are alive, which were created by this EntityFactory
		size_t _aliveCount;
		
		
		
		// Prevent from copying; purposely not defined
		EntityFactory(const EntityFactory&);
		const EntityFactory& operator=(const EntityFactory&);
	};
}

#endif // __ANAX_ENTITYFACTORY_H__