///
/// anax - Movement Example
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

#ifndef ANAX_EXAMPLES_MOVEMENT_PLAYERCOMPONENT_HPP
#define ANAX_EXAMPLES_MOVEMENT_PLAYERCOMPONENT_HPP

#include <anax/Component.hpp>

#include <SFML/Window/Keyboard.hpp>

struct PlayerComponent : anax::Component
{
    PlayerComponent() : 
        state(State::NO_STATE)
    {
    }

    /// The base speed of the player
    float baseSpeed;

    /// The current state of the player
    enum class State
    {
        NO_STATE = -1,
        DEFAULT_STATE = 0,
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_LEFT_SHOOT,
        MOVE_RIGHT_SHOOT,
        JUMP,
        SHOOT,
        JUMP_SHOOT
    } state;


    /// The controls the player has
    struct Controls
    {
        typedef sf::Keyboard::Key Key;

        Controls()
        : left(sf::Keyboard::Key::A),
        right(sf::Keyboard::Key::D),
        jump(sf::Keyboard::Key::W),
        shoot(sf::Keyboard::Key::Space)
        {
        }

        Controls(Key Left, Key Right, Key Jump, Key Shoot)
        : left(Left),
        right(Right),
        jump(Jump),
        shoot(Shoot)
        {
        }

        Key left, right, jump, shoot;
    } controls;
};

#endif // ANAX_EXAMPLES_MOVEMENT_PLAYERCOMPONENT_HPP
