#pragma once

#include "TNAH/Events/Event.h"
#include "TNAH/Core/MouseCodes.h"

namespace tnah {

	/**
	 * @class	MouseMovedEvent
	 *
	 * @brief	A mouse moved event class that inherits from the base event class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class MouseMovedEvent : public Event
	{
	public:

		/**
		 * @fn	MouseMovedEvent::MouseMovedEvent(const float x, const float y)
		 *
		 * @brief	Constructor for the mouse moved event
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	x	The x coordinate of the mouse.
		 * @param 	y	The y coordinate of the mouse.
		 */

		MouseMovedEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {}

		/**
		 * @fn	float MouseMovedEvent::GetX() const
		 *
		 * @brief	Get x coordinate of the mouse
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The x coordinate.
		 */

		float GetX() const { return m_MouseX; }

		/**
		 * @fn	float MouseMovedEvent::GetY() const
		 *
		 * @brief	Get y coordinate of the mouse
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The y coordinate.
		 */

		float GetY() const { return m_MouseY; }

		/**
		 * @fn	std::string MouseMovedEvent::ToString() const override
		 *
		 * @brief	Convert the mouse x and y coordinates into a string representation
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	A std::string that represents this object.
		 */

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:


		/** @brief	The mouse x and y coordinates */
		float m_MouseX, m_MouseY;
	};

	/**
	 * @class	MouseScrolledEvent
	 *
	 * @brief	A mouse scrolled event that inherits from the Event class 
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class MouseScrolledEvent : public Event
	{
	public:

		/**
		 * @fn	MouseScrolledEvent::MouseScrolledEvent(const float xOffset, const float yOffset)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	xOffset	The offset on the x-axis.
		 * @param 	yOffset	The offset on the y-axis.
		 */

		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		/**
		 * @fn	float MouseScrolledEvent::GetXOffset() const
		 *
		 * @brief	Gets x coordinate offset
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The x coordinate offset.
		 */

		float GetXOffset() const { return m_XOffset; }

		/**
		 * @fn	float MouseScrolledEvent::GetYOffset() const
		 *
		 * @brief	Gets y coordinate offset
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The y coordinate offset.
		 */

		float GetYOffset() const { return m_YOffset; }

		/**
		 * @fn	std::string MouseScrolledEvent::ToString() const override
		 *
		 * @brief	Convert the x and y offset of the the event into a string
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	A std::string that represents this object.
		 */

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:

		/** @brief	The x and y offset */
		float m_XOffset, m_YOffset;
	};

	/**
	 * @class	MouseButtonEvent
	 *
	 * @brief	A mouse button event class that inherits from the base Event class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class MouseButtonEvent : public Event
	{
	public:

		/**
		 * @fn	MouseCode MouseButtonEvent::GetMouseButton() const
		 *
		 * @brief	Gets mouse button
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The mouse button.
		 */

		MouseCode GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
	protected:

		/**
		 * @fn	tnah::MouseButtonEvent::MouseButtonEvent(const MouseCode button)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	button	The button.
		 */

		MouseButtonEvent(const MouseCode button)
			: m_Button(button) {}


		/** @brief	The button */
		MouseCode m_Button;
	};

	/**
	 * @class	MouseButtonPressedEvent
	 *
	 * @brief	A mouse button pressed event class that inherits from the MouseButtonEvent class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:

		/**
		 * @fn	MouseButtonPressedEvent::MouseButtonPressedEvent(const MouseCode button)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	button	The button.
		 */

		MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		/**
		 * @fn	std::string MouseButtonPressedEvent::ToString() const override
		 *
		 * @brief	Converts the mouse button code into a string representation
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	A std::string that represents this object.
		 */

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/**
	 * @class	MouseButtonReleasedEvent
	 *
	 * @brief	A mouse button released event class that inherits from the MouseButtonEvent class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:

		/**
		 * @fn	MouseButtonReleasedEvent::MouseButtonReleasedEvent(const MouseCode button)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	button	The button.
		 */

		MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		/**
		 * @fn	std::string MouseButtonReleasedEvent::ToString() const override
		 *
		 * @brief	Converts the mouse button code into a string representation
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	A std::string that represents this object.
		 */

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
