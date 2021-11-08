#pragma once

#include "TNAH/Renderer/Texture.h"

namespace tnah {

    /**
     * @class	UI
     *
     * @brief	UI elements based on ImGui. Predefined wrappers to make creating UI faster and more
     * consistent this class is designed to wrap as many ImGui functions and controls under the UI
     * name, simplifying functions but also making the API more flexible with what it can do and
     * what values it can take
     *
     * @author	Bryce Standley
     * @date	01/09/2021
     */

    class UI
    {
    public:

        /**
         * @enum	SeparatorStyle
         *
         * @brief	Values that represent separator styles
         */

        enum class SeparatorStyle
        {
            Line = 0, Space = 1
        };

        /**
         * @enum	LineFlag
         *
         * @brief	Values that represent line flags
         */

        enum class LineFlag
        {
            SameLine = 0, NextLine = 1
        };

        /**
         * @enum	FileBrowserMode
         *
         * @brief	Values that represent file browser modes
         */

        enum class FileBrowserMode
        {
            Open = 0, Save = 1
        };

        /**
         * @fn	static void UI::Entry(const char* format, ...);
         *
         * @brief	Entry function 
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	format	Describes the format to use.
         * @param 	...   	Variable arguments providing additional information.
         */

        static void Entry(const char* format, ...);

        /**
         * @fn	static void UI::Entry(const std::string& text);
         *
         * @brief	Entry function that takes in a string of text
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	text	The text.
         */

        static void Entry(const std::string& text);

        /**
         * @fn	static void UI::Entry(const char* text, bool wrapped = false);
         *
         * @brief	Entry function that takes in a const char pointer of text and a bool value to confirm if text should wrap or not
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	text   	The text.
         * @param 	wrapped	(Optional) True if wrapped.
         */

        static void Entry(const char* text, bool wrapped = false);

        /**
         * @fn	static void UI::Entry(const std::string& text, bool wrapped = false);
         *
         * @brief	Entry function that takes in a string of text and a bool value to confirm if text should wrap or not 
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	text   	The text.
         * @param 	wrapped	(Optional) True if wrapped.
         */

        static void Entry(const std::string& text, bool wrapped = false);

