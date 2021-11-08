#include "tnahpch.h"
#include "Affordance.h"

namespace tnah
{
    Affordance::Affordance(std::string t) : tag(t)
    {
        objectsActions[none] = 0;
        objectsActions[abuse] = 0;
        objectsActions[drink] = 0;
        objectsActions[greeting] = 0;
        objectsActions[kick] = 0;
        objectsActions[pickup] = 0;
        objectsActions[play] = 0;
        objectsActions[punch] = 0;
        objectsActions[sit] = 0;
        objectsActions[sleep] = 0;
    }

    Affordance::~Affordance()
    {
    }

    float Affordance::GetActionValue(Actions action)
    {
        float value;
        value = objectsActions[action];
        //TNAH_CORE_INFO("action value {0}", objectsActions[action]);
        return value;
    }

    void Affordance::SetActionValues(Actions action, float value)
    {
        if(action != none)
        {
            if(value > 1)
                value = 1;
            else if(value < 0)
                value = 0;
            
            objectsActions[action] = value;
        }
    }

    std::string Affordance::GetActionString(Actions action)
    {
        switch(action)
        {
        case abuse:
            return "Abuse";
        case drink:
            return "Drink";
        case greeting:
            return "Greeting";
        case kick:
            return "Kick";
        case pickup:
            return "Pickup";
        case play:
            return "Play";
        case punch:
            return "Punch";
        case sit:
            return "Sit";
        case sleep:
            return "Sleep";
        case none:
        default:
            return "None";
        }
    }
}

