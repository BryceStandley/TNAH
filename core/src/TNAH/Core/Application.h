#pragma once

#include <queue>

#include "TNAH/Core/Core.h"

#include "TNAH/Core/Window.h"
#include "TNAH/Events/ApplicationEvent.h"
#include "TNAH/Layers/LayerStack.h"
#include "TNAH/Layers/UI.h"


#include "Timestep.h"

#include "TNAH/Layers/ImGuiLayer.h"
#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Renderer.h"

#include "TNAH/Scene/SceneCamera.h"

#include "TNAH/Physics/PhysicsTimestep.h"

/**
 * @fn	int main(int argc, char** argv);
 *
 * @brief	Main entry-point for this application
 *
 * @author	Bryce Standley
 * @date	7/09/2021
 *
 * @param 	argc	The number of command-line arguments provided.
 * @param 	argv	An array of command-line argument strings.
 *
 * @returns	Exit-code for the process - 0 for success, else an error code.
 */


int main(int argc, char** argv);


/**
 * @namespace tnah {}
 *
 * @brief Main TNAH namespace
 *
 */
namespace tnah
{
	class Scene;
#define BIND_EVENT_FN(x) std::bind(&tnah::Application::x, this, std::placeholders::_1)

	/**
	 * @class	Application
	 *
	 * @brief	A base Application class.
	 *
	 * @author	Bryce Standley
	 * @date	10/09/2021
	 */

	class Application
	{
	public:

		/**
		 * @fn	Application::Application(const std::string& name = "TNAH App");
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	name	(Optional) The name of the application.
		 */

		Application(const std::string& name = "TNAH App");

		/**
		 * @fn	virtual Application::~Application();
		 *
		 * @brief	Destructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 */

		virtual ~Application();

		/**
		 * @fn	virtual void Application::Run();
		 *
		 * @brief	Runs this object
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 */

		virtual void Run();

		/**
		 * @fn	virtual void Application::OnEvent(Event& e);
		 *
		 * @brief	Executes the 'event' action
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	e	an Event to process.
		 */

		virtual void OnEvent(Event& e);

		/**
		 * @fn	void Application::PushLayer(Layer* layer);
		 *
		 * @brief	Pushes a layer
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	layer	If non-null, the layer.
		 */

		void PushLayer(Layer* layer);

		/**
		 * @fn	void Application::PushOverlay(Layer* overlay);
		 *
		 * @brief	Pushes an overlay
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	overlay	If non-null, the overlay.
		 */

		void PushOverlay(Layer* overlay);

		/**
		 * @fn	void Application::Close();
		 *
		 * @brief	Closes this object
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 */

		void Close();

		inline static Application& Get() { return *s_Instance; }

		/**
		 * @fn	inline Window& Application::GetWindow()
		 *
		 * @brief	Gets the window
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The window.
		 */

		inline Window& GetWindow() { return *m_Window; }

		/**
		 * @fn	static std::pair<std::string, int> Application::OpenFileFromBrowser();
		 *
		 * @brief	Opens file from browser
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	A std::pair&lt;std::string,int&gt;
		 */

		static std::pair<std::string, int> OpenFileFromBrowser();

		/**
		 * @fn	static std::pair<std::string, int> Application::OpenAudioFromBrowser();
		 *
		 * @brief	Opens audio from browser
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	A std::pair&lt;std::string,int&gt;
		 */

		static std::pair<std::string, int> OpenAudioFromBrowser();

		/**
		 * @fn	static std::pair<std::string, int> Application::OpenMeshFromBrowser();
		 *
		 * @brief	Opens mesh from browser
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	A std::pair&lt;std::string,int&gt;
		 */

		static std::pair<std::string, int> OpenMeshFromBrowser();

		/**
		 * @fn	static std::pair<std::string, int> Application::SaveFileAs(const char* fileName);
		 *
		 * @brief	Saves a file
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	fileName	Filename of the file.
		 *
		 * @returns	A std::pair&lt;std::string,int&gt;
		 */