        /**
         * @fn	static bool UI::Entry(const char* label, std::string& value, bool readOnly = false, bool error = false);
         *
         * @brief	Entry function that 
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	readOnly	(Optional) True to read only.
         * @param 		  	error   	(Optional) True to error.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(const char* label, std::string& value, bool readOnly = false, bool error = false);

        /**
         * @fn	static bool UI::Entry(const std::string& label, std::string& value, bool readOnly = false, bool error = false);
         *
         * @brief	Entry function that takes in a label and value string, alongside bools for readOnly and error
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	readOnly	(Optional) True to read only.
         * @param 		  	error   	(Optional) True to error.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(const std::string& label, std::string& value, bool readOnly = false, bool error = false);

        /**
         * @fn	static bool UI::Entry(const char* label, float& value, bool readOnly = false, bool error = false);
         *
         * @brief	Entry function that takes in a char * label and float value string, alongside bools for readOnly and error
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	readOnly	(Optional) True to read only.
         * @param 		  	error   	(Optional) True to error.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(const char* label, float& value, bool readOnly = false, bool error = false);

        /**
         * @fn	static bool UI::Entry(std::string& label, float& value, bool readOnly = false, bool error = false);
         *
         * @brief	Entry function that takes in a string label and a float value, alongside bools for readOnly and error
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param [in,out]	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	readOnly	(Optional) True to read only.
         * @param 		  	error   	(Optional) True to error.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(std::string& label, float& value, bool readOnly = false, bool error = false);

        /**
         * @fn	static bool UI::Entry(const char* label, int& value, bool readOnly = false, bool error = false);
         *
         * @brief	Entry function that takes in a char* label and an int value, alongside bools for readOnly and error
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	readOnly	(Optional) True to read only.
         * @param 		  	error   	(Optional) True to error.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(const char* label, int& value, bool readOnly = false, bool error = false);

        /**
         * @fn	static bool UI::Entry(std::string& label, int& value, bool readOnly = false, bool error = false);
         *
         * @brief	Entry function that takes in a label string and int value, alongside bools for readOnly and error
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param [in,out]	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	readOnly	(Optional) True to read only.
         * @param 		  	error   	(Optional) True to error.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(std::string& label, int& value, bool readOnly = false, bool error = false);

        /**
         * @fn	static bool UI::Entry(const char* label, bool& value, bool readOnly = false);
         *
         * @brief	Entry function that takes in a char* label and a bool value, alongside a bool for read only
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	True to value.
         * @param 		  	readOnly	(Optional) True to read only.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(const char* label, bool& value, bool readOnly = false);

        /**
         * @fn	static bool UI::Entry(std::string& label, bool& value, bool readOnly = false);
         *
         * @brief	Entry function that takes in a label string, alongside bools for value and readOnly
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param [in,out]	label   	The label.
         * @param [in,out]	value   	True to value.
         * @param 		  	readOnly	(Optional) True to read only.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(std::string& label, bool& value, bool readOnly = false);

        /**
         * @fn	static bool UI::Entry(const char* label, glm::vec2& value, bool readOnly = false, float resetValue = 0.0f);
         *
         * @brief	Entry function that takes in a char* label and glm::vec2 value, alongside a bool for readOnly and a float representing the resetValue
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(const char* label, glm::vec2& value, bool readOnly = false, float resetValue = 0.0f);

        /**
         * @fn	static bool UI::Entry(std::string& label, glm::vec2& value, bool readOnly = false, float resetValue = 0.0f);
         *
         * @brief	Entry function that takes in a string label and a glm::vec2 value, alongside a bool for readOnly and a float representing the resetValue
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param [in,out]	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(std::string& label, glm::vec2& value, bool readOnly = false, float resetValue = 0.0f);

        /**
         * @fn	static bool UI::Entry(const char* label, glm::vec3& value, bool readOnly = false, float resetValue = 0.0f);
         *
         * @brief	Entry function that takes in a char* label and a glm::vec3 value, alongside a bool for readOnly and a float representing the resetValue
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(const char* label, glm::vec3& value, bool readOnly = false, float resetValue = 0.0f);

        /**
         * @fn	static bool UI::Entry(std::string& label, glm::vec3& value, bool readOnly = false, float resetValue = 0.0f);
         *
         * @brief	Entry function that takes in a string label and a glm::vec3 value, alongside a bool for readOnly and a float representing the resetValue
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param [in,out]	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(std::string& label, glm::vec3& value, bool readOnly = false, float resetValue = 0.0f);

        /**
         * @fn	static bool UI::Entry(const char* label, glm::vec4& value, bool readOnly = false, float resetValue = 0.0f);
         *
         * @brief	Entry function that takes in a char* string label and a glm::vec4 value, alongside a bool for readOnly and a float representing the resetValue
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(const char* label, glm::vec4& value, bool readOnly = false, float resetValue = 0.0f);

        /**
         * @fn	static bool UI::Entry(std::string& label, glm::vec4& value, bool readOnly = false, float resetValue = 0.0f);
         *
         * @brief	Entry function that takes in a string label and a glm::vec4 value, alongside a bool for readOnly and a float representing the resetValue
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param [in,out]	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Entry(std::string& label, glm::vec4& value, bool readOnly = false, float resetValue = 0.0f);

        //*********************** Slider Controls ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static bool UI::EntrySlider(const char* label, int& value, bool readOnly = false, int min = 0, int max = 0, int resetValue = 0);
         *
         * @brief	Entry slider
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntrySlider(const char* label, int& value, bool readOnly = false, int min = 0, int max = 0, int resetValue = 0);

        /**
         * @fn	static bool UI::EntrySlider(const std::string& label, int& value, bool readOnly = false, int min = 0, int max = 0, int resetValue = 0);
         *
         * @brief	Entry slider
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntrySlider(const std::string& label, int& value, bool readOnly = false, int min = 0, int max = 0, int resetValue = 0);

        /**
         * @fn	static bool UI::EntrySlider(const char* label, float& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry slider
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntrySlider(const char* label, float& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntrySlider(const std::string& label, float& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry slider
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntrySlider(const std::string& label, float& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntrySlider(const char* label, glm::vec2& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry slider
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntrySlider(const char* label, glm::vec2& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntrySlider(const std::string& label, glm::vec2& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry slider
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntrySlider(const std::string& label, glm::vec2& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntrySlider(const char* label, glm::vec3& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry slider
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntrySlider(const char* label, glm::vec3& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntrySlider(const std::string& label, glm::vec3& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry slider
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntrySlider(const std::string& label, glm::vec3& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntrySlider(const char* label, glm::vec4& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry slider
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntrySlider(const char* label, glm::vec4& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntrySlider(const std::string& label, glm::vec4& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry slider
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntrySlider(const std::string& label, glm::vec4& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        //*********************** Drag Controls ++++++++++++++++++++++++++++++++//


        /**
         * @fn	static bool UI::EntryDrag(const char* label, int& value, bool readOnly = false, int speed = 1, int min = 0, int max = 0, float resetValue = 0);
         *
         * @brief	Entry drag
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	speed	  	(Optional) The speed.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDrag(const char* label, int& value, bool readOnly = false, int speed = 1, int min = 0, int max = 0, int resetValue = 0);

        /**
         * @fn	static bool UI::EntryDrag(const std::string& label, int& value, bool readOnly = false, int speed = 1, int min = 0.0f, int max = 0.0f, int resetValue = 0);
         *
         * @brief	Entry drag
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	speed	  	(Optional) The speed.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

         static bool EntryDrag(const std::string& label, int& value, bool readOnly = false, int speed = 1, int min = 0, int max = 0, int resetValue = 0);

        /**
         * @fn	static bool UI::EntryDrag(const char* label, float& value, bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry drag
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	speed	  	(Optional) The speed.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */
        static bool EntryDrag(const char* label, float& value, bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntryDrag(const std::string& label, float& value, bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry drag
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	speed	  	(Optional) The speed.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDrag(const std::string& label, float& value, bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntryDrag(const char* label, glm::vec2& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry drag
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	speed	  	(Optional) The speed.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDrag(const char* label, glm::vec2& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntryDrag(const std::string& label, glm::vec2& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry drag
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	speed	  	(Optional) The speed.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDrag(const std::string& label, glm::vec2& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntryDrag(const char* label, glm::vec3& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry drag
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	speed	  	(Optional) The speed.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDrag(const char* label, glm::vec3& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntryDrag(const std::string& label, glm::vec3& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry drag
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	speed	  	(Optional) The speed.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDrag(const std::string& label, glm::vec3& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntryDrag(const char* label, glm::vec4& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry drag
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	speed	  	(Optional) The speed.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDrag(const char* label, glm::vec4& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        /**
         * @fn	static bool UI::EntryDrag(const std::string& label, glm::vec4& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
         *
         * @brief	Entry drag
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	speed	  	(Optional) The speed.
         * @param 		  	min		  	(Optional) The minimum.
         * @param 		  	max		  	(Optional) The maximum.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDrag(const std::string& label, glm::vec4& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        //*********************** Color Controls ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static bool UI::EntryColor(const char* label, glm::vec3& value, bool readOnly = false);
         *
         * @brief	Entry color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	readOnly	(Optional) True to read only.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryColor(const char* label, glm::vec3& value, bool readOnly = false);

        /**
         * @fn	static bool UI::EntryColor(const std::string& label, glm::vec3& value, bool readOnly = false);
         *
         * @brief	Entry color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	readOnly	(Optional) True to read only.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryColor(const std::string& label, glm::vec3& value, bool readOnly = false);

        /**
         * @fn	static bool UI::EntryColor(const char* label, glm::vec4& value, bool readOnly = false);
         *
         * @brief	Entry color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	readOnly	(Optional) True to read only.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryColor(const char* label, glm::vec4& value, bool readOnly = false);

        /**
         * @fn	static bool UI::EntryColor(const std::string& label, glm::vec4& value, bool readOnly = false);
         *
         * @brief	Entry color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	readOnly	(Optional) True to read only.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryColor(const std::string& label, glm::vec4& value, bool readOnly = false);

        //*********************** Checkbox Controls ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static bool UI::EntryCheckbox(const char* label, bool& value, bool readOnly = false);
         *
         * @brief	Entry checkbox
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	True to value.
         * @param 		  	readOnly	(Optional) True to read only.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryCheckbox(const char* label, bool& value, bool readOnly = false);

        /**
         * @fn	static bool UI::EntryCheckbox(const std::string& label, bool& value, bool readOnly = false);
         *
         * @brief	Entry checkbox
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	True to value.
         * @param 		  	readOnly	(Optional) True to read only.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryCheckbox(const std::string& label, bool& value, bool readOnly = false);

        
        //*********************** Organisation Controls ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static bool UI::EntryDropdown(const char* label, const char** options, uint32_t optionCount, uint32_t* selectedOption);
         *
         * @brief	Entry dropdown
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label		  	The label.
         * @param 		  	options		  	Options for controlling the operation.
         * @param 		  	optionCount   	Number of options.
         * @param [in,out]	selectedOption	If non-null, the selected option.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDropdown(const char* label, const char** options, uint32_t optionCount, uint32_t* selectedOption);

        /**
         * @fn	static bool UI::EntryDropdown(const std::string& label, const char** options, uint32_t optionCount, uint32_t* selectedOption);
         *
         * @brief	Entry dropdown
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label		  	The label.
         * @param 		  	options		  	Options for controlling the operation.
         * @param 		  	optionCount   	Number of options.
         * @param [in,out]	selectedOption	If non-null, the selected option.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDropdown(const std::string& label, const char** options, uint32_t optionCount, uint32_t* selectedOption);

        /**
         * @fn	static bool UI::EntryDropdown(const char* label, const std::vector<std::string>& options, uint32_t optionCount, uint32_t* selectedOption);
         *
         * @brief	Entry dropdown
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label		  	The label.
         * @param 		  	options		  	Options for controlling the operation.
         * @param 		  	optionCount   	Number of options.
         * @param [in,out]	selectedOption	If non-null, the selected option.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDropdown(const char* label, const std::vector<std::string>& options, uint32_t optionCount, uint32_t* selectedOption);

        /**
         * @fn	static bool UI::EntryDropdown(const std::string& label, const std::vector<std::string>& options, uint32_t optionCount, uint32_t* selectedOption);
         *
         * @brief	Entry dropdown
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label		  	The label.
         * @param 		  	options		  	Options for controlling the operation.
         * @param 		  	optionCount   	Number of options.
         * @param [in,out]	selectedOption	If non-null, the selected option.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryDropdown(const std::string& label, const std::vector<std::string>& options, uint32_t optionCount, uint32_t* selectedOption);

        /**
         * @fn	static bool UI::EntryCollapsable(const char* label);
         *
         * @brief	Entry collapsable
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label	The label.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryCollapsable(const char* label);

        /**
         * @fn	static bool UI::EntryCollapsable(const std::string& label);
         *
         * @brief	Entry collapsable
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label	The label.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryCollapsable(const std::string& label);

        /**
         * @fn	static bool UI::BeginTable(const char* label, int columnCount, ImGuiTableFlags flags = 0);
         *
         * @brief	Begins a table
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label	   	The label.
         * @param 	columnCount	Number of columns.
         * @param 	flags	   	(Optional) The flags.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool BeginTable(const char* label, int columnCount, ImGuiTableFlags flags = 0);

        /**
         * @fn	static bool UI::BeginTable(const std::string& label, int columnCount, ImGuiTableFlags flags = 0);
         *
         * @brief	Begins a table
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label	   	The label.
         * @param 	columnCount	Number of columns.
         * @param 	flags	   	(Optional) The flags.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool BeginTable(const std::string& label, int columnCount, ImGuiTableFlags flags = 0);

        /**
         * @fn	static void UI::EndTable();
         *
         * @brief	Ends a table
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void EndTable();

        //*********************** Images ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static void UI::Image(const Ref<Texture2D>& texture, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), const ImVec4& tint_color = ImVec4(1,1,1,1), const ImVec4& border_color = ImVec4(0,0,0,0));
         *
         * @brief	Images
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	texture			The texture.
         * @param 	size			The size.
         * @param 	uv0				(Optional) The uv 0.
         * @param 	uv1				(Optional) The first uv.
         * @param 	tint_color  	(Optional) The tint color.
         * @param 	border_color	(Optional) The border color.
         */

        static void Image(const Ref<Texture2D>& texture, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), const ImVec4& tint_color = ImVec4(1,1,1,1), const ImVec4& border_color = ImVec4(0,0,0,0));

        //*********************** Buttons ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static bool UI::Button(const std::string& label, const ImVec2& size = ImVec2(0,0));
         *
         * @brief	Button
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label	The label.
         * @param 	size 	(Optional) The size.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Button(const std::string& label, const ImVec2& size = ImVec2(0,0));

        /**
         * @fn	static bool UI::Button(const char* label, const ImVec2& size = ImVec2(0,0));
         *
         * @brief	Buttons
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label	The label.
         * @param 	size 	(Optional) The size.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Button(const char* label, const ImVec2& size = ImVec2(0,0));

        /**
         * @fn	static bool UI::ImageButton(const Ref<Texture2D>& texture, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), int frame_padding = -1, const ImVec4& bg_color = ImVec4(0,0,0,0), const ImVec4& tint_color = ImVec4(1,1,1,1));
         *
         * @brief	Image button
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	texture		 	The texture.
         * @param 	size		 	The size.
         * @param 	uv0			 	(Optional) The uv 0.
         * @param 	uv1			 	(Optional) The first uv.
         * @param 	frame_padding	(Optional) The frame padding.
         * @param 	bg_color	 	(Optional) The background color.
         * @param 	tint_color   	(Optional) The tint color.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool ImageButton(const Ref<Texture2D>& texture, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), int frame_padding = -1, const ImVec4& bg_color = ImVec4(0,0,0,0), const ImVec4& tint_color = ImVec4(1,1,1,1));

        //*********************** Misc Begins/Ends + ID/Style/Colors ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static void UI::BeginDockingWindow(const std::string& label, bool& open, ImGuiWindowFlags flags = 0);
         *
         * @brief	Begins docking window
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	The label.
         * @param [in,out]	open 	True to open.
         * @param 		  	flags	(Optional) The flags.
         */

        static void BeginDockingWindow(const std::string& label, bool& open, ImGuiWindowFlags flags = 0);

        /**
         * @fn	static void UI::EndDockingWindow();
         *
         * @brief	Ends docking window
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void EndDockingWindow();

        /**
         * @fn	static void UI::BeginWindow(const char* label, bool& open, ImGuiWindowFlags flags = 0);
         *
         * @brief	Begins a window
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	The label.
         * @param [in,out]	open 	True to open.
         * @param 		  	flags	(Optional) The flags.
         */

        static void BeginWindow(const char* label, bool& open, ImGuiWindowFlags flags = 0);

        /**
         * @fn	static void UI::BeginWindow(const std::string& label, bool& open, ImGuiWindowFlags flags = 0);
         *
         * @brief	Begins a window
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	label	The label.
         * @param [in,out]	open 	True to open.
         * @param 		  	flags	(Optional) The flags.
         */

        static void BeginWindow(const std::string& label, bool& open, ImGuiWindowFlags flags = 0);

        /**
         * @fn	static void UI::EndWindow();
         *
         * @brief	Ends a window
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void EndWindow();

        /**
         * @fn	static void UI::BeginSubWindow(const std::string& label, ImVec2 size, 0} parameter3, bool border, ImGuiWindowFlags flags);
         *
         * @brief	A sub window of another window. Visibility is controlled by the parent window.
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label	  	The label.
         * @param 	size	  	(Optional) The size.
         * @param 	border	  	(Optional) True to border.
         * @param 	flags	  	(Optional) The flags.
         */

        static void BeginSubWindow(const std::string& label, ImVec2 size = {0,0}, bool border = false, ImGuiWindowFlags flags = 0);

        /**
         * @fn	static void UI::BeginSubWindow(const char* label, ImVec2 size, 0} parameter3, bool border, ImGuiWindowFlags flags);
         *
         * @brief	A sub window of another window. Visibility is controlled by the parent window.
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label	  	The label.
         * @param 	size	  	(Optional) The size.
         * @param 	border	  	(Optional) True to border.
         * @param 	flags	  	(Optional) The flags.
         */

        static void BeginSubWindow(const char* label, ImVec2 size = {0,0}, bool border = false, ImGuiWindowFlags flags = 0);

        /**
         * @fn	static void UI::EndSubWindow();
         *
         * @brief	Ends sub window
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void EndSubWindow();

        /**
         * @fn	static bool UI::BeginMenuBar();
         *
         * @brief	Begins menu bar
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool BeginMenuBar();

        /**
         * @fn	static void UI::EndMenuBar();
         *
         * @brief	Ends menu bar
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void EndMenuBar();

        /**
         * @fn	static bool UI::BeginSubMenu(const std::string& label);
         *
         * @brief	Begins sub menu
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label	The label.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool BeginSubMenu(const std::string& label);

        /**
         * @fn	static bool UI::BeginSubMenu(const char* label);
         *
         * @brief	Begins sub menu
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label	The label.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool BeginSubMenu(const char* label);

        /**
         * @fn	static void UI::EndSubMenu();
         *
         * @brief	Ends sub menu
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void EndSubMenu();

        /**
         * @fn	static bool UI::EntryMenu(const char* label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);
         *
         * @brief	Entry menu
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label   	The label.
         * @param 	shortcut	(Optional) The shortcut.
         * @param 	selected	(Optional) True if selected.
         * @param 	enabled 	(Optional) True to enable, false to disable.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryMenu(const char* label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);

        /**
         * @fn	static bool UI::EntryMenu(const std::string& label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);
         *
         * @brief	Entry menu
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label   	The label.
         * @param 	shortcut	(Optional) The shortcut.
         * @param 	selected	(Optional) True if selected.
         * @param 	enabled 	(Optional) True to enable, false to disable.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryMenu(const std::string& label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);

        /**
         * @fn	static bool UI::EntryMenu(const std::string& label, const std::string& shortcut = "", bool selected = false, bool enabled = true);
         *
         * @brief	Entry menu
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	label   	The label.
         * @param 	shortcut	(Optional) The shortcut.
         * @param 	selected	(Optional) True if selected.
         * @param 	enabled 	(Optional) True to enable, false to disable.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool EntryMenu(const std::string& label, const std::string& shortcut = "", bool selected = false, bool enabled = true);

        /**
         * @fn	static void UI::EntrySeparator(SeparatorStyle style = SeparatorStyle::Line);
         *
         * @brief	Entry separator
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	style	(Optional) The style.
         */

        static void EntrySeparator(SeparatorStyle style = SeparatorStyle::Line);

        /**
         * @fn	static void UI::EntryLine(LineFlag flag = LineFlag::NextLine);
         *
         * @brief	Entry line
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	flag	(Optional) The flag.
         */

        static void EntryLine(LineFlag flag = LineFlag::NextLine);

        /**
         * @fn	static void UI::PushID(ImGuiStyleVar id);
         *
         * @brief	Pushes an identifier
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	id	The identifier.
         */

        static void PushID(ImGuiStyleVar id);

        /**
         * @fn	static void UI::PopID();
         *
         * @brief	Pops the identifier
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void PopID();

        /**
         * @fn	static void UI::PushStyle(ImGuiStyleVar idx, ImVec2 value);
         *
         * @brief	Pushes a style
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	idx  	Zero-based index of the.
         * @param 	value	The value.
         */

        static void PushStyle(ImGuiStyleVar idx, ImVec2 value);

        /**
         * @fn	static void UI::PushStyle(ImGuiStyleVar idx, float value);
         *
         * @brief	Pushes a style
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	idx  	Zero-based index of the.
         * @param 	value	The value.
         */

        static void PushStyle(ImGuiStyleVar idx, float value);

        /**
         * @fn	static void UI::PopStyle(int count = 0);
         *
         * @brief	Pops the style described by count
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	count	(Optional) Number of.
         */

        static void PopStyle(int count = 0);

        /**
         * @fn	static void UI::PushColor(ImGuiColorEditFlags idx, ImVec4 value);
         *
         * @brief	Pushes a color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	idx  	Zero-based index of the.
         * @param 	value	The value.
         */

        static void PushColor(ImGuiColorEditFlags idx, ImVec4 value);

        /**
         * @fn	static void UI::PopColor(int count = 0);
         *
         * @brief	Pops the color described by count
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	count	(Optional) Number of.
         */

        static void PopColor(int count = 0);

        //*********************** Window Set/Get Properties ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static bool UI::IsFocused();
         *
         * @brief	Query if this object is focused
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @returns	True if focused, false if not.
         */

        static bool IsFocused();

        /**
         * @fn	static void UI::SetWindowPosition(const ImVec2& position = ImVec2(0,0));
         *
         * @brief	Sets window position
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	position	(Optional) The position.
         */

        static void SetWindowPosition(const ImVec2& position = ImVec2(0,0));

        /**
         * @fn	static void UI::SetWindowPosition(const glm::vec2& position = glm::vec2(0,0));
         *
         * @brief	Sets window position
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	position	(Optional) The position.
         */

        static void SetWindowPosition(const glm::vec2& position = glm::vec2(0,0));

        /**
         * @fn	static void UI::SetWindowPosition(const float& x = 0, const float& y = 0);
         *
         * @brief	Sets window position
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	x	(Optional) The x coordinate.
         * @param 	y	(Optional) The y coordinate.
         */

        static void SetWindowPosition(const float& x = 0, const float& y = 0);

        /**
         * @fn	static glm::vec2 UI::GetWindowPosition();
         *
         * @brief	Gets window position
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @returns	The window position.
         */

        static glm::vec2 GetWindowPosition();

        /**
         * @fn	static glm::vec2 UI::GetWindowMinPosition();
         *
         * @brief	Gets the upper left position of the current window
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @returns	The window minimum position.
         */

        static glm::vec2 GetWindowMinPosition();

        /**
         * @fn	static glm::vec2 UI::GetWindowMaxPosition();
         *
         * @brief	Gets the bottom right position of the current window
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @returns	The window maximum position.
         */

        static glm::vec2 GetWindowMaxPosition();

        /**
         * @fn	static void UI::SetWindowSize(const ImVec2& size = ImVec2(0,0));
         *
         * @brief	Sets window size
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	size	(Optional) The size.
         */

        static void SetWindowSize(const ImVec2& size = ImVec2(0,0));

        /**
         * @fn	static void UI::SetWindowSize(const glm::vec2& size = glm::vec2(0,0));
         *
         * @brief	Sets window size
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	size	(Optional) The size.
         */

        static void SetWindowSize(const glm::vec2& size = glm::vec2(0,0));

        /**
         * @fn	static void UI::SetWindowSize(const float& x = 0, const float& y = 0);
         *
         * @brief	Sets window size
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	x	(Optional) The x coordinate.
         * @param 	y	(Optional) The y coordinate.
         */

        static void SetWindowSize(const float& x = 0, const float& y = 0);

        /**
         * @fn	static glm::vec2 UI::GetWindowSize();
         *
         * @brief	Gets window size
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @returns	The window size.
         */

        static glm::vec2 GetWindowSize();

        /**
         * @fn	static void UI::SetCursorPosition(const ImVec2& position = ImVec2(0,0));
         *
         * @brief	Sets cursor position
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	position	(Optional) The position.
         */

        static void SetCursorPosition(const ImVec2& position = ImVec2(0,0));

        /**
         * @fn	static void UI::SetCursorPosition(const glm::vec2& position = glm::vec2(0,0));
         *
         * @brief	Sets cursor position
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	position	(Optional) The position.
         */

        static void SetCursorPosition(const glm::vec2& position = glm::vec2(0,0));

        /**
         * @fn	static void UI::SetCursorPosition(const float& x = 0, const float& y = 0);
         *
         * @brief	Sets cursor position
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	x	(Optional) The x coordinate.
         * @param 	y	(Optional) The y coordinate.
         */

        static void SetCursorPosition(const float& x = 0, const float& y = 0);

        /**
         * @fn	static void UI::SetWindowAlpha(const float& alpha = 0);
         *
         * @brief	Sets window alpha
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	alpha	(Optional) The alpha.
         */

        static void SetWindowAlpha(const float& alpha = 0);

        /**
         * @fn	static void UI::SetWindowBackgroundColor(const ImVec4& bg_color = ImVec4(0,0,0,0));
         *
         * @brief	Sets window background color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	bg_color	(Optional) The background color.
         */

        static void SetWindowBackgroundColor(const ImVec4& bg_color = ImVec4(0,0,0,0));

        /**
         * @fn	static void UI::SetWindowBackgroundColor(const glm::vec4& bg_color = glm::vec4(0,0,0,0));
         *
         * @brief	Sets window background color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	bg_color	(Optional) The background color.
         */

        static void SetWindowBackgroundColor(const glm::vec4& bg_color = glm::vec4(0,0,0,0));

        /**
         * @fn	static void UI::SetWindowBackgroundColor(const glm::vec3& bg_color = glm::vec3(0,0,0), const float& alpha = 0);
         *
         * @brief	Sets window background color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	bg_color	(Optional) The background color.
         * @param 	alpha   	(Optional) The alpha.
         */

        static void SetWindowBackgroundColor(const glm::vec3& bg_color = glm::vec3(0,0,0), const float& alpha = 0);

        /**
         * @fn	static void UI::SetWindowRounding(const float& value);
         *
         * @brief	Sets window rounding
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	value	The value.
         */

        static void SetWindowRounding(const float& value);

        /**
         * @fn	static void UI::SetWindowPadding(const ImVec2& value);
         *
         * @brief	Sets window padding
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	value	The value.
         */

        static void SetWindowPadding(const ImVec2& value);

        /**
         * @fn	static void UI::SetWindowPadding(const glm::vec2& value);
         *
         * @brief	Sets window padding
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	value	The value.
         */

        static void SetWindowPadding(const glm::vec2& value);

        /**
         * @fn	static void UI::ClearWindowRounding();
         *
         * @brief	Clears the window rounding
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void ClearWindowRounding();

        /**
         * @fn	static void UI::ClearWindowPadding();
         *
         * @brief	Clears the window padding
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void ClearWindowPadding();

        /**
         * @fn	static glm::vec2 UI::GetContentSpaceAvailable();
         *
         * @brief	Gets content space available
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @returns	The content space available.
         */

        static glm::vec2 GetContentSpaceAvailable();

        //*********************** Button Set Properties ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static void UI::SetButtonColors(const ImVec4& idleColor, const ImVec4& hoverColor, const ImVec4& pressedColor);
         *
         * @brief	Sets idle, hover and pressed colors for a button.
         * @warning Clear with UI::ClearButtonColors()
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	idleColor   	The idle color.
         * @param 	hoverColor  	The hover color.
         * @param 	pressedColor	The pressed color.
         */

        static void SetButtonColors(const ImVec4& idleColor, const ImVec4& hoverColor, const ImVec4& pressedColor);

        /**
         * @fn	static void UI::SetButtonColors(const glm::vec4& idleColor, const glm::vec4& hoverColor, const glm::vec4& pressedColor);
         *
         * @brief	Sets button colors
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	idleColor   	The idle color.
         * @param 	hoverColor  	The hover color.
         * @param 	pressedColor	The pressed color.
         */

        static void SetButtonColors(const glm::vec4& idleColor, const glm::vec4& hoverColor, const glm::vec4& pressedColor);

        /**
         * @fn	static void UI::SetButtonStateColor(const ImVec4& color, ImGuiCol buttonState = ImGuiCol_Button);
         *
         * @brief	Sets a given state color for a button
         * @warning Clear with UI::ClearButtonColor()
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	color	   	The color.
         * @param 	buttonState	(Optional) State of the button.
         */

        static void SetButtonStateColor(const ImVec4& color, ImGuiCol buttonState = ImGuiCol_Button);

        /**
         * @fn	static void UI::SetButtonStateColor(const glm::vec4& color, ImGuiCol buttonState = ImGuiCol_Button);
         *
         * @brief	Sets button state color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	color	   	The color.
         * @param 	buttonState	(Optional) State of the button.
         */

        static void SetButtonStateColor(const glm::vec4& color, ImGuiCol buttonState = ImGuiCol_Button);

        /**
         * @fn	static void UI::SetButtonIdleColor(const ImVec4& color);
         *
         * @brief	Sets a single state color for a button
         * @warning Clear with UI::ClearButtonXXXColor() where XXX is the state set
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	color	The color.
         */

        static void SetButtonIdleColor(const ImVec4& color);

        /**
         * @fn	static void UI::SetButtonIdleColor(const glm::vec4& color);
         *
         * @brief	Sets button idle color
         * @warning Clear with UI::ClearButtonXXXColor() where XXX is the state set
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	color	The color.
         */

        static void SetButtonIdleColor(const glm::vec4& color);

        /**
         * @fn	static void UI::SetButtonHoverColor(const ImVec4& color);
         *
         * @brief	Sets button hover color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	color	The color.
         */

        static void SetButtonHoverColor(const ImVec4& color);

        /**
         * @fn	static void UI::SetButtonHoverColor(const glm::vec4& color);
         *
         * @brief	Sets button hover color
         * @warning Clear with UI::ClearButtonXXXColor() where XXX is the state set
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	color	The color.
         */

        static void SetButtonHoverColor(const glm::vec4& color);

        /**
         * @fn	static void UI::SetButtonPressedColor(const ImVec4& color);
         *
         * @brief	Sets button pressed color
         * @warning Clear with UI::ClearButtonXXXColor() where XXX is the state set
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	color	The color.
         */

        static void SetButtonPressedColor(const ImVec4& color);

        /**
         * @fn	static void UI::SetButtonPressedColor(const glm::vec4& color);
         *
         * @brief	Sets button pressed color
         * @warning Clear with UI::ClearButtonXXXColor() where XXX is the state set
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	color	The color.
         */

        static void SetButtonPressedColor(const glm::vec4& color);

        /**
         * @fn	static void UI::ClearButtonIdleColor();
         *
         * @brief	Clear a buttons idle color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void ClearButtonIdleColor();

        /**
         * @fn	static void UI::ClearButtonHoverColor();
         *
         * @brief	Clear a buttons hover color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void ClearButtonHoverColor();

        /**
         * @fn	static void UI::ClearButtonPressedColor();
         *
         * @brief	Clear a buttons pressed color
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void ClearButtonPressedColor();

        /**
         * @fn	static void UI::ClearButtonColors();
         *
         * @brief	Clear a button from all colors set
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void ClearButtonColors();

        /**
         * @fn	static void UI::ClearButtonColor();
         *
         * @brief	Clear a single buttons color style
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         */

        static void ClearButtonColor();

        //*********************** Fonts ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static void UI::SetFont(ImFont* font);
         *
         * @brief	Sets a font
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param [in,out]	font	If non-null, the font.
         */

        static void SetFont(ImFont* font);

        /**
         * @fn	static ImFont* UI::LoadFont(const char* fontPath, float size_pixels);
         *
         * @brief	Loads a font
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	fontPath   	Full pathname of the font file.
         * @param 	size_pixels	The size pixels.
         *
         * @returns	Null if it fails, else the font.
         */

        static ImFont* LoadFont(const char* fontPath, float size_pixels);

        /**
         * @fn	static void UI::LoadFonts(const char* rootFontPath, float size_pixels);
         *
         * @brief	Loads the fonts
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	rootFontPath	Full pathname of the root font file.
         * @param 	size_pixels 	The size pixels.
         */

        static void LoadFonts(const char* rootFontPath, float size_pixels);

        /**
         * @fn	static ImFont* UI::LoadFont(const std::string& fontPath, float size_pixels);
         *
         * @brief	Loads a font
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	fontPath   	Full pathname of the font file.
         * @param 	size_pixels	The size pixels.
         *
         * @returns	Null if it fails, else the font.
         */

        static ImFont* LoadFont(const std::string& fontPath, float size_pixels);

        /**
         * @fn	static void UI::LoadFonts(const std::string& rootFontPath, float size_pixels);
         *
         * @brief	Loads the fonts
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	rootFontPath	Full pathname of the root font file.
         * @param 	size_pixels 	The size pixels.
         */

        static void LoadFonts(const std::string& rootFontPath, float size_pixels);

        /**
         * @fn	static std::vector<ImFont*> UI::LoadFonts(const std::vector<std::string>& fontPaths, float size_pixels);
         *
         * @brief	Loads the fonts
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	fontPaths  	The font paths.
         * @param 	size_pixels	The size pixels.
         *
         * @returns	Null if it fails, else the fonts.
         */

        static std::vector<ImFont*> LoadFonts(const std::vector<std::string>& fontPaths, float size_pixels);

        /**
         * @fn	static std::list<ImFont*> UI::LoadFonts(const std::list<std::string>& fontPaths, float size_pixels);
         *
         * @brief	Loads the fonts
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	fontPaths  	The font paths.
         * @param 	size_pixels	The size pixels.
         *
         * @returns	Null if it fails, else the fonts.
         */

        static std::list<ImFont*> LoadFonts(const std::list<std::string>& fontPaths, float size_pixels);

        /**
         * @fn	static void UI::SetDefaultFont(const char* fontPath, float size_pixels);
         *
         * @brief	Sets default font
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	fontPath   	Full pathname of the font file.
         * @param 	size_pixels	The size pixels.
         */

        static void SetDefaultFont(const char* fontPath, float size_pixels);

        /**
         * @fn	static void UI::SetDefaultFont(ImFont* font);
         *
         * @brief	Sets default font
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param [in,out]	font	If non-null, the font.
         */

        static void SetDefaultFont(ImFont* font);

        
        //*********************** Misc Widgets ++++++++++++++++++++++++++++++++//

        /**
         * @fn	static std::string UI::OpenFileBrowser(const char* browserLabel, const FileBrowserMode& mode = FileBrowserMode::Open, const ImVec2& position = ImVec2(0,0), const char* validTypes = "*.*");
         *
         * @brief	Opens file browser
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 	browserLabel	The browser label.
         * @param 	mode			(Optional) The mode.
         * @param 	position		(Optional) The position.
         * @param 	validTypes  	(Optional) List of types of the valids.
         *
         * @returns	A std::string.
         */

        static std::string OpenFileBrowser(const char* browserLabel, const FileBrowserMode& mode = FileBrowserMode::Open, const ImVec2& position = ImVec2(0,0), const char*
                                           validTypes = "*.*");

        /**
         * @fn	static void UI::EntryToggleCheckbox(const char* id, bool& value);
         *
         * @brief	Entry toggle checkbox
         *
         * @author	Bryce Standley
         * @date	11/09/2021
         *
         * @param 		  	id   	The identifier.
         * @param [in,out]	value	True to value.
         */

        static void EntryToggleCheckbox(const char* id, bool& value);
        //TODO: Add functions for the spinners and loading widgets
    
    private:

        //*********************** Control Variables  ++++++++++++++++++++++++++++++++//
        
        /** @brief	The counter */
        inline static uint32_t s_Counter = 0;

        /**
         * @property	inline static char s_IDBuffer[16]
         *
         * @brief	Gets the identifier buffer[ 16]
         *
         * @returns	The s identifier buffer[ 16].
         */

        inline static char s_IDBuffer[16];
        

    };
}
