#pragma once
#include "TNAH/Scene/GameObject.h"



namespace tnah {

    /**
     * @class	EditorUI
     *
     * @brief	An editor user interface.
     *
     * @author	Bryce Standley
     * @date	7/09/2021
     */

    class EditorUI
    {
    public:

        /**
         * @fn	static void DrawComponentProperties(GameObject& object, const bool& addComponents);
         *
         * @brief	Draw component properties
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param [in,out]	object	The object.
         * @param addComponents
         */

        static void DrawComponentProperties(GameObject& object, const bool& addComponents);

        /**
         * @fn	static bool EditorUI::DrawFloatControl(const std::string& label, float& value, float min = 0.0f, float max = 0.0f, bool readOnly = false);
         *
         * @brief	Draw float control
         *
         * @author	Bryce Standley
         * @author	Dylan Blereau
         * @author	Christopher Logan
         * @date	7/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	value   	The value.
         * @param 		  	min			(Optional) The minimum.
         * @param 		  	max			(Optional) The maximum.
         * @param 		  	readOnly	(Optional) True to read only.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool DrawFloatControl(const std::string& label, float& value, float min = 0.0f, float max = 0.0f, bool readOnly = false);

        /**
         * @fn	static bool EditorUI::DrawVec4Control(const std::string& label, glm::vec4& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);
         *
         * @brief	Draw vector 4 control
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 		  	label	   	The label.
         * @param [in,out]	values	   	The values.
         * @param 		  	readOnly   	(Optional) True to read only.
         * @param 		  	resetValue 	(Optional) The reset value.
         * @param 		  	columnWidth	(Optional) Width of the column.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool DrawVec4Control(const std::string& label, glm::vec4& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);

        /**
         * @fn	static bool EditorUI::DrawVec3Control(const std::string& label, glm::vec3& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);
         *
         * @brief	Draw vector 3 control
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 		  	label	   	The label.
         * @param [in,out]	values	   	The values.
         * @param 		  	readOnly   	(Optional) True to read only.
         * @param 		  	resetValue 	(Optional) The reset value.
         * @param 		  	columnWidth	(Optional) Width of the column.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool DrawVec3Control(const std::string& label, glm::vec3& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);

        /**
         * @fn	static bool EditorUI::DrawVec2Control(const std::string& label, glm::vec2& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);
         *
         * @brief	Draw vector 2 control
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 		  	label	   	The label.
         * @param [in,out]	values	   	The values.
         * @param 		  	readOnly   	(Optional) True to read only.
         * @param 		  	resetValue 	(Optional) The reset value.
         * @param 		  	columnWidth	(Optional) Width of the column.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool DrawVec2Control(const std::string& label, glm::vec2& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);

        /**
         * @fn	static bool EditorUI::DrawTextControl(const char* label, std::string& text, bool error = false, bool readOnly = false);
         *
         * @brief	Draw text control
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 		  	label   	The label.
         * @param [in,out]	text		The text.
         * @param 		  	error   	(Optional) True to error.
         * @param 		  	readOnly	(Optional) True to read only.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool DrawTextControl(const char* label, std::string& text, bool error = false, bool readOnly = false);

        /**
         * @fn	static bool EditorUI::Draw4ColorControl(const std::string& label, glm::vec4& value, bool readOnly, const glm::vec4& resetValue, 0 parameter5, 0 parameter6, 0} parameter7);
         *
         * @brief	Draw 4 color control
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 		  	label	  	The label.
         * @param [in,out]	value	  	The value.
         * @param 		  	readOnly  	(Optional) True to read only.
         * @param 		  	resetValue	(Optional) The reset value.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Draw4ColorControl(const std::string& label, glm::vec4& value, bool readOnly = false,  const glm::vec4& resetValue = {0,0,0,0});

        /**
         * @fn	static bool EditorUI::DrawMaterialProperties(bool empty, Ref<Material> material = nullptr);
         *
         * @brief	Draw material properties
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	empty   	True to empty.
         * @param 	material	(Optional) The material.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool DrawMaterialProperties(bool empty, Ref<Material> material = nullptr);

        /**
         * @fn	static bool EditorUI::DrawRemoveComponentButton(const std::string& id);
         *
         * @brief	Draw remove component button
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	id	The identifier.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool DrawRemoveComponentButton(const std::string& id);

        /**
         * @fn	static bool EditorUI::DrawResetButton(const std::string& id);
         *
         * @brief	Draw reset button
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	id	The identifier.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool DrawResetButton(const std::string& id);

        /**
         * @fn	static bool EditorUI::DrawRedButton(const std::string& label);
         *
         * @brief	Draw red button
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	label	The label.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool DrawRedButton(const std::string& label);

    private:

        /**
         * @fn	static std::list<ComponentTypes> EditorUI::GetPossibleComponentTypes(std::vector<ComponentTypes> typesHeld);
         *
         * @brief	Gets the possible component types
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	typesHeld	The types held.
         *
         * @returns	ComponentVariations - A type of a given component as a enum
         * @note Not all ComponentTypes can be returned as some are internal types not intended for
         * being added at runtime.
         */

