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

#include <Systems/AnimationSystem.hpp>

#include <iostream>

void AnimationSystem::update(double deltaTime)
{
    auto entities = getEntities();
    for(auto& e : entities)
    {		
        auto& animation = e.getComponent<AnimationComponent>();
        auto& sprite = e.getComponent<SpriteComponent>().sprite;

        AnimationComponent::State* animationState = nullptr;
        if(!animation.playingState.empty())
        {
            animationState = &animation.states[animation.playingState];
        }

        if(animation.isPlaying && animationState)
        {
            animation.m_frameAccumulator += deltaTime * (animationState->frameRate == 0 ? getFps() : animationState->frameRate);
            animation.currentFrame.x = (int)animation.m_frameAccumulator;

            if(animation.currentFrame.x >= animationState->frameAmount.x)
            {
                // go to the next row (if necessary)
                if(animationState->frameAmount.y)
                {
                    if(animation.currentFrame.y >= animationState->frameAmount.y)
                    {
                        animation.currentFrame.y = 0;
                    }
                    else
                    {
                        ++animation.currentFrame.y;
                    }
                }

                // reset the animation
                animation.currentFrame.x = 0;
                animation.m_frameAccumulator = 0;

                animation.isPlaying = animation.repeat;
            }
        }

        if(animationState)
        {
            sf::IntRect rect(sf::Vector2i(animationState->startPosition.x + animation.frameSize.x * (int)animation.currentFrame.x, 
                                          animationState->startPosition.y + animation.frameSize.y * (int)animation.currentFrame.y), 
                             sf::Vector2i(animation.frameSize)); 

            sprite.setTextureRect(rect);
        }
    }
}
