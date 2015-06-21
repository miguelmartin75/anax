///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///

#ifndef ANAX_DETAIL_ENTITYIDPOOL_HPP
#define ANAX_DETAIL_ENTITYIDPOOL_HPP

#include <vector>

#include <anax/Entity.hpp>

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

            explicit EntityIdPool(std::size_t poolSize);

            EntityIdPool(const EntityIdPool&) = delete;
            EntityIdPool(EntityIdPool&&) = delete;
            EntityIdPool& operator=(const EntityIdPool&) = delete;
            EntityIdPool& operator=(EntityIdPool&&) = delete;


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

            /// \return The amount of entities that this pool can store
            std::size_t getSize() const;

            /// Resizes the pool
            /// \param amount The amount you wish to resize
            void resize(std::size_t amount);

            /// Clears the pool
            /// \note This will invalidate every entity ID given out
            void clear();

        private:

            /// The default pool size
            std::size_t m_defaultPoolSize;

            /// The next ID to be used (if there is no IDs in the freelist)
            Entity::Id::int_type m_nextId;

            /// The entities ids that are available to be used
            std::vector<Entity::Id> m_freeList;

            /// The Entities that are within the pool
            /// Stored as a counter and the index is the index part of the ID
            std::vector<Entity::Id::int_type> m_counts;
        };
    }
}

#endif // ANAX_DETAIL_ENTITYIDPOOL_HPP
