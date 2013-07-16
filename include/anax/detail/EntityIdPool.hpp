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

#ifndef __ANAX_DETAIL_ENTITYIDPOOL_HPP__
#define __ANAX_DETAIL_ENTITYIDPOOL_HPP__

#include <vector>

#include "../Entity.hpp"

namespace anax
{
	namespace detail
	{
		/// \brief A pool of entity IDs
		///
		/// Used to pool entity IDs, so they can be re-used.
		///
		/// \author Miguel Martin
		class EntityIdPool
		{
		public:
			
			/// Creates an Entity ID
			/// \return The newly created Entity ID
			Entity::Id create();
			
			/// Removes an ID from the pool
			/// \param id The ID you wish to remove
			/// \note
			/// The ID will be invalidated automatically
			/// once the entity ID is removed.
			void remove(Entity::Id id);
			
			/// \param The index you wish to access the Entity::Id at
			/// \return An Entity::Id at index
			Entity::Id get(std::size_t index) const;
			
			/// Determines if an Entity ID is valid
			/// \return true if the ID is valid
			bool isValid(Entity::Id id) const;
			
		private:
			
			/// The entities ids that are avaliable to be used
			std::vector<Entity::Id> _freeList;
			
			/// The Entities that are within the pool
			std::vector<Entity::Id> _entities;
		};
	}
}

#endif // __ANAX_DETAIL_ENTITYIDPOOL_HPP__
