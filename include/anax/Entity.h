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

#ifndef __ANAX_ENTITY_H__
#define __ANAX_ENTITY_H__

#include "types.h"

namespace anax
{
	class World;
	class Entity
	{
	public:
		
		// ID for entity is composed of two values:
		// - a counter variable (16 bits)
		// - the index to the entity in the pool (48 bits)
		struct Id
		{
			Id()
				: index(0),
				  counter(0)
			{
			}
			
			Id(uint Index, uint Counter)
				: index(Index),
				  counter(Counter)
			{
			}
			
			inline operator uint() const
			{ return value(); }
			
			inline uint value() const
			{ return (counter << ANAX_ENTITY_ID_COUNTER_BIT_COUNT) | index; }
			
			/// Clears the ID by setting the index and counter to 0.
			void clear() { index = counter = 0; }
			
			uint index : ANAX_ENTITY_ID_INDEX_BIT_COUNT;
			uint counter : ANAX_ENTITY_ID_COUNTER_BIT_COUNT;
		};
		
		/// Resembles a null id for an entity
		static const Id NULL_ID;
		
		
		Entity();
		
		Entity(World& world_, Id id_);
		
		/// Determines if this Entity handle is able to be used.
		/// \note You should only use this for DEBUG builds
		///		  as checking if an Entity is valid may/may not
		///		  impact your performance.
		/// \return true if this Entity is valid, false otherwise
		bool isValid() const;
		
		/// Determines whether this Entity is a null entity
		/// \note This function should only be called for DEBUG builds.
		///	      As an Entity is only ever null if it is unassigned.
		/// \return true if this Entity is a null Entity, false otherwise.
		bool isNull() const;
		
		/// \return The Entity's ID
		const Id& getId() const;
		
		/// \return The World that the Entity belongs to.
		/// \note This function will fail if the Entity is null.
		/// \see isNull() To check whether the Entity is null.
		World& getWorld() const;
		
	private:
		
		/// The ID of the Entity
		Id _id;
		
		/// The world that this Entity belongs to. This is guarenteed
		/// to not be null, as long as this entity is not null.
		/// \see isNull() To determine if the entity is null or not.
		World* _world;
	};
}

#endif // __ANAX_ENTITY_H__