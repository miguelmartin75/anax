//
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

#ifndef ANAX_EXAMPLES_COMMON_BASEGAME_HPP
#define ANAX_EXAMPLES_COMMON_BASEGAME_HPP

#include <cassert>

/// \brief The base class for Game classes
///
/// This base class provides basic functions that
/// may be overriden to suit your game. Note that
/// run-time polymorphism is not used, hence you're
/// not technically overriding the methods; merely
/// hiding them.
///
/// \author Miguel Martin
class BaseGame
{
public:

    /// Default constructor
    BaseGame() : m_isRunning(true) { }

    /// Updates the game
    /// \param deltaTime The change in time
    /// \note You must define your own update method
    virtual void update(float deltaTime) = 0;

    /// Renders the game
    /// \note You must define your own render method
    virtual void render() = 0;

    /// Handles SFML events
    /// \note You must define your own handleEvents method
    virtual void handleEvents(sf::Event events) = 0;

    /// \return true if this Game is running
    bool isRunning() const { return m_isRunning; }

    /// Quits the game
    void quit() { m_isRunning = false; }

private:

    bool m_isRunning;
};

#endif // ANAX_EXAMPLES_COMMON_BASEGAME_HPP
