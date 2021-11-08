#pragma once

#include "TNAH/Renderer/Texture.h"

#include <glad/glad.h>

namespace tnah {

	/**
	 * @class	OpenGLTexture2D
	 *
	 * @brief	An OpenGLTexture2D class that inherits from the Texture2D class 
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 */

	class OpenGLTexture2D : public Texture2D
	{
	public:

		/**
		 * @fn	OpenGLTexture2D::OpenGLTexture2D(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	format	  	Describes the image format to use.
		 * @param 	width	  	The width.
		 * @param 	height	  	The height.
		 * @param 	data	  	The data.
		 * @param 	properties	The properties.
		 */

		OpenGLTexture2D(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties);

		/**
		 * @fn	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	width 	The width.
		 * @param 	height	The height.
		 */

		OpenGLTexture2D(uint32_t width, uint32_t height);

		/**
		 * @fn	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, const std::string& textureName = "", bool loadFromMemory = false, void* assimpTexture = nullptr);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 		  	path		  	Full pathname of the file.
		 * @param 		  	textureName   	(Optional) Name of the texture.
		 * @param 		  	loadFromMemory	(Optional) True to load from memory.
		 * @param [in,out]	assimpTexture 	(Optional) If non-null, the assimp texture.
		 */

		OpenGLTexture2D(const std::string& path, const std::string& textureName = "", bool loadFromMemory = false, void* assimpTexture = nullptr);

		/**
		 * @fn	OpenGLTexture2D::~OpenGLTexture2D() override;
		 *
		 * @brief	Destructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		~OpenGLTexture2D() override;

		/**
		 * @fn	unsigned char* OpenGLTexture2D::LoadFromMemory(const std::string& path, void* assimpTexture = nullptr);
		 *
		 * @brief	Loads from memory
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 		  	path		 	Full pathname of the file.
		 * @param [in,out]	assimpTexture	(Optional) If non-null, the assimp texture.
		 *
		 * @returns	Null if it fails, else the data that was read from the memory.
		 */

		unsigned char* LoadFromMemory(const std::string& path, void* assimpTexture = nullptr);

		/**
		 * @fn	uint32_t OpenGLTexture2D::GetWidth() const override
		 *
		 * @brief	Gets the width
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The width.
		 */

		uint32_t GetWidth() const override { return m_Width;  }

		/**
		 * @fn	uint32_t OpenGLTexture2D::GetHeight() const override
		 *
		 * @brief	Gets the height
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The height.
		 */

		uint32_t GetHeight() const override { return m_Height; }

		/**
		 * @fn	uint32_t OpenGLTexture2D::GetRendererID() const override
		 *
		 * @brief	Gets renderer identifier
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The renderer identifier.
		 */

		uint32_t GetRendererID() const override { return m_RendererID; }

		/**
		 * @fn	void OpenGLTexture2D::SetData(void* data, uint32_t size) override;
		 *
		 * @brief	Sets the data
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param [in,out]	data	If non-null, the data.
		 * @param 		  	size	The size.
		 */

		void SetData(void* data, uint32_t size) override;

		/**
		 * @fn	void OpenGLTexture2D::Bind(uint32_t slot) const override;
		 *
		 * @brief	Binds the given slot
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	slot	The slot.
		 */

		void Bind(uint32_t slot) const override;

		/**
		 * @fn	void OpenGLTexture2D::Bind() const override;
		 *
		 * @brief	Binds this object
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void Bind() const override;

		/**
		 * @fn	ktxTexture* OpenGLTexture2D::GetKtxData() const override
		 *
		 * @brief	Gets ktx data
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	Null if it fails, else the ktx data.
		 */

		ktxTexture* GetKtxData() const override { return nullptr; }

		/**
		 * @fn	unsigned char* OpenGLTexture2D::GetImageData() const override
		 *
		 * @brief	Gets image data
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	Null if it fails, else the image data.
		 */

		unsigned char* GetImageData() const override { return nullptr; }

		/**
		 * @fn	void OpenGLTexture2D::Free() override
		 *
		 * @brief	Frees this object
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void Free() override {}

		/**
		 * @fn	void OpenGLTexture2D::Free(void* data) override
		 *
		 * @brief	Frees the given data
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param [in,out]	data	If non-null, the data.
		 */

		void Free(void* data) override {}
	};

	/**
	 * @class	OpenGLTexture3D
	 *
	 * @brief	An OpenGLTexture3D that inherits from the base glass Texture3D
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 */

	class OpenGLTexture3D : public Texture3D
	{
	public:

		/**
		 * @fn	OpenGLTexture3D::OpenGLTexture3D(const std::vector<std::string>& paths, const std::string& textureName = "");
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	paths	   	A vector of texture paths.
		 * @param 	textureName	(Optional) Name of the texture.
		 */

		OpenGLTexture3D(const std::vector<std::string>& paths, const std::string& textureName = "");

		/**
		 * @fn	OpenGLTexture3D::OpenGLTexture3D(const Texture3DProperties& properties, const std::string& textureName = "");
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	properties 	The properties.
		 * @param 	textureName	(Optional) Name of the texture.
		 */

		OpenGLTexture3D(const Texture3DProperties& properties, const std::string& textureName = "");

		/**
		 * @fn	OpenGLTexture3D::~OpenGLTexture3D() override;
		 *
		 * @brief	Destructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		~OpenGLTexture3D() override;

		/**
		 * @fn	uint32_t OpenGLTexture3D::GetWidth() const override
		 *
		 * @brief	Gets the width
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The width.
		 */

		uint32_t GetWidth() const override { return m_Width;  }

		/**
		 * @fn	uint32_t OpenGLTexture3D::GetHeight() const override
		 *
		 * @brief	Gets the height
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The height.
		 */

		uint32_t GetHeight() const override { return m_Height; }

		/**
		 * @fn	uint32_t OpenGLTexture3D::GetRendererID() const override
		 *
		 * @brief	Gets renderer identifier
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The renderer identifier.
		 */

		uint32_t GetRendererID() const override { return m_RendererID; }

		/**
		 * @fn	void OpenGLTexture3D::SetData(void* data, uint32_t size) override;
		 *
		 * @brief	Sets a data
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param [in,out]	data	If non-null, the data.
		 * @param 		  	size	The size.
		 */

		void SetData(void* data, uint32_t size) override;

		/**
		 * @fn	void OpenGLTexture3D::Bind(uint32_t slot) const override;
		 *
		 * @brief	Binds the given slot
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	slot	The slot.
		 */

		void Bind(uint32_t slot) const override;

		/**
		 * @fn	void OpenGLTexture3D::Bind() const override;
		 *
		 * @brief	Binds this object
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void Bind() const override;

		/**
		 * @fn	ktxTexture* OpenGLTexture3D::GetKtxData() const override
		 *
		 * @brief	Gets ktx data
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	nullptr.
		 */

		ktxTexture* GetKtxData() const override { return nullptr; }

		/**
		 * @fn	unsigned char* OpenGLTexture3D::GetImageData() const override
		 *
		 * @brief	Gets image data
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	nullptr.
		 */

		unsigned char* GetImageData() const override { return nullptr; }
	};

}
