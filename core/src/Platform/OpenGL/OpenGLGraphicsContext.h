#pragma once

#include "TNAH/Renderer/GraphicsContext.h"

/**
 * @struct	GLFWwindow
 *
 * @brief	Form for viewing the glfw.
 *
 * @author	Dylan Blereau
 * @date	7/09/2021
 */

struct GLFWwindow;

namespace tnah {

		/**
		 * @class	OpenGLGraphicsContext
		 *
		 * @brief	An OpenGlGraphicsContext class that inherbits from a base GraphicsContext.
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

	class OpenGLGraphicsContext : public GraphicsContext
	{
	public:

			/**
			 * @fn	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window);
			 *
			 * @brief	Constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param [in,out]	window	A pointer to the GLFWwindow.
			 */

		OpenGLGraphicsContext(GLFWwindow* window);

			/**
			 * @fn	void OpenGLGraphicsContext::Init() override;
			 *
			 * @brief	Initializes GLFW
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void Init() override;

			/**
			 * @fn	void OpenGLGraphicsContext::SwapBuffers() override;
			 *
			 * @brief	Swap buffers
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void SwapBuffers() override;
	private:

			/** @brief	The GLFW window */
		GLFWwindow* m_Window;
	};


}
