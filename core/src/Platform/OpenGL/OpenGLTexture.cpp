#include "tnahpch.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "TNAH/Renderer/Renderer.h"

#pragma warning(push, 0)
#include "TNAH/Renderer/stb_image.h"
#include <Assimp/scene.h>
#pragma warning(pop)

namespace tnah {
	
	OpenGLTexture2D::OpenGLTexture2D(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties)
	{
		m_Width = width;
		m_Height = height;
		m_Properties = properties;
		m_DataFormat = GL_RGBA;
		m_InternalFormat = GL_RGBA8;
		
		TNAH_CORE_WARN("Generating a texture at runtime isn't implimented yet!");
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
	{
		m_Width = width;
		m_Height = height;
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, const std::string& textureName, bool loadFromMemory, void* assimpTexture)
	{
		m_TextureResource = path;
		m_TextureResource.CustomName = textureName;
		m_UniformName = textureName;
		int width, height, channels;
		unsigned char* data = nullptr;
		if(path.find(".png") != std::string::npos)
		{
			// .png was found in the file path, flip vertically on load
			stbi_set_flip_vertically_on_load(0);
		}
		else
		{
			stbi_set_flip_vertically_on_load(1);
		}

		if(loadFromMemory && assimpTexture != nullptr)
		{
			data = LoadFromMemory(path, assimpTexture);
		}
		else
		{
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
			if(!data)
			{
				TNAH_CORE_ERROR("STBI Error: {0} with file {1}", stbi_failure_reason(), path.c_str());
				TNAH_CORE_ASSERT(data, "Failed to load texture or image at path: " + path);
			}
		}
		
		if(!loadFromMemory)
		{
			m_Width = (uint32_t)width;
			m_Height = (uint32_t)height;
			m_Channels = (uint32_t)channels;

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

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			TNAH_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");
		}
		else
		{
			GLenum internalFormat = 0, dataFormat = 0;
			if (m_Channels == 4)
			{
				internalFormat = GL_RGBA;
				dataFormat = GL_RGBA;
			}
			else if (m_Channels == 3)
			{
				internalFormat = GL_RGB;
				dataFormat = GL_RGB;
			}
			else
			{
				internalFormat = GL_RED;
				dataFormat = GL_RED;
			}

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			TNAH_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");
		}

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
			glTexImage2D(GL_TEXTURE_2D, 0, (int)m_InternalFormat, m_Width, m_Height, 0, m_InternalFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(data);
			m_Loaded = true;
			m_Slot = m_RendererID;
		
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	unsigned char* OpenGLTexture2D::LoadFromMemory(const std::string& path, void* assimpTexture)
	{
		unsigned char* data = nullptr;
		auto const aiTex = static_cast<aiTexture*>(assimpTexture);
		int width, height, channels;
		if(aiTex->mHeight == 0)
		{
			data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(aiTex->pcData),aiTex->mWidth, &width, &height, &channels, 0);
			if(!data)
			{
				TNAH_CORE_ERROR("STBI Error: {0} with file {1}", stbi_failure_reason(), path.c_str());
				TNAH_CORE_ASSERT(data, "Failed to load texture or image at path: " + path);
				return nullptr;
			}
			else
			{
				m_Width = (uint32_t)width;
				m_Height = (uint32_t)height;
				m_Channels = (uint32_t)channels;
				return data;
			}
		}
		else
		{
			data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(aiTex->pcData),aiTex->mWidth * aiTex->mHeight, &width, &height, &channels, 0);
			if(!data)
			{
				TNAH_CORE_ERROR("STBI Error: {0} with file {1}", stbi_failure_reason(), path.c_str());
				TNAH_CORE_ASSERT(data, "Failed to load texture or image at path: " + path);
				return nullptr;
			}
			else
			{
				m_Width = (uint32_t)width;
				m_Height = (uint32_t)height;
				m_Channels = (uint32_t)channels;
				return data;
			}
		}
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		TNAH_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void OpenGLTexture2D::Bind() const
	{
		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}



	// Texture 3D / CubeMaps
	OpenGLTexture3D::OpenGLTexture3D(const std::vector<std::string>& paths, const std::string& textureName)
	{
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

		int width, height, channels;
		unsigned char* data;
		stbi_set_flip_vertically_on_load(false);
		for(uint32_t i = 0; paths.size(); i++)
		{
			data = stbi_load(paths[i].c_str(), &width	, &height, &channels, 0);
			if(data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				TNAH_CORE_ERROR("Failed to load texture for Texture3D with path: {0}", paths[i]);
				TNAH_CORE_ASSERT(false, "Texture failed to load");
			}
			
			
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	OpenGLTexture3D::OpenGLTexture3D(const Texture3DProperties& properties, const std::string& textureName)
	{
		m_TextureResource.CustomName = textureName;
		m_TextureResource = properties.IsKtx ? properties.Cubemap.RelativeDirectory : properties.Front.RelativeDirectory;
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

		Ref<Texture2D> dataRight, dataLeft, dataBack, dataFront, dataTop, dataBottom, dataCubemap;	

		if(!properties.IsKtx)
		{
			stbi_set_flip_vertically_on_load(false);
			dataRight = Texture2D::LoadImageToMemory(properties.Right.AbsoluteDirectory);
			dataLeft = Texture2D::LoadImageToMemory(properties.Left.AbsoluteDirectory);
			dataBack = Texture2D::LoadImageToMemory(properties.Back.AbsoluteDirectory);
			dataFront = Texture2D::LoadImageToMemory(properties.Front.AbsoluteDirectory);
			dataTop = Texture2D::LoadImageToMemory(properties.Top.AbsoluteDirectory);
			dataBottom = Texture2D::LoadImageToMemory(properties.Bottom.AbsoluteDirectory);
		}
		else
		{
			dataCubemap = Texture2D::LoadImageToMemory(properties.Cubemap.AbsoluteDirectory);
		}
		
		if(!properties.IsKtx && dataRight && dataLeft && dataBack && dataFront && dataTop && dataBottom)
		{
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, dataRight->m_Width, dataRight->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataRight->m_ImageData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, dataLeft->m_Width, dataLeft->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataLeft->m_ImageData);
			
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, dataTop->m_Width, dataTop->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataTop->m_ImageData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, dataBottom->m_Width, dataBottom->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataBottom->m_ImageData);
			
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, dataBack->m_Width, dataBack->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataBack->m_ImageData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, dataFront->m_Width, dataFront->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataFront->m_ImageData);
			
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			
			dataRight->Free();
			dataLeft->Free();
			dataTop->Free();
			dataBottom->Free();
			dataFront->Free();
			dataBack->Free();
		}
		else if(properties.IsKtx && dataCubemap)
		{
			/*
			auto size = dataCubemap->m_CubemapInformation.CubeSize;
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, dataRight->m_ImageData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, dataLeft->m_ImageData);
			
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, dataTop->m_ImageData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, dataBottom->m_ImageData);
			
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, dataFront->m_ImageData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, dataBack->m_ImageData);
			*/
			GLenum target, error;
			ktxTexture_GLUpload(dataCubemap->GetKtxData(), &m_RendererID, &target, &error);
			dataCubemap->Free(dataCubemap->GetKtxData());
			
			//glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		}
		else
		{
			TNAH_CORE_ASSERT(false, "One or more textures failed to load");
		}
		
		m_Loaded = true;
		//m_Slot = Renderer::GetAndIncrementTextureSlot();
	}

	OpenGLTexture3D::~OpenGLTexture3D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture3D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		TNAH_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture3D::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
	}

	void OpenGLTexture3D::Bind() const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
	}
}
