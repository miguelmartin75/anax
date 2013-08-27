#ifndef __SCORECOMPONENT_HPP__
#define __SCORECOMPONENT_HPP__

#include <anax/Component.hpp>

struct ScoreComponent : anax::Component<ScoreComponent>
{
    ScoreComponent(int Score = 0) : score(Score) {}
    int score; // The score
};

#endif // __SCORECOMPONENT_HPP__
