#pragma once
#include "TNAH/Core/Window.h"
#include "TNAH/Events/ApplicationEvent.h"
#include "TNAH/Events/MouseEvent.h"
#include "TNAH/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLGraphicsContext.h"


#include <GLFW/glfw3.h>


namespace tnah {

	/**
	 * @class	WinWindow
	 *
	 * @brief	Form for viewing the window.
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 */

	class WinWindow : public Window
	{
	public:

		/**
		 * @fn	WinWindow::WinWindow(const WindowProps& props);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	props	The properties.
		 */

		WinWindow(const WindowProps& props);

		/**
		 * @fn	virtual WinWindow::~WinWindow();
		 *
		 * @brief	Destructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		virtual ~WinWindow();

		/**
		 * @fn	void WinWindow::OnUpdate() override;
		 *
		 * @brief	Executes the 'update' action
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void OnUpdate() override;

		/**
		 * @fn	inline unsigned int WinWindow::GetWidth() const override
		 *
		 * @brief	Gets the width of window
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The width.
		 */

		inline unsigned int GetWidth() const override { return m_Data.Width; }

		/**
		 * @fn	inline unsigned int WinWindow::GetHeight() const override
		 *
		 * @brief	Gets the height of window
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The height.
		 */

		inline unsigned int GetHeight() const override { return m_Data.Height; }

		/**
		 * @fn	inline void WinWindow::SetEventCallback(const EventCallbackFn& callback) override
		 *
		 * @brief	Sets the event callback
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	callback	The callback.
		 */
		
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		/**
		 * @fn	void WinWindow::SetVSync(bool enabled) override;
		 *
		 * @brief	Sets v synchronize
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	enabled	True to enable, false to disable.
		 */

		void SetVSync(bool enabled) override;

		/**
		 * @fn	bool WinWindow::IsVSync() const override;
		 *
		 * @brief	Query if this object is v synchronize
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	True if v synchronize, false if not.
		 */

		bool IsVSync() const override;

		/**
		 * @fn	inline void* WinWindow::GetNativeWindow() const override
		 *
		 * @brief	Gets native window
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	Null if it fails, else the native window.
		 */

		inline void* GetNativeWindow() const override { return m_Window; }

		/**
		 * @fn	inline virtual void WinWindow::SetCursorDisabled(bool disable) override
		 *
		 * @brief	Sets cursor status
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	disable	True to disable, false to enable.
		 */

		inline virtual void SetCursorDisabled(bool disable) override
		{
			if(disable)
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

	/**
	 * @fn	virtual void WinWindow::ToggleFullScreen(const bool& enabled) override;
	 *
	 * @brief	Toggle full screen
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 *
	 * @param 	enabled	True to enable, false to disable.
	 */

	virtual void ToggleFullScreen(const bool& enabled) override;

	/**
	 * @fn	inline bool WinWindow::IsFullscreen() const override
	 *
	 * @brief	Query if this object is fullscreen
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 *
	 * @returns	True if fullscreen, false if not.
	 */

	inline bool IsFullscreen() const override {return m_Data.Fullscreen;}

	/**
	 * @fn	virtual void WinWindow::SetScreenResolution(const uint32_t& width, const uint32_t& height) override;
	 *
	 * @brief	Sets screen resolution
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 *
	 * @param 	width 	The width.
	 * @param 	height	The height.
	 */

	virtual void SetScreenResolution(const uint32_t& width, const uint32_t& height) override;
	
	private:

		/**
		 * @fn	virtual void WinWindow::Init(const WindowProps& props);
		 *
		 * @brief	Initializes this object
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	props	The properties.
		 */

		virtual void Init(const WindowProps& props);

		/**
		 * @fn	virtual void WinWindow::Shutdown();
		 *
		 * @brief	Shuts down this object and frees any resources it is using
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		virtual void Shutdown();
	private:

		/** @brief	The window */
		GLFWwindow* m_Window;

		/** @brief	The context */
		GraphicsContext* m_Context;

		/**
		 * @struct	WindowData
		 *
		 * @brief	A struct containing Window data.
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		struct WindowData
		{

			/** @brief	The title */
			std::string Title;

			
			/** @brief	The window with and height */
			unsigned int Width, Height;

			/** @brief	True to synchronize */
			bool VSync;

			/** @brief	True to fullscreen */
			bool Fullscreen;

			/** @brief	The event callback */
			EventCallbackFn EventCallback;
		};

		/** @brief	The data */
		WindowData m_Data;
	};





}
