///
/// anax
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
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

#ifndef __ANAX_ENTITY_HPP__
#define __ANAX_ENTITY_HPP__

#include <cstdint>

#include "config.hpp"

namespace anax
{
	class World;
	
	/// \brief A handle to an Entity within a World.
	///
	/// This class is used as a handle to an entity within a world.
	/// The handle can be invalid, as it "handle" no entity at all.
	///
	/// \todo
	/// Benchmark this against a plain old 64-bit Id (as in just use
	/// the ID class)
	///
	/// \author Miguel Martin
	class Entity
	{
	public:
		
		/// \brief A class to describe an ID for an entity
		///
		/// An ID for entity is composed of two values:
		/// - an index variable 
		/// - a counter variable
		///
		/// The index variable is used to locate components/location
		/// in the entity ID pool. The counter variable is used to
		/// determine if this ID is valid, and has not been killed.
		///
		/// \author Miguel Martin
		struct Id
		{
			typedef

#	ifdef ANAX_USE_32_BIT_IDS
			std::uint32_t
#	else
			std::uint64_t
#	endif // ANAX_USE_32_BIT_IDS
			
			int_type;
			
			/// Default constructor.
			/// \note
			/// This constructor will automatically nullify the ID
			Id()
				: index(0),
				  counter(0)
			{
			}
			
			/// Sets the index and counter variables of the ID
			/// \param Index The value for the index you wish to set
			/// \param Counter The value for the counter you wish to set
			Id(int_type Index, int_type Counter)
				: index(Index),
				  counter(Counter)
			{
			}
			
			/// \return The value of the ID, as an integer
			inline operator int_type() const
			{ return value(); }
			
			/// \return The value of the ID, as an integer
			inline int_type value() const
			{ return (counter << ANAX_ENTITY_ID_COUNTER_BIT_COUNT) | index; }
			
			/// Clears the ID by setting the index and counter to 0.
			void clear() { index = counter = 0; }
			
			/// Determines if the ID is null
			/// \return true if the ID is null
			bool isNull() const { return value() == 0; }
			
			int_type index : ANAX_ENTITY_ID_INDEX_BIT_COUNT;
			int_type counter : ANAX_ENTITY_ID_COUNTER_BIT_COUNT;
		};
		
		/// Default constructor
		Entity();
		
		Entity(const Entity&) = default;
		Entity(Entity&&) = default;
		Entity& operator=(const Entity&) = default;
		Entity& operator=(Entity&&) = default;
		
		
		/// Determines if this Entity handle is valid & able to be used.
		/// \note You should only use this for DEBUG builds
		///		  as checking if an Entity is valid may/may not
		///		  impact your performance.
		/// \return true if this Entity is valid, false otherwise
		bool isValid() const;
		
		/// \return The Entity's ID
		const Id& getId() const;
		
		/// \return The World that the Entity belongs to.
		/// \note This function will fail if the Entity is null.
		/// \see isNull() To check whether the Entity is null.
		World& getWorld() const;
		
		bool isActivated() const;
		
		void activate();
		
		void deactivate();
		
		void kill();
				
	private:
		
		/// \param world The World the entity belongs to
		/// \param id The designated ID of the Entity
		Entity(World& world, Id id);
		
		
		
		/// The ID of the Entity
		Id _id;
		
		/// The world that this Entity belongs to. This is guarenteed
		/// to not be null, as long as this entity is not null.
		/// \see isNull() To determine if the entity is null or not.
		World* _world;
		
		
		
		friend class World;
	};
}

#endif // __ANAX_ENTITY_HPP__