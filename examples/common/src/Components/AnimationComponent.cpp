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

#include <Components/AnimationComponent.hpp>

#include <iostream>
#include <unordered_map>
#include <functional>
#include <sstream>

void to_lower(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

std::string to_lower(const std::string& str)
{
    std::string temp(str);
    to_lower(temp);
    return temp;
}

    template <typename T>
T to_value(const std::string& str)
{
    T temp;
    std::istringstream stream(str);
    stream >> temp;
    return temp;
}

enum class ErrorType
{
    None,
    Syntax
};

template <typename T>
static void checkForVariables(std::istream& stream, const std::string& fullVarName, T& obj, const std::unordered_map<std::string, std::function<void (T&, unsigned int value)>> vars, ErrorType* error)
{
    std::string buffer; // used temporarily

    // if we don't see a '=' sign,
    // then there is a syntax error.
    // if this is the case, we'll just return false
    if(fullVarName[fullVarName.size() - 1] != '=')
    {
        std::cerr << "Syntax error: ";
        std::cerr << "\"" << fullVarName << "\" is invalid\n";
        *error = ErrorType::Syntax;
        return;
    }

    std::string varName = fullVarName.substr(0, fullVarName.size() - 1);

    // convert the var name to lower case
    to_lower(varName);


    if(stream >> buffer)
    {
        to_lower(buffer);
        unsigned int value = to_value<unsigned int>(buffer);

        // check if variable exsists
        if(vars.find(varName) == vars.end())
        {
            std::cerr << "No such variable as: \"" << varName << "\" variable\n";
            *error = ErrorType::Syntax;
            return;
        }
        vars.at(varName)(obj, value);
    }
}

/*

*/
bool AnimationComponent::loadData(std::istream& stream)
{
    /*
       The file structure has the following format:

       width= <width>
       height= <height>

       <state-name>:
       startx
       starty<x> <y>
       framesx <x-count> 
       framesy <y-count>

       ...

NOTES:
---
1. If nothing is supplied for start, then it is assumed it is (0, 0)
2. If nothing is supplied for frameCount, then it is assumed (1, 0)
3. This is not case sensitive, but is whitespace (and name) sensitive
4. You cannot declare global varaible assingments for the animations after
you declare different states (i.e. do width/height assignment at the TOP of the file).
*/

    static const std::unordered_map<std::string, std::function<void (AnimationComponent& anim, unsigned int value)>> animation_variable_assign_map =
    {
        {
            "width",
            [](AnimationComponent& anim, unsigned int value)
            {
                anim.frameSize.x = value;
            }
        },
        {
            "height",
            [](AnimationComponent& anim, unsigned int value)
            {
                anim.frameSize.y = value;
            }
        }
    };

    static const std::unordered_map<std::string, std::function<void (State& state, unsigned int value)>> state_variable_assign_map =
    {
        {
            "fps",
            [](State& state, unsigned int value)
            {
                state.frameRate = value;
            }
        },
        {
            "startx",
            [](State& state, unsigned int value)
            {
                state.startPosition.x = value;
            }
        },
        {
            "starty",
            [](State& state, unsigned int value)
            {
                state.startPosition.y = value;
            }
        },
        {
            "framesx",
            [](State& state, unsigned int value)
            {
                state.frameAmount.x = value;
            }
        },
        {
            "framesy",
            [](State& state, unsigned int value)
            {
                state.frameAmount.x = value;
            }
        }
    };

    ErrorType error = ErrorType::None;
    State* state = nullptr; // a temporary state variable
    std::string stateName; // current statename
    std::string buffer; // temporary buffer

    while(stream >> buffer)
    {		
        if(buffer[buffer.size() - 1] == '=')
        {
            // for general variables of the animation, e.g. width/height
            if(state == nullptr)
            {
                checkForVariables(stream, buffer, *this, animation_variable_assign_map, &error);
            }
            // for the current state
            else
            {
                checkForVariables(stream, buffer, *state, state_variable_assign_map, &error);
            }

            if(error != ErrorType::None)
            {
                return false;
            }
        }
        // if we're requiring a new state name and we didn't see any variables
        // then we'll search for a state
        else if(buffer[buffer.size() - 1] == ':')
        {
            // otherwise if we did see a statename,
            // we'll extract the statename
            stateName = buffer.substr(0, buffer.size() - 1);
            
            // create/retrieve the state associated with the name
            state = &states[stateName];
        }
    }

    return true;
}
