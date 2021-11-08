#pragma once

#include <tnahpch.h>
#include "TNAH/Events/Event.h"

namespace tnah
{
	struct WindowProps
	{

		/** @brief	The title */
		std::string Title;

		/** @brief	The width */
		unsigned int Width;

		/** @brief	The height */
		unsigned int Height;

		/**
		 * @fn	WindowProps(const std::string& title = "TNAH-Engine", unsigned int width = 1280, unsigned int height = 720)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	title 	(Optional) The title.
		 * @param 	width 	(Optional) The width.
		 * @param 	height	(Optional) The height.
		 */

		WindowProps(const std::string& title = "TNAH-Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	/**
	 * @class	Window
	 *
	 * @brief	An abstract window class that provides the virtual function defintions required to create a window
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	class Window
	{
	public:

		/** @brief	The event callback function */
		using EventCallbackFn = std::function<void(Event&)>;

		/**
		 * @fn	virtual Window::~Window()
		 *
		 * @brief	Destructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		virtual ~Window() {}

		/**
		 * @fn	virtual void Window::OnUpdate() = 0;
		 *
		 * @brief	Executes the 'update' action
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		virtual void OnUpdate() = 0;

		/**
		 * @fn	virtual unsigned int Window::GetWidth() const = 0;
		 *
		 * @brief	Gets the width
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The width.
		 */

		virtual unsigned int GetWidth() const = 0;

		/**
		 * @fn	virtual unsigned int Window::GetHeight() const = 0;
		 *
		 * @brief	Gets the height
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The height.
		 */

		virtual unsigned int GetHeight() const = 0;

		/**
		 * @fn	virtual void Window::SetEventCallback(const EventCallbackFn& callback) = 0;
		 *
		 * @brief	sets the event callback to the callback given as a parameter
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	callback	The callback.
		 */

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		/**
		 * @fn	virtual void Window::SetVSync(bool enabled) = 0;
		 *
		 * @brief	Sets v synchronize
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	enabled	True to enable, false to disable.
		 */

		virtual void SetVSync(bool enabled) = 0;

		/**
		 * @fn	virtual bool Window::IsVSync() const = 0;
		 *
		 * @brief	Query if this object is v synchronize
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	True if v synchronize, false if not.
		 */

		virtual bool IsVSync() const = 0;

		/**
		 * @fn	virtual bool Window::IsFullscreen() const = 0;
		 *
		 * @brief	Query if this object is fullscreen
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	True if fullscreen, false if not.
		 */

		virtual bool IsFullscreen() const = 0;

		/**
		 * @fn	virtual void Window::ToggleFullScreen(const bool& enabled) = 0;
		 *
		 * @brief	Toggle full screen
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	enabled	True to enable, false to disable.
		 */

		virtual void ToggleFullScreen(const bool& enabled) = 0;

		/**
		 * @fn	virtual void Window::SetScreenResolution(const uint32_t& width, const uint32_t& height) = 0;
		 *
		 * @brief	Sets screen resolution
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	width 	The width.
		 * @param 	height	The height.
		 */

		virtual void SetScreenResolution(const uint32_t& width, const uint32_t& height) = 0;

		/**
		 * @fn	virtual void* Window::GetNativeWindow() const = 0;
		 *
		 * @brief	Gets native window
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	Null if it fails, else the native window.
		 */

		virtual void* GetNativeWindow() const = 0;

		/**
		 * @fn	virtual void Window::SetCursorDisabled(bool disable) = 0;
		 *
		 * @brief	Sets cursor disabled
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	disable	True to disable, false to enable.
		 */

		virtual void SetCursorDisabled(bool disable) = 0;

		/**
		 * @fn	static Scope<Window> Window::Create(const WindowProps& props = WindowProps());
		 *
		 * @brief	Creates a new Scope&lt;Window&gt;
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	props	(Optional) The properties.
		 *
		 * @returns	A Scope&lt;Window&gt;
		 */

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};


}
