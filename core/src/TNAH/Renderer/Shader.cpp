#include "tnahpch.h"
#include "TNAH/Renderer/Shader.h"

#include <entt.hpp>

#include "TNAH/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace tnah {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		auto shader = CheckShaderExists(filepath);
		if(!shader)
		{
			switch (Renderer::GetAPI())
			{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  
				Ref<Shader> ref = Ref<OpenGLShader>::Create(filepath);
				Renderer::RegisterShader(ref);
				return ref;
			}
			TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		return shader;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		auto shader = CheckShaderExists(vertexSrc, fragmentSrc);
		if(!shader)
		{
			switch (Renderer::GetAPI())
			{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:
				Ref<Shader> ref = Ref<OpenGLShader>::Create(vertexSrc, fragmentSrc);
				Renderer::RegisterShader(ref);
				return ref;
			}

			TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		return shader;
	}

	Ref<Shader> Shader::CheckShaderExists(const std::string& filePath)
	{
		for(auto& shader : Renderer::GetLoadedShaders())
		{
			if(shader->m_FilePaths.first == filePath)
			{
				//The shader is already loaded and compiled, return shader
				return shader;
			}
		}
		return nullptr;
	}

	Ref<Shader> Shader::CheckShaderExists(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		for(auto& shader : Renderer::GetLoadedShaders())
		{
			if(shader->m_FilePaths.first == vertexSrc || shader->m_FilePaths.second == fragmentSrc)
			{
				//The shader is already loaded and compiled, return shader
				return shader;
			}
		}
		return nullptr;
	}


}
