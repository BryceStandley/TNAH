#include "tnahpch.h"
#include "Character.h"

#include "TNAH/Core/Application.h"

namespace tnah{

    void Character::LogAction(std::string text, glm::vec4 colour)
    {
        Application::LogPush(LogText(name + ": " + text, colour));
    }

    std::string Character::GetActionString(Actions action)
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
