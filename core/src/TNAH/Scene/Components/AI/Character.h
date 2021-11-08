#pragma once
#include "Actions.h"
#include "EmotionComponent.h"
#include "StateMachine.h"

namespace tnah
{

   /**
    * @class  Character
    *
    * @brief
    *
    * @author Christopher Logan
    * @date   2/11/2021
    */
    class Character : public RefCounted
    {
    public:
        
        /**
         * @fn  OnUpdate
         * 
         * @brief Updates the character according to deltaTime
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param deltaTime - the timestep of the update
         * @param transform - the transform component of the character
         * @return glm::vec3 - the target position of the character
         */

        virtual glm::vec3 OnUpdate(Timestep deltaTime,TransformComponent &transform) = 0;
        /**
         * @fn  ~Character
         * 
         * @brief Virtual Destructor 
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         */

        virtual ~Character() = default;
        /**
         * @fn  GetDeltaTime
         * 
         * @brief Gets the deltatime 
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @return float - the deltaTime
         */

        float GetDeltaTime() const {return mDt;}
        /**
         * @fn  SetDeltaTime
         * 
         * @brief  sets the deltatime using the provided parameter
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param t - the  deltatime value to be set
         */

        void SetDeltaTime(const float t) {mDt = t;}

        /**
         * @fn  SetDesiredAction
         * 
         * @brief Sets the desired action that the NPC would like to perform, using the provided Action parameter
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param a - an enum Action value
         */

        void SetDesiredAction(const Actions a) {mDesiredAction = a;}
        /**
         * @fn  GetDesiredAction
         * 
         * @brief  Gets the desired action of the NPC
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @return Action - the desired action
         */

        Actions GetDesiredAction() const {return mDesiredAction;}
        /**
         * @fn  SetDistance
         * 
         * @brief  Sets the affordance distance of the NPC 
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param d - the affordance distance
         */
        void SetDistance(const float d) {affordanceDistance = d;}
        /**
         * @fn  GetDistance
         * 
         * @brief Gets the affordance distance  
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @return float - the affordance distance
         */
        float GetDistance() const {return affordanceDistance;}
        /**
         * @fn  CheckAction
         * 
         * @brief Checks the action 
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param affordanceValue
         * @param distance
         * @param tag
         * @return 
         */
        virtual std::pair<bool, bool> CheckAction(float affordanceValue, float distance, std::string tag) = 0;
        /**
         * @fn  LogAction
         * 
         * @brief Logs the action of the character, which can be displayed via text on the screen.  
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param text - the output of the character
         * @param colour - the colour of the text
         */
        void LogAction(std::string text, glm::vec4 colour);

        
        ///CHARACTER NAME
        std::string name;

        /**
         * @fn  GetWander
         * 
         * @brief Gets the bool that determines whether or not the character is wandering
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @return bool - the wander flag
         */
        bool GetWander() {return wander;}

        /**
         * @fn  SetWander
         * 
         * @brief Grants the ability to set the characters wander flag to true or false using the boolean parameter
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param w
         */
        void SetWander(bool w) {wander = w;}

        /**
         * @fn  SetSpeed
         * 
         * @brief Sets the movement speed of the character 
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param s - the speed value that will be assigned to speed
         */
        void SetSpeed(float s) {speed = s;}

        /**
         * @fn  GetSpeed
         * 
         * @brief Gets the movement speed of the character 
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @return float - the character speed
         */
        float GetSpeed() {return speed;}

        /**
         * @fn  ApplyPlayerAction
         * 
         * @brief  Can be used to apply actions of the player to the NPC
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param givenAction - refers to the given player action, which will be applied to the NPC character
         */
        virtual void ApplyPlayerAction(PlayerActions givenAction) = 0;

        /**
         * @fn  CharacterString
         * 
         * @brief Gets the character information string that include Emotion and Action Information
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @return string - the Character information string
         */
        virtual std::string CharacterString() = 0;

        /**
         * @fn  GetActionString
         * 
         * @brief Gets the string containing action information  
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param action - refers to the action that we will convert to string 
         * @return string - the action information string
         */
        static std::string GetActionString(Actions action);

    protected:

     /**
     * @fn  BalanceRange
     *
     * @brief Used to balance the given value between the given min and max values
     *
     * @author Chris Logan
     * @date   2/11/2021
     *
     * @param min - the minimum value
     * @param max - the maximum value
     * @param balanceValue - the value that is balanced
     * @return float
     */
     static float BalanceRange(float min, float max, float balanceValue)
     {
          if (balanceValue < min)
           return min;
            
          if (balanceValue > max)
           return max;

          return 0;
     }


    
    private:

        /// deltaTime
        float mDt = 0.0f;

        /// the desired action
        Actions mDesiredAction = Actions::sit;

        /// the affordance distance of the npc
        float affordanceDistance = 0.0f;

        /// true to wander, false to not
        bool wander = false;

        /// movement speed 
        float speed = 1.0f;
    };
   
}
