#pragma once

namespace tnah {
    /**
     * @brief enums that represent the three NPC types
     */
    enum class CharacterNames
    {
        None = 0, Rubbish = 1, StudentAi = 2, DogAi = 3
    };

    struct CharacterComponent
    {
        /**
         * @fn  CharacterComponent
         * 
         * @brief default constructor of the character component struct 
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         */
        CharacterComponent()
        {
        }

        /**
         * @fn  CharacterComponent
         * 
         * @brief  Constructor for the character component that takes in the character type name and sets the character accordingly
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         * @param characterType
         * @param character
         */
        CharacterComponent(CharacterNames characterType, Character* character)
        {
            SetCharacter(characterType, character);
        }

        /**
         * @fn  SetCharacter
         * 
         * @brief  Sets the character using the given characterType name
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         * @param characterType
         * @param character
         */
        void SetCharacter(CharacterNames characterType, Character* character)
        {
            if(character)
            {
                switch (characterType)
                {
                case CharacterNames::StudentAi:
                    aiCharacter = character;
                    break;
                case CharacterNames::DogAi:
                    aiCharacter = character;
                    break;
                case CharacterNames::Rubbish:
                    aiCharacter = character;
                    break;
                case CharacterNames::None:
                    aiCharacter = nullptr;
                    break;
                default:
                    break;
                }
                currentCharacter = characterType;
            }
        }

        /// A pointer to the an instance of character class
        Ref<Character> aiCharacter = nullptr;
        
        /// character name value of the current character
        CharacterNames currentCharacter = CharacterNames::None;
    };
}