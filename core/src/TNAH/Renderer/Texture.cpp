#include "tnahpch.h"
#include "TNAH/Renderer/Texture.h"
#include "TNAH/Renderer/Image.h"
#include "TNAH/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif
#define STBI_FAILURE_USERMSG
#include "stb_image.h"

namespace tnah {
	Ref<Texture2D> Texture2D::Create(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return Ref<OpenGLTexture2D>::Create(format, width, height, data, properties);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::LoadImageToMemory(const std::string& filePath, const bool& flipOnLoad, const bool& isCubemap)
	{
		if(filePath.find(".ktx") != std::string::npos)
		{
			return LoadKTXImage(filePath, isCubemap);
		}

		return LoadSTBiImage(filePath, flipOnLoad);
	}

	Ref<Texture2D> Texture2D::LoadKTXImage(const std::string& filePath, const bool& isCubemap)
	{
		auto texture = Ref<Image>::Create();
		texture->m_TextureResource = { filePath };
		texture->m_LoadFormat = ImageLoadFormat::KTX;

		ktxTexture* ktx;

		KTX_error_code result = ktxTexture_CreateFromNamedFile(filePath.c_str(),
			KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT,
			&ktx);
		if(result != KTX_SUCCESS)
		{
			TNAH_CORE_ERROR("KTX Error: {0} with file {1}", KtxErrorReason(result), filePath.c_str());
			TNAH_CORE_ASSERT(texture->m_ImageData, "Failed to load image at path: " + filePath);
		}
		texture->m_Width = ktx->baseWidth;
		texture->m_Height = ktx->baseHeight;
		texture->m_ImageData = ktx;

		if(isCubemap)
		{
			texture->m_CubemapInformation = FindCubemapInfo(texture);
		}
		
		return texture;
	}

	std::string Texture2D::KtxErrorReason(const int& ktxError)
	{
		switch (auto error = static_cast<ktx_error_code_e>(ktxError))
		{
			case KTX_SUCCESS:  return "Operation was successful.";
			case KTX_FILE_DATA_ERROR: return "The data in the file is inconsistent with the spec.";
			case KTX_FILE_ISPIPE: return "The file is a pipe or named pipe.";
			case KTX_FILE_OPEN_FAILED: return "The target file could not be opened.";
			case KTX_FILE_OVERFLOW: return "The operation would exceed the max file size.";
			case KTX_FILE_READ_ERROR: return "An error occurred while reading from the file.";
			case KTX_FILE_SEEK_ERROR: return " An error occurred while seeking in the file.";
			case KTX_FILE_UNEXPECTED_EOF: return " File does not have enough data to satisfy request.";
			case KTX_FILE_WRITE_ERROR: return "An error occurred while writing to the file.";
			case KTX_GL_ERROR: return "GL operations resulted in an error.";
			case KTX_INVALID_OPERATION: return "The operation is not allowed in the current state.";
			case KTX_INVALID_VALUE: return "A parameter value was not valid.";
			case KTX_NOT_FOUND: return "Requested key was not found.";
			case KTX_OUT_OF_MEMORY: return "Not enough memory to complete the operation.";
			case KTX_TRANSCODE_FAILED: return "Transcoding of block compressed texture failed.";
			case KTX_UNKNOWN_FILE_FORMAT: return "The file not a KTX file.";
			case KTX_UNSUPPORTED_TEXTURE_TYPE: return "The KTX file specifies an unsupported texture type.";
			case KTX_UNSUPPORTED_FEATURE: return "Feature not included in in-use library or not yet implemented.";
			case KTX_LIBRARY_NOT_LINKED: return "Library dependency (OpenGL or Vulkan) not linked into application.";
			default: return "Not a KTX error code.";
		}
	}

	Ref<Texture2D> Texture2D::LoadSTBiImage(const std::string& filePath, const bool& flipOnLoad)
	{
		auto texture = Ref<Image>::Create();
		texture->m_TextureResource = {filePath};

		int width, height, channels;

		if(flipOnLoad)
		{
			stbi_set_flip_vertically_on_load(true);
		}
		else
		{
			if(filePath.find(".png") != std::string::npos)
			{
				// .png was found in the file path, flip vertically on load
				stbi_set_flip_vertically_on_load(true);
			}
			else
			{
				stbi_set_flip_vertically_on_load(false);
			}
		}
		
		texture->m_ImageData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
		if(!texture->m_ImageData)
		{
			TNAH_CORE_ERROR("STBI Error: {0} with file {1}", stbi_failure_reason(), filePath.c_str());
			TNAH_CORE_ASSERT(texture->m_ImageData, "Failed to load image at path: " + filePath);
		}
		
		texture->m_Width = (uint32_t)width;
		texture->m_Height = (uint32_t)height;
		texture->m_Channels = (uint32_t)channels;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB;
			dataFormat = GL_RGB;
		}
		else
		{
			internalFormat = GL_RED;
			dataFormat = GL_RED;
		}

		texture->m_InternalFormat = (uint32_t)internalFormat;
		texture->m_DataFormat = (uint32_t)dataFormat;
		
		
		return texture;
	}

