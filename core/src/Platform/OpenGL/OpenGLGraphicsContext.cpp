#include <tnahpch.h>
#include "OpenGLGraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace tnah {

	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* glfwWindow)
		: m_Window(glfwWindow)
	{
		TNAH_CORE_ASSERT(m_Window, "Window handle is null!");
	}

	void OpenGLGraphicsContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TNAH_CORE_ASSERT(status, "Failed to initialize GLAD!");


		TNAH_CORE_INFO("OpenGL Information:");
		TNAH_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		TNAH_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		TNAH_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}


}