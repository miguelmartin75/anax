///
/// anax tests
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

#ifndef ANAX_TESTS_SYSTEMS_HPP
#define ANAX_TESTS_SYSTEMS_HPP

#include <stdexcept>

#include <anax/System.hpp>

#include "Components.hpp"

class MovementSystem : public anax::System<anax::Requires<PositionComponent, VelocityComponent>>
{
public:

    void update()
    {
        auto entities = getEntities();
        for(auto& e : entities)
        {			
            auto& position = e.getComponent<PositionComponent>();
            auto& velocity = e.getComponent<VelocityComponent>();

            position.x += velocity.x;
            position.y += velocity.y;
            position.z += velocity.z;
        }
    }

private:

    virtual void onEntityAdded(anax::Entity& e) override
    {
    }

    virtual void onEntityRemoved(anax::Entity& e) override
    {
    }
};

class PlayerSystem : public anax::System<anax::Requires<PlayerComponent>, anax::Excludes<NPCComponent>>
{
private:

    virtual void onEntityAdded(anax::Entity& e) override
    {
        if(e.hasComponent<NPCComponent>())
        {
            throw std::logic_error("Player contains NPCComponent, this goes against the component filter");
        }
    }


    virtual void onEntityRemoved(anax::Entity& e) override
    {
    }
};

#endif // ANAX_TESTS_SYSTEMS_HPP
