///
/// anax
/// Copyright (C) 2012-2013 Anax Creations. All rights reserved.
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

#ifndef __ANAX_ENTITYPROCESSINGSYSTEM_H__
#define __ANAX_ENTITYPROCESSINGSYSTEM_H__

#include "EntitySystem.h"

namespace anax
{
	/// \class EntityProcessingSystem
	/// \brief A class that is used to process one Entity at a time
	///
	/// If you do not need to control how to loop through Entities that are within an
	/// EntitySystem, then class is suggested for you.
	///
	/// \see BaseEntitySystem for more overrideable methods
	///
	/// \author Miguel Martin
	template <typename T>
	class EntityProcessingSystem
		: public EntitySystem<T>
	{
	public:
		
		typedef EntityProcessingSystem<T> Base;
		
		/// Default Constructor
		EntityProcessingSystem()
		{
		}
		
		/// Constructs an EntitySystem
		/// \param componentFilter The ComponentFilter you wish to construct the EntitySystem with
		EntityProcessingSystem(const ComponentFilter& componentFilter)
			: EntitySystem<T>(componentFilter)
		{
		}
		
		/// Destructor
		virtual ~EntityProcessingSystem() {}
	};
}

#endif // __ANAX_ENTITYPROCESSINGSYSTEM_H__