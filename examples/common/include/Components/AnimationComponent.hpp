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

#ifndef ANAX_EXAMPLES_COMMON_COMPONENTS_ANIMATIONCOMPONENT_HPP
#define ANAX_EXAMPLES_COMMON_COMPONENTS_ANIMATIONCOMPONENT_HPP

#include <fstream>
#include <vector>
#include <map>

#include <anax/Component.hpp>
#include <anax/Config.hpp>
#include <SFML/Graphics/Sprite.hpp>


struct AnimationSystem;
/// \brief A component used to describe animation
///
/// \note This component assumes that all frames are equal size.
/// Thus if you would like frames that are not equal sizes,
/// you must change that.
///
/// \author Miguel Martin
struct AnimationComponent : anax::Component
{
    struct State
    {
        State() : startPosition{0, 0}, frameAmount{1, 0} {}

        /// The starting position of the animaton
        sf::Vector2u startPosition;

        /// The amount of frames in each direction
        sf::Vector2u frameAmount;

        /// The frame rate you wish to play the state at
        /// Set this to 0 if you wish to use the animation frame rate
        unsigned int frameRate;
    };

    AnimationComponent() : 
        currentFrame(0, 0), isPlaying(false), repeat(false)
    {
    }

#ifdef ANAX_VIRTUAL_DTORS_IN_COMPONENT
    virtual ~AnimationComponent() { }
#endif // ANAX_VIRTUAL_DTORS_IN_COMPONENT

    /// Plays an animation
    void play(const std::string& state)
    {
        playingState = state;
        isPlaying = true;
    }

    /// Resets the animation
    void reset()
    {
        currentFrame.x = 0;
        currentFrame.y = 0;
    }

    /// Pauses the animation
    void pause()
    {
        isPlaying = false;
    }

    /// Stops the animation
    void stop()
    {
        pause();
        reset();
    }

    /// Loads animation data from a stream
    /// \param stream the stream you wish to load data from
    bool loadData(std::istream& stream);

    /// Loads animation data from a filepath
    /// \param filepath The filepath to the file you wish to load data from
    bool loadData(const std::string& filepath) { std::ifstream stream{filepath}; return stream.is_open() ? loadData(stream) : false; }

    /// The size of each frame
    sf::Vector2u frameSize;

    /// A map to describe the animations the entity has
    std::map<std::string, State> states;

    /// The current frame number (in both directions)
    sf::Vector2u currentFrame;

    /// The currently playing animation state (represented as a string)
    std::string playingState;

    /// Determines if the animation is playing
    bool isPlaying;

    /// Determines whether or not the animation should repeat
    bool repeat;

private:

    // used in implemenation
    double m_frameAccumulator;

    friend struct AnimationSystem;
};

#endif // ANAX_EXAMPLES_COMMON_COMPONENTS_ANIMATIONCOMPONENT_HPP
