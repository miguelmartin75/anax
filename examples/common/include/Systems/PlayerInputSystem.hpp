///
/// Example1
/// Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)
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

#ifndef ANAX_EXAMPLES_MOVEMENT_PLAYERINPUTSYSTEM_HPP
#define ANAX_EXAMPLES_MOVEMENT_PLAYERINPUTSYSTEM_HPP

#include <algorithm>

#include <anax/System.hpp>

#include <Components/PlayerComponent.hpp>

struct VelocityComponent;

struct PlayerInputSystem : 
    anax::System<anax::Requires<PlayerComponent, VelocityComponent>>
{
public:

    struct Listener
    {
        virtual void onPlayerStateChanged(anax::Entity& e, PlayerComponent::State state) = 0;
    };


    void update(double deltaTime);

    void addListener(Listener* listener) { m_listeners.push_back(listener); }
    void removeListener(Listener* listener) { m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end()); }

private:

    void setPlayerState(anax::Entity& e, PlayerComponent&, PlayerComponent::State);

    std::vector<Listener*> m_listeners;
};

#endif // ANAX_EXAMPLES_MOVEMENT_PLAYERINPUTSYSTEM_HPP
