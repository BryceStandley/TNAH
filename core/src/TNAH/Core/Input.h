#pragma once
#include "TNAH/Core/Core.h"

namespace tnah {

	/**
	 * @class	Input
	 *
	 * @brief	An Input 
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	class Input
	{
	public:

		/**
		 * @fn	inline static bool Input::IsKeyPressed(int keycode)
		 *
		 * @brief	Query if 'keycode' is key pressed
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	keycode	The keycode.
		 *
		 * @returns	True if key pressed, false if not.
		 */

		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		/**
		 * @fn	inline static bool Input::IsMouseButtonPressed(int button)
		 *
		 * @brief	Query if 'button' is mouse button pressed
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	button	The button.
		 *
		 * @returns	True if mouse button pressed, false if not.
		 */

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		/**
		 * @fn	inline static float Input::GetMouseX()
		 *
		 * @brief	Gets mouse x coordinate
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The mouse x coordinate.
		 */

		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }

		/**
		 * @fn	inline static float Input::GetMouseY()
		 *
		 * @brief	Gets mouse y coordinate
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The mouse y coordinate.
		 */

		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		/**
		 * @fn	inline static std::pair<float, float> Input::GetMousePos()
		 *
		 * @brief	Gets mouse position
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The mouse position.
		 */

		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }

	protected:

		/**
		 * @fn	virtual bool Input::IsKeyPressedImpl(int keycode) = 0;
		 *
		 * @brief	Query if 'keycode' is key pressed implementation
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	keycode	The keycode.
		 *
		 * @returns	True if key pressed implementation, false if not.
		 */

		virtual bool IsKeyPressedImpl(int keycode) = 0;

		/**
		 * @fn	virtual bool Input::IsMouseButtonPressedImpl(int button) = 0;
		 *
		 * @brief	Query if 'button' is mouse button pressed implementation
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	button	The button.
		 *
		 * @returns	True if mouse button pressed implementation, false if not.
		 */

		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		/**
		 * @fn	virtual float Input::GetMouseXImpl() = 0;
		 *
		 * @brief	Gets mouse x coordinate implementation
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The mouse x coordinate implementation.
		 */

		virtual float GetMouseXImpl() = 0;

		/**
		 * @fn	virtual float Input::GetMouseYImpl() = 0;
		 *
		 * @brief	Gets mouse y coordinate implementation
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The mouse y coordinate implementation.
		 */

		virtual float GetMouseYImpl() = 0;

		/**
		 * @fn	virtual std::pair<float, float> Input::GetMousePosImpl() = 0;
		 *
		 * @brief	Gets mouse position implementation
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The mouse position implementation.
		 */

		virtual std::pair<float, float> GetMousePosImpl() = 0;

	private:

		/** @brief	The instance */
		static Input* s_Instance;
	};




}
