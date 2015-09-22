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

#ifndef ANAX_EXAMPLES_COMMON_SYSTEMS_COLLISIONSYSTEM_HPP
#define ANAX_EXAMPLES_COMMON_SYSTEMS_COLLISIONSYSTEM_HPP

#include <vector>

#include <anax/System.hpp>

#include <Components/TransformComponent.hpp>
#include <Components/CollisionComponent.hpp>

/// \brief A system that handles collisions
///
/// This system handles collisions. It uses entities with the following components:
///		- Transform
///		- Collision
///
/// \author Miguel Martin
struct CollisionSystem : anax::System<anax::Requires<TransformComponent, CollisionComponent>>
{
public:

    struct Listener
    {
        virtual ~Listener() = 0;

        /// Occurs when an Entity has collided with another entity
        /// \param e1 The first entity that has been collided with
        /// \param e2 The second entity that has been collided with
        /// \note e1 Is guarenteed to have the causesEvent flag to be true
        virtual void onCollisionOccured(anax::Entity& e1, anax::Entity& e2) = 0;
    };

    /// Updates the collision system
    /// \param deltaTime The change in time
    void update(double deltaTime);

    /// Adds a Listener to the CollisionSystem
    /// \param listener The Listener you wish to add
    void addListener(Listener& listener);

    /// Removes a Listener from the CollisionSystem
    /// \param listener The Listener you wish to remove
    void removeListener(Listener& listener);

private:

    /// The listeners apart of the CollisionSystem
    std::vector<Listener*> m_listeners;
};

#endif // ANAX_EXAMPLES_COMMON_SYSTEMS_COLLISIONSYSTEM_HPP
