#pragma once

#include "TNAH/Core/Core.h"

#ifdef TNAH_PLATFORM_WINDOWS

	/**
	 * @fn	extern tnah::Application* tnah::CreateApplication();
	 *
	 * @brief	Creates the application
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 *
	 * @returns	Null if it fails, else the new application.
	 */

	extern tnah::Application* tnah::CreateApplication();

	/**
	 * @fn	int main(int argc, char** argv)
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

	int main(int argc, char** argv)
	{
		tnah::Log::Init();
		
		auto app = tnah::CreateApplication();

		app->Run();
		
		delete app;
	}

#endif