	CubemapInformation Texture2D::FindCubemapInfo(Ref<Texture2D> texture)
	{
		float aspect = (float)texture->m_Width / (float)texture->m_Height;
		CubemapInformation info;
		
		float h = 4.0f / 3.0f; // 1.3
		float v = 3.0f / 4.0f; // 0.75
		float c = 6.0f / 1.0f; // 6.0
		float r = 1.0f / 6.0f; // 0.16
		if(aspect > 1.0f && aspect < 1.5f)
		{
			info.Format = CubemapImageFormat::Horizontal;
		}
		else if (aspect > 0.5f && aspect < 1.0f)
		{
			info.Format = CubemapImageFormat::Vertical;
		}
		else if(aspect > 5.5f)
		{
			info.Format = CubemapImageFormat::Column;
		}
		else if(aspect < 0.5f)
		{
			info.Format = CubemapImageFormat::Row;
		}

		switch (info.Format)
		{
			case CubemapImageFormat::Column:
				{
					info.CubeSize = texture->m_Width / 6;
					break;
				}
			case CubemapImageFormat::Row:
				{
					info.CubeSize = texture->m_Height / 6;
					break;
				}
			case CubemapImageFormat::Vertical:
				{
					info.CubeSize = texture->m_Width / 4;
					break;
				}
			case CubemapImageFormat::Horizontal:
				{
					info.CubeSize = texture->m_Width / 3;
					break;
				}
			default: break;
		}
		return info;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		Ref<Texture2D> t = nullptr;
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  t =  Ref<OpenGLTexture2D>::Create(width, height);
		}

		if(t != nullptr)
		{
			Renderer::RegisterTexture(t);
			return t;
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path, const std::string& textureName, bool loadFromMemory, void* assimpTexture)
	{
		Ref<Texture2D> t = nullptr;
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  t = Ref<OpenGLTexture2D>::Create(path, textureName, loadFromMemory, assimpTexture);
		}
		if(t != nullptr)
		{
			Renderer::RegisterTexture(t);
			return t;
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}



	Ref<Texture3D> Texture3D::Create(const std::vector<std::string>& paths, const std::string& textureName)
	{
		Ref<Texture3D> t = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  t = Ref<OpenGLTexture3D>::Create(paths, textureName);
		}

		if(t != nullptr)
		{
			return t;
		}
		
		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture3D> Texture3D::Create(const Texture3DProperties& properties, const std::string& textureName)
	{
		Ref<Texture3D> t = nullptr;
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  t = Ref<OpenGLTexture3D>::Create(properties, textureName);
		}

		if(t != nullptr)
		{
			return t;
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
