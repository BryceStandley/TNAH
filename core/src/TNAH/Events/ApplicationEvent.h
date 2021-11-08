#pragma once

#include <sstream>
#include "TNAH/Events/Event.h"

namespace tnah {

	/**
	 * @class	WindowResizeEvent
	 *
	 * @brief	A window resize event class that inherits from the base event class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class WindowResizeEvent : public Event
	{
	public:

		/**
		 * @fn	WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	width 	The width.
		 * @param 	height	The height.
		 */

		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		/**
		 * @fn	unsigned int WindowResizeEvent::GetWidth() const
		 *
		 * @brief	Gets the width
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The width.
		 */

		unsigned int GetWidth() const { return m_Width; }

		/**
		 * @fn	unsigned int WindowResizeEvent::GetHeight() const
		 *
		 * @brief	Gets the height
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The height.
		 */

		unsigned int GetHeight() const { return m_Height; }

		/**
		 * @fn	std::string WindowResizeEvent::ToString() const override
		 *
		 * @brief	Convert this object into a string representation
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	A std::string that represents this object.
		 */

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

		/** @brief	The width of the window */
		unsigned int m_Width;


		/** @brief	The height of the window */
		unsigned int m_Height;
	};

	/**
	 * @class	WindowCloseEvent
	 *
	 * @brief	A window close event class that inherits from the base event class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class WindowCloseEvent : public Event
	{
	public:

		/**
		 * @fn	WindowCloseEvent::WindowCloseEvent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @class	AppTickEvent
	 *
	 * @brief	An application tick event class that inherits from the base event class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class AppTickEvent : public Event
	{
	public:

		/**
		 * @fn	AppTickEvent::AppTickEvent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @class	AppUpdateEvent
	 *
	 * @brief	An application update event class that inherits from the base event class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class AppUpdateEvent : public Event
	{
	public:

		/**
		 * @fn	AppUpdateEvent::AppUpdateEvent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @class	AppRenderEvent
	 *
	 * @brief	An application render event class that inherits from the base event class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class AppRenderEvent : public Event
	{
	public:

		/**
		 * @fn	AppRenderEvent::AppRenderEvent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @class	MonitorResolutionChangeEvent
	 *
	 * @brief	A monitor resolution change event class that inherits from the base event class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class MonitorResolutionChangeEvent: public Event
	{
	public:

		/**
		 * @fn	MonitorResolutionChangeEvent::MonitorResolutionChangeEvent (unsigned int width, unsigned int height)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	width 	The width.
		 * @param 	height	The height.
		 */

		MonitorResolutionChangeEvent (unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		/**
		 * @fn	unsigned int MonitorResolutionChangeEvent::GetWidth() const
		 *
		 * @brief	Gets the width
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The width.
		 */

		unsigned int GetWidth() const { return m_Width; }

		/**
		 * @fn	unsigned int MonitorResolutionChangeEvent::GetHeight() const
		 *
		 * @brief	Gets the height
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The height.
		 */

		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MonitorResolutionChangeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MonitorResolutionChange)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:

		/** @brief	The width and height of the window resolution */
		unsigned int m_Width, m_Height;
	};
}