        static std::list<ComponentVariations> GetPossibleComponentTypes(std::vector<ComponentVariations> typesHeld);

        /**
         * @fn	static bool EditorUI::DrawAddComponent(GameObject& object, const std::string& searchTerm = "");
         *
         * @brief	Draw add component
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param [in,out]	object	  	The object.
         * @param 		  	searchTerm	(Optional) The search term.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool DrawAddComponent(GameObject& object, const std::string& searchTerm = "");

        /**
         * @fn	static ComponentTypes EditorUI::FindAndDrawComponentSearchTerm(std::list<ComponentTypes> typesToSearch, const std::string& searchTerm);
         *
         * @brief	Finds all the components that contain the search terms and draws the component list
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	typesToSearch	The types to search.
         * @param 	searchTerm   	The search term.
         *
         * @returns	The draw component list.
         */

        static ComponentVariations FindAndDrawComponentSearchTerm(std::list<ComponentVariations> typesToSearch, const std::string& searchTerm);

        /**
         * @fn	static ComponentTypes EditorUI::DrawComponentList(std::list<ComponentTypes> componentsToDisplay);
         *
         * @brief	Draw component list
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	componentsToDisplay	The components to display.
         *
         * @returns	The ComponentTypes.
         */

        static ComponentVariations DrawComponentList(std::list<ComponentVariations> componentsToDisplay);

        /**
         * @fn	static std::list<ComponentTypes> EditorUI::FindAllComponentsContaining(std::list<ComponentTypes> componentsToSearch, const std::string& term);
         *
         * @brief	Searches for all components containing the given
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	componentsToSearch	The components to search.
         * @param 	term			  	The term.
         *
         * @returns	The found components containing the term.
         */

        static std::list<ComponentVariations> FindAllComponentsContaining(std::list<ComponentVariations> componentsToSearch, const std::string& term);

     /**
     * @fn	static std::list<ComponentTypes> EditorUI::FindAllSubtypesFromBaseType(std::list<ComponentTypes> componentsToSearch, const ComponentCategory& category);
     *
     * @brief	Searches for all components containing the given
     *
     * @author	Bryce Standley
     * @date	7/09/2021
     *
     * @param 	componentsToSearch	The components to search.
     * @param 	category			  	The component category to find.
     *
     * @returns	The found components within the category.
     */

     static std::list<ComponentVariations> FindAllSubtypesFromBaseType(std::list<ComponentVariations> componentsToSearch, const ComponentCategory& category);

        /**
         * @fn	static std::string EditorUI::FindStringFromComponentType(ComponentTypes type);
         *
         * @brief	Finds the string that matches the given component type
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	type	The type.
         *
         * @returns	The found string from component type.
         */

        static std::string FindStringFromComponentType(ComponentVariations type);

        /**
         * @fn	static std::string EditorUI::FindComponentTypeCategory(ComponentTypes type);
         *
         * @brief	Searches for the component type category
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	type	The type.
         *
         * @returns	The found component type category.
         */

        static std::string FindComponentTypeCategory(ComponentVariations type);

        /**
         * @fn	static bool EditorUI::AddComponentFromType(GameObject& object, ComponentTypes type);
         *
         * @brief	Adds a component from type
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param [in,out]	object	The object.
         * @param 		  	type  	The type.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool AddComponentFromType(GameObject& object, ComponentVariations type);
        
    };



}