		static std::pair<std::string, int> SaveFileAs(const char* fileName);

		static void LogPush(LogText log);
		
		static std::deque<LogText> GetLogQueue();
		/**
		 * @fn	bool Application::CheckEditor() const
		 *
		 * @brief	Determines if the editor if active
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		bool CheckEditor() const { return m_IsEditor; }

		/**
		 * @fn	void Application::SetEditorMode(const bool& isEditor)
		 *
		 * @brief	Sets editor mode
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	isEditor	True if is editor, false if not.
		 */

		void SetEditorMode(const bool& isEditor) { m_IsEditor = isEditor; }
		bool& GetDebugModeStatus() { return m_DebugModeEnabled;  }
		void SetDebugStatusChange() { m_DebugModeToggled = true; }
	
	private:

		/**
		 * @fn	bool Application::OnWindowClose(WindowCloseEvent& e);
		 *
		 * @brief	Executes the 'window close' action
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	e	A WindowCloseEvent to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		bool OnWindowClose(WindowCloseEvent& e);

		/**
		 * @fn	bool Application::OnWindowResize(WindowResizeEvent& e);
		 *
		 * @brief	Executes the 'window resize' action
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	e	A WindowResizeEvent to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		bool OnWindowResize(WindowResizeEvent& e);

		/**
		 * @fn	bool Application::OnMonitorResolutionChange(MonitorResolutionChangeEvent& e);
		 *
		 * @brief	Executes the 'monitor resolution change' action
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	e	A MonitorResolutionChangeEvent to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		bool OnMonitorResolutionChange(MonitorResolutionChangeEvent& e);

		
		/**
		* @fn	void Application::CheckDebugModeStatus()
		*
		* @brief	Checks the status of the application and if in debug mode, set the logger to debuf
		*
		* @author	Bryce Standley
		* @date	6/09/2021
		*
		*/
		void CheckDebugModeStatus()
		{
			if(m_DebugModeEnabled && m_DebugModeToggled)
			{
				m_DebugModeToggled = false;
				TNAH_CORE_INFO("Debug Mode Enabled");
				Log::SetLoggerDebugMode();
			}
			else if(!m_DebugModeEnabled && m_DebugModeToggled)
			{
				m_DebugModeToggled = false;
				Log::SetLoggerCoreMode();
				TNAH_CORE_INFO("Debug Mode Disabled");
			}
			
		} 

	
	private:
        /** @brief	The window */		
		Scope<Window> m_Window;


		/** @brief	True if application is running */
		bool m_Running = true;


		/** @brief	True if minimized, false if not */
		bool m_Minimized = false;


		/** @brief	Stack of layers */
		LayerStack m_LayerStack = LayerStack();


		/** @brief	The delta time */
		float m_DeltaTime = 0.0f;


		/** @brief	The imgui layer */
		ImGuiLayer* m_ImGuiLayer;


		/** @brief	True if is editor, false if not */
		bool m_IsEditor = false;
		bool m_DebugModeEnabled = false;
		bool m_DebugModeToggled = false;

		static std::deque<LogText> logQueue;
		
		
		/** @brief	The pointer to the instance of the application */
		static Application* s_Instance;

		/**
		 * @fn	friend int ::main(int argc, char** argv);
		 *
		 * @brief	Main entry-point for this application
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	argc	The number of command-line arguments provided.
		 * @param 	argv	An array of command-line argument strings.
		 *
		 * @returns	Exit-code for the process - 0 for success, else an error code.
		 */

		friend int ::main(int argc, char** argv);


	};

	/**
	 * @fn	Application* CreateApplication();
	 *
	 * @brief	Creates the application
	 *
	 * @author	Bryce Standley
	 * @date	10/09/2021
	 *
	 * @returns	Null if it fails, else the new application.
	 */

	Application* CreateApplication();
}

