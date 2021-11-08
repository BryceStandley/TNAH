#pragma once

#include <sstream>
#include "TNAH/Events/Event.h"
#include "TNAH/Core/KeyCodes.h"

namespace tnah {

	/**
	 * @class	KeyEvent
	 *
	 * @brief	A key event class that inherits from the base class event
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class KeyEvent : public Event
	{
	public:

		/**
		 * @fn	KeyCode KeyEvent::GetKeyCode() const
		 *
		 * @brief	Gets key code
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The key code.
		 */

		KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:

		/**
		 * @fn	tnah::KeyEvent::KeyEvent(const KeyCode keycode)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	keycode	The keycode.
		 */

		KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};

	/**
	 * @class	KeyPressedEvent
	 *
	 * @brief	A key pressed event class that inherits from KeyEvent class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class KeyPressedEvent : public KeyEvent
	{
	public:

		/**
		 * @fn	KeyPressedEvent::KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	keycode	   	The keycode.
		 * @param 	repeatCount	Number of repeats.
		 */

		KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		/**
		 * @fn	uint16_t KeyPressedEvent::GetRepeatCount() const
		 *
		 * @brief	Gets repeat count
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The repeat count.
		 */

		uint16_t GetRepeatCount() const { return m_RepeatCount; }

		/**
		 * @fn	std::string KeyPressedEvent::ToString() const override
		 *
		 * @brief	Convert the keycode and repeat count into a string format
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	A std::string that represents this object.
		 */

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:

		/** @brief	Number of repeats */
		uint16_t m_RepeatCount;
	};

	/**
	 * @class	KeyReleasedEvent
	 *
	 * @brief	A key released event that inherits from the KeyEvent class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class KeyReleasedEvent : public KeyEvent
	{
	public:

		/**
		 * @fn	KeyReleasedEvent::KeyReleasedEvent(const KeyCode keycode)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	keycode	The keycode.
		 */

		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		/**
		 * @fn	std::string KeyReleasedEvent::ToString() const override
		 *
		 * @brief	Convert the keyCode of the KeyReleasedEvent to a string format
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	A std::string that represents this object.
		 */

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	/**
	 * @class	KeyTypedEvent
	 *
	 * @brief	A key typed event that inherits from the KeyEvent class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class KeyTypedEvent : public KeyEvent
	{
	public:

		/**
		 * @fn	KeyTypedEvent::KeyTypedEvent(const KeyCode keycode)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	keycode	The keycode.
		 */

		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		/**
		 * @fn	std::string KeyTypedEvent::ToString() const override
		 *
		 * @brief	Convert this keycode into into a string representation
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	A std::string that represents this object.
		 */

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}