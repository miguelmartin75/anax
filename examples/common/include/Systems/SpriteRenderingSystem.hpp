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

#ifndef ANAX_EXAMPLES_COMMON_SYSTEMS_SPRITERENDERINGSYSTEM_HPP
#define ANAX_EXAMPLES_COMMON_SYSTEMS_SPRITERENDERINGSYSTEM_HPP

#include <anax/System.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

struct SpriteComponent;
struct TransformComponent;

/// \brief A system that renders sprites
///
/// This system renders sprites, using SFML.
/// It uses entities with the following components:
///		- Transform
///		- Sprite
///
/// \author Miguel Martin
struct SpriteRenderingSystem : anax::System<anax::Requires<SpriteComponent, TransformComponent>>
{
    /// Construct a SpriteRenderingSystem with no render target
    SpriteRenderingSystem();

    /// Construct a SpriteRenderingSystem
    /// \param renderTarget The render target you wish to render to
    SpriteRenderingSystem(sf::RenderTarget& renderTarget);

    /// Renders the system
    void render();

    /// Sets the render target
    /// \param renderTarget
    void setRenderTarget(sf::RenderTarget& renderTarget);

    /// \return The render target this system is rendering to
    sf::RenderTarget& getRenderTarget() const;

    /// Determines if this system is valid or not
    /// \return true if this system is value, false otherwise
    bool isValid() const;

private:

    /// The render target to render to
    sf::RenderTarget* m_renderTarget;
};

#endif // ANAX_EXAMPLES_COMMON_SYSTEMS_SPRITERENDERINGSYSTEM_HPP
