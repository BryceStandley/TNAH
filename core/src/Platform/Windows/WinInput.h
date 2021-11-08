#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Core/Input.h"

#include <GLFW/glfw3.h>

namespace tnah {

	/**
	 * @class	WinInput
	 *
	 * @brief	A Window Input class that inherits from the base Input class
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 */

	class WinInput : public Input
	{

	protected:

		/**
		 * @fn	virtual bool WinInput::IsKeyPressedImpl(int keycode) override;
		 *
		 * @brief	Query if 'keycode' is pressed implementation
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	keycode	The keycode.
		 *
		 * @returns	True if key pressed, false if not.
		 */

		virtual bool IsKeyPressedImpl(int keycode) override;

		/**
		 * @fn	virtual bool WinInput::IsMouseButtonPressedImpl(int button) override;
		 *
		 * @brief	Query if 'button' is mouse button pressed
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	button	The button.
		 *
		 * @returns	True if mouse button pressed, false if not.
		 */

		virtual bool IsMouseButtonPressedImpl(int button) override;

		/**
		 * @fn	virtual float WinInput::GetMouseXImpl() override;
		 *
		 * @brief	Gets mouse x coordinate implementation
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The mouse x coordinate implementation.
		 */

		virtual float GetMouseXImpl() override;

		/**
		 * @fn	virtual float WinInput::GetMouseYImpl() override;
		 *
		 * @brief	Gets mouse y coordinate implementation
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The mouse y coordinate implementation.
		 */

		virtual float GetMouseYImpl() override;

		/**
		 * @fn	virtual std::pair<float, float> WinInput::GetMousePosImpl() override;
		 *
		 * @brief	Gets mouse position implementation
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The mouse position implementation.
		 */

		virtual std::pair<float, float> GetMousePosImpl() override;
	};
}
