#pragma once
#include <tnahpch.h>

namespace tnah {

	/**
	 * @enum	EventType
	 *
	 * @brief	Values that represent event types
	 */

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		DebugApp, DebugCore,
		MonitorResolutionChange
	};

	/**
	 * @enum	EventCategory
	 *
	 * @brief	Values that represent event categories
	 */

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
		EventCategoryDebugApp = BIT(5),
		EventCategoryDebugCore = BIT(6)
	};

/**
 * @def	EVENT_CLASS_TYPE(type)
 *
 * @brief	A macro that defines event class type
 *
 * @author	Dylan Blereau
 * @date	10/09/2021
 *
 * @param 	type	The type.
 */

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

/**
 * @def	EVENT_CLASS_CATEGORY(category)
 *
 * @brief	A macro that defines event class category
 *
 * @author	Dylan Blereau
 * @date	10/09/2021
 *
 * @param 	category	The category.
 */

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/**
	 * @class	Event
	 *
	 * @brief	An base class for all events, handles the type of events and dispatching them to the correct layers or processors for the given event
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class Event
	{
	public:

		/**
		 * @fn	virtual Event::~Event() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		virtual ~Event() = default;


		/** @brief	True if handled, false if not*/
		bool Handled = false;

		/**
		 * @fn	virtual EventType Event::GetEventType() const = 0;
		 *
		 * @brief	Pure virtual function used to get the event type
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The event type.
		 */

		virtual EventType GetEventType() const = 0;

		/**
		 * @fn	virtual const char* Event::GetName() const = 0;
		 *
		 * @brief	Pure virtual function used to get the name
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else the name.
		 */

		virtual const char* GetName() const = 0;

		/**
		 * @fn	virtual int Event::GetCategoryFlags() const = 0;
		 *
		 * @brief	Pure virtual function used to get category flags
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	The category flags.
		 */

		virtual int GetCategoryFlags() const = 0;

		/**
		 * @fn	virtual std::string Event::ToString() const
		 *
		 * @brief	Convert this object into a string representation
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	A std::string that represents this object.
		 */

		virtual std::string ToString() const { return GetName(); }

		/**
		 * @fn	bool Event::IsInCategory(EventCategory category)
		 *
		 * @brief	Query if the given event category is in category
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param 	category	The category.
		 *
		 * @returns	True if in category, false if not.
		 */

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	/**
	 * @class	EventDispatcher
	 *
	 * @brief	An event dispatcher class
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class EventDispatcher
	{
	public:

		/**
		 * @fn	EventDispatcher::EventDispatcher(Event& event)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param [in,out]	event	The event.
		 */

		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		/**
		 * @fn	template<typename T, typename F> bool EventDispatcher::Dispatch(const F& func)
		 *
		 * @brief	Dispatches the given function
		 *
		 * @tparam	T	Generic type parameter.
		 * @tparam	F	Will be deduced by the compiler.
		 * @param 	func	The function.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	/**
	 * @fn	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString();
	 *
	 * @brief	Stream insertion operator
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 *
	 * @param [in,out]	os	The output stream.
	 * @param 		  	e 	An Event to process.
	 *
	 * @returns	The event converted to string representation.
	 */

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}

