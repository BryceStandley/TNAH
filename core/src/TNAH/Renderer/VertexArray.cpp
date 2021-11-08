#include "tnahpch.h"
#include "TNAH/Renderer/VertexArray.h"

#include "TNAH/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace tnah {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}