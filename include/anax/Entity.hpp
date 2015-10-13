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

#ifndef ANAX_ENTITY_HPP
#define ANAX_ENTITY_HPP

#include <type_traits>
#include <utility>
#include <cstdint>

#include <anax/detail/ClassTypeId.hpp>
#include <anax/detail/ComponentTypeList.hpp>

#include <anax/Component.hpp>
#include <anax/Config.hpp>

namespace anax
{
    class World;

    /// \brief A handle to an Entity within a World
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

#   ifdef ANAX_32_BIT_ENTITY_IDS
            std::uint32_t
#   else
            std::uint64_t
#   endif // ANAX_32_BIT_ENTITY_IDS

            int_type;

            /// Default constructor
            /// \note
            /// This constructor will automatically nullify the ID
            Id() : 
                index(0),
                counter(0)
            {
            }

            /// Sets the index and counter variables of the ID
            /// \param Index The value for the index you wish to set
            /// \param Counter The value for the counter you wish to set
            Id(int_type Index, int_type Counter) : 
                index(Index),
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

        /// \param world The World the entity belongs to
        /// \param id The designated ID of the Entity
        /// \note You should not call this ctor
        Entity(World& world, Id id);

        /// Default copy/move ctors and assignment operators
        Entity(const Entity&) = default;
        Entity(Entity&&) = default;
        Entity& operator=(const Entity&) = default;
        Entity& operator=(Entity&&) = default;

        /// Determines if this Entity handle is valid & able to be used.
        /// \note You should only use this for DEBUG builds
        ///       as checking if an Entity is valid may/may not
        ///       impact your performance.
        /// \return true if this Entity is valid, false otherwise
        bool isValid() const;

        /// \return The Entity's ID
        const Id& getId() const;

        /// \return The World that the Entity belongs to.
        /// \note This function will fail if the Entity is null.
        /// \see isNull() To check whether the Entity is null.
        World& getWorld() const;

        /// \return true if this Entity is activated
        bool isActivated() const;

        /// Activates this Entity
        void activate();

        /// Deactivates this Entity
        void deactivate();

        /// Kills this Entity
        /// \see World::killEntity for an alternate way to kill an Entity
        void kill();

        /// Adds a component to the Entity
        /// \tparam The type of component you wish to add
        /// \param args The arguments for the constructor of the component
        template <typename T, typename... Args>
        T& addComponent(Args&&... args);

        /// Removes a component
        /// \tparam The type of component you wish to remove
        template <typename T>
        void removeComponent();

        /// Removes all the components attached to the Entity
        void removeAllComponents();

        /// Retrives a component from this Entity
        /// \tparam The type of component you wish to retrieve
        /// \return A pointer to the component
        template <typename T>
        T& getComponent() const;

        /// Determines if this Entity has a component or not
        /// \tparam The type of component you wish to check for
        /// \return true if this Entity contains a component
        template <typename T>
        bool hasComponent() const;

        /// \return All the components the Entity has
        ComponentArray getComponents() const;

        /// \return A component type list, which resembles the components
        /// this entity has attached to it
        detail::ComponentTypeList getComponentTypeList() const;

        /// Comparison operator
        bool operator==(const Entity& entity) const;
        bool operator!=(const Entity& entity) const { return !operator==(entity); }

    private:

        // wrappers to add components
        // so I may call them from templated public interfaces
        void addComponent(Component* component, detail::TypeId componentTypeId);
        void removeComponent(detail::TypeId componentTypeId);
        Component& getComponent(detail::TypeId componentTypeId) const;
        bool hasComponent(detail::TypeId componentTypeId) const;


        /// The ID of the Entity
        Id m_id;

        /// The world that this Entity belongs to. This is guarenteed
        /// to not be null, as long as this entity is not null.
        /// \see isNull() To determine if the entity is null or not.
        World* m_world;
    };

    template <typename T, typename... Args>
    T& Entity::addComponent(Args&&... args)
    {
        static_assert(std::is_base_of<Component, T>(), "T is not a component, cannot add T to entity");
        // TODO: align components by type
        auto component = new T{std::forward<Args>(args)...};
        addComponent(component, ComponentTypeId<T>());
        return *component;
    }

    template <typename T>
    void Entity::removeComponent()
    {
        static_assert(std::is_base_of<Component, T>(), "T is not a component, cannot remove T from entity");
        removeComponent(ComponentTypeId<T>());
    }

    template <typename T>
    T& Entity::getComponent() const
    {
        static_assert(std::is_base_of<Component, T>(), "T is not a component, cannot retrieve T from entity");
        return static_cast<T&>(getComponent(ComponentTypeId<T>()));
    }

    template <typename T>
    bool Entity::hasComponent() const
    {
        static_assert(std::is_base_of<Component, T>(), "T is not a component, cannot determine if entity has T");
        return hasComponent(ComponentTypeId<T>());
    }
}

#endif // ANAX_ENTITY_HPP
