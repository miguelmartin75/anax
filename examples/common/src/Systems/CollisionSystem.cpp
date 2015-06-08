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

#include <Systems/CollisionSystem.hpp>

#include <iostream>
#include <algorithm>

CollisionSystem::Listener::~Listener()
{
}

static sf::FloatRect getBBoxRectFor(const sf::Transformable& transformable, const sf::FloatRect& bbox)
{
    return sf::FloatRect(transformable.getPosition().x + bbox.left, transformable.getPosition().y + bbox.top, bbox.width, bbox.height);
}

static sf::FloatRect getBBoxRectFor(const anax::Entity& entity)
{
    auto& transform = entity.getComponent<TransformComponent>().transform;
    auto& bbox = entity.getComponent<CollisionComponent>().boundingBox;
    return getBBoxRectFor(transform, bbox);
}

void CollisionSystem::update(double)
{
    auto colliders = getEntities();

    // Temporary values for rectangles (to check collision)
    sf::FloatRect rect1;
    sf::FloatRect rect2;	

    // NOTES:
    // 1. This is quite in-efficient, however this is just a simple example.
    // 2. This does NOT check for collision with rotation
    for(std::size_t i = 0; i < colliders.size(); ++i)
    {
        auto& e1 = colliders[i];
        if(!e1.getComponent<CollisionComponent>().causesEvents)
        {
            continue;
        }

        rect1 = getBBoxRectFor(e1);

        for(std::size_t j = i+1; j < colliders.size(); ++j)
        {
            auto& e2 = colliders[j];
            rect2 = getBBoxRectFor(e2);

            // Check for the collision
            if(rect1.intersects(rect2))
            {
                for(auto& listener : m_listeners)
                    listener->onCollisionOccured(e1, e2);
            }
        }
    }
}

void CollisionSystem::addListener(Listener &listener)
{
    m_listeners.push_back(&listener);
}

void CollisionSystem::removeListener(Listener &listener)
{
    m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), &listener), m_listeners.end());
}
