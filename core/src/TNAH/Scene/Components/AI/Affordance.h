/*****************************************************************//**
* @file   Affordance.h
* @brief  Affordances
* 
* @author chris
* @date   November 2021
*********************************************************************/
#pragma once
#include "Actions.h"
#include <unordered_map>
namespace tnah
{
    class Affordance
    {
    public:

        Affordance(std::string t = "");
        
        ~Affordance();
       
        /**
         *
         * @fn GetActionValue
         * @brief Gets the value of the givena action
         * 
         * @param action
         * @return float
         * @author chris
         */
        float GetActionValue(Actions action);
        /**
         *
         * @fn SetActionValues
         * @brief Sets the action to the given value
         * 
         * @param action
         * @param value
         * @author chris
         */
        void SetActionValues(Actions action, float value);
        /**
         *
         * @fn GetTag
         * 
         * @return 
         * @author chris
         */
        std::string GetTag() const {return tag;}
        /**
         *
         * @fn GetActionString
         * @brief Gets the action string
         * 
         * @param action
         * @return 
         * @author chris
         */
        static std::string GetActionString(Actions action);
        
        /**
         *
         * @fn GetActions
         *
         * @author chris
         */
        std::unordered_map<Actions, float> GetActions() {return objectsActions;};

        ///Editor value
        float editorValue = 0;

        ///Most recent
        std::string recent = "";
    private:

        ///The tag
        std::string tag;

        ///The objects actions
        std::unordered_map<Actions, float> objectsActions;
        inline static std::string s_SearchString = "Affordance";
        /** @brief	Type identifiers for the component */
        inline static ComponentTypes s_Types = {
            {ComponentVariations::Affordance},
            {{ComponentCategory::AI},{ComponentCategory::Emotion}}
        };
        friend class EditorUI;
    };
}
