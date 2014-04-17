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

#ifndef ANAX_EXAMPLES_MOVEMENT_PLAYERCOMPONENT_HPP
#define ANAX_EXAMPLES_MOVEMENT_PLAYERCOMPONENT_HPP

#include <anax/Component.hpp>

#include <SFML/Window/Keyboard.hpp>

struct PlayerComponent : anax::Component<PlayerComponent>
{
    PlayerComponent()
    : state(State::NO_STATE)
    {
    }

    //base speed
    float baseSpeed;

    //players' state
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

    //controls for player
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

#endif
