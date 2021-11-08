#include "tnahpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace tnah {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}