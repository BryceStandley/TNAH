/*****************************************************************//**
 * \file   Actions.h
 * \brief  
 * 
 * \author chris
 * \date   November 2021
 *********************************************************************/
#pragma once

namespace tnah
{
           
    /** \enum Actions The actions the objects can afford */
    enum Actions
    {
        sit = 1, kick = 2, punch = 3, none = 0, greeting = 4, pickup = 5, abuse = 6, sleep = 7, drink = 9, play = 10
    };
    /** \enum PlayerActions the actions players can do */
    enum PlayerActions
    {
        pumpUp, calm, compliment, insult
    };
}
