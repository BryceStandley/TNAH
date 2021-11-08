#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Events/Event.h"

namespace tnah {

	/**
	 * @class	DebugEvent
	 *
	 * @brief	A debug event class that inherits from the base event class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class DebugEvent : public Event
	{
	public:

		/**
		 * @fn	std::pair<std::string, std::string> DebugEvent::GetDetails()
		 *
		 * @brief	Gets the name and description details and stores them as a pair
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The details.
		 */

		std::pair<std::string, std::string> GetDetails() { return { m_Name, m_Description }; }


		EVENT_CLASS_CATEGORY(EventCategoryDebugCore | EventCategoryDebugApp)
	protected:


		/** @brief	The name */
		std::string m_Name;

		/** @brief	The description */
		std::string m_Description;
	};
}
