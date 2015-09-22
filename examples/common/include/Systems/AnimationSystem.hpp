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

#ifndef ANAX_EXAMPLES_COMMON_SYSTEMS_ANIMATIONSYSTEM_HPP
#define ANAX_EXAMPLES_COMMON_SYSTEMS_ANIMATIONSYSTEM_HPP

#include <vector>

#include <anax/System.hpp>

#include <Components/SpriteComponent.hpp>
#include <Components/AnimationComponent.hpp>

/// \brief A system that animates entities
///
/// This system animates entities. It uses entities with the following components:
///		- Sprite
///		- Animation
///
/// \author Miguel Martin
struct AnimationSystem : anax::System<anax::Requires<SpriteComponent, AnimationComponent>>
{
public:

    /// Updates the collision system
    /// \param deltaTime The change in time
    void update(double deltaTime);

    /// Sets the frame-rate at which animation occurs
    /// \param fps The frames per second you wish to set the frame-rate to
    void setFps(unsigned int fps) { m_fps = fps; }

    /// \return The frames per second the animation system plays animation
    unsigned int getFps() const { return m_fps; }

private:

    /// The frame rate of the animation
    unsigned int m_fps;
};

#endif // ANAX_EXAMPLES_COMMON_SYSTEMS_ANIMATIONSYSTEM_HPP
