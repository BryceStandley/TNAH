#pragma once


#pragma warning(push, 0)

#include <string>

#include <ktx.h>
#pragma warning(pop)

#include "TNAH/Core/Core.h"
#include "TNAH/Core/FileStructures.h"
#include "TNAH/Core/Ref.h"

namespace tnah {

#pragma region Enums
	using uchar8_t = unsigned char;

	/**
	 * @enum	ImageLoadFormat
	 *
	 * @brief	Values that represent image load formats
	 */

	enum class ImageLoadFormat
	{
		KTX, STB
	};

	/**
	 * @enum	ImageFormat
	 *
	 * @brief	Values that represent image formats
	 */

	enum class ImageFormat
	{
		None = 0,
		RED32F,
		RGB,
		RGBA,
		RGBA16F,
		RGBA32F,
		RG16F,
		RG32F,

		SRGB,

		DEPTH32F,
		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8,
	};

	/**
	 * @enum	ImageUsage
	 *
	 * @brief	Values that represent image usage options
	 */

	enum class ImageUsage
	{
		None = 0,
		Texture,
		Attachment,
		Storage
	};

	/**
	 * @enum	TextureWrap
	 *
	 * @brief	Values that represent texture wrap options
	 */

	enum class TextureWrap
	{
		None = 0,
		Clamp,
		Repeat
	};

	/**
	 * @enum	TextureFilter
	 *
	 * @brief	Values that represent texture filter options
	 */

	enum class TextureFilter
	{
		None = 0,
		Linear,
		Nearest
	};

	/**
	 * @enum	TextureType
	 *
	 * @brief	Values that represent texture types
	 */

	enum class TextureType
	{
		None = 0,
		Texture2D,
		Texture3D
	};

	/**
	 * @struct	TextureProperties
	 *
	 * @brief	texture properties.
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	struct TextureProperties
	{

		/** @brief	The sampler wrap */
		TextureWrap SamplerWrap = TextureWrap::Repeat;

		/** @brief	A filter specifying the sampler */
		TextureFilter SamplerFilter = TextureFilter::Linear;

		/** @brief	True to generate mips */
		bool GenerateMips = true;

		/** @brief	True to sRGB */
		bool SRGB = false;

		/** @brief	True to storage */
		bool Storage = false;
	};

	/**
	 * @struct	ImageSpecification
	 *
	 * @brief	An image specification struct
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	struct ImageSpecification
	{

		/** @brief	Describes the format to use */
		ImageFormat Format = ImageFormat::RGBA;

		/** @brief	The usage */
		ImageUsage Usage = ImageUsage::Texture;

		/** @brief	The width */
		uint32_t Width = 1;

		/** @brief	The height */
		uint32_t Height = 1;

		/** @brief	The mips */
		uint32_t Mips = 1;

		/** @brief	The layers */
		uint32_t Layers = 1;

		/** @brief	True if deinterleaved */
		bool Deinterleaved = false;

		/** @brief	Name of the debug */
		std::string DebugName = "";
	};

	/**
	 * @class	Texture3DProperties
	 *
	 * @brief	A texture 3D properties class. Used to assist with skybox creation
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class Texture3DProperties
	{
	public:

		/**
		 * @fn	Texture3DProperties::Texture3DProperties() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		Texture3DProperties() = default;

		/**
		 * @fn	Texture3DProperties::Texture3DProperties(Resource front,Resource back, Resource left, Resource right, Resource top, Resource bottom)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	front 	The front.
		 * @param 	back  	The back.
		 * @param 	left  	The left.
		 * @param 	right 	The right.
		 * @param 	top   	The top.
		 * @param 	bottom	The bottom.
		 */

		Texture3DProperties(Resource front,Resource back, Resource left, Resource right, Resource top, Resource bottom)
			:Front(front), Back(back), Left(left), Right(right), Top(top), Bottom(bottom) {}

		/**
		 * @fn	Texture3DProperties::Texture3DProperties(Resource cubemap)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	cubemap	The cubemap.
		 */

		Texture3DProperties(Resource cubemap)
			:Cubemap(cubemap)
		{
			if(Cubemap.Type.Type == RType::Image && Cubemap.FileName.Extension.find("ktx") != std::string::npos)
			{
				IsKtx = true;
			}
		}
		

		/** @brief	The cubemap */
		Resource Cubemap;

		/** @brief	True if is ktx, false if not */
		bool IsKtx = false;

		/** @brief	The front face */
		Resource Front;

		/** @brief	The back face */
		Resource Back;

		/** @brief	The left face */
		Resource Left;

		/** @brief	The right face */
		Resource Right;

		/** @brief	The top face */
		Resource Top;

		/** @brief	The bottom face */
		Resource Bottom;
	};

	/**
	 * @enum	CubemapImageFormat
	 *
	 * @brief	Values that represent cubemap image formats
	 */

	enum class CubemapImageFormat
	{
		Column, Row, Vertical, Horizontal
	};

	/**
	 * @struct	CubemapInformation
	 *
	 * @brief	Information about the cubemap.
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	struct CubemapInformation
	{
		uint32_t CubeSize = 1;
		CubemapImageFormat Format = CubemapImageFormat::Column;
	};

	/**
	 * @class	Texture
	 *
	 * @brief	A texture class responsible for loading and applying textures
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

#pragma endregion

	class Texture : public RefCounted
	{
	public:

		/**
		 * @fn	virtual Texture::~Texture() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~Texture() = default;

		/**
		 * @fn	virtual uint32_t Texture::GetWidth() const
		 *
		 * @brief	Gets the width
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The width.
		 */

		virtual uint32_t GetWidth() const { return m_Width; }

		/**
		 * @fn	virtual uint32_t Texture::GetHeight() const
		 *
		 * @brief	Gets the height
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The height.
		 */

		virtual uint32_t GetHeight() const { return m_Height; }

		/**
		 * @fn	virtual bool Texture::IsLoaded() const
		 *
		 * @brief	Query if this object is loaded
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	True if loaded, false if not.
		 */

		virtual bool IsLoaded() const { return m_Loaded; }

		/**
		 * @fn	virtual std::string Texture::GetPath() const
		 *
		 * @brief	Gets the path
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The path.
		 */

		virtual std::string GetPath() const { return m_TextureResource.RelativeDirectory; }

		/**
		 * @fn	virtual std::string Texture::GetName() const
		 *
		 * @brief	Gets the name
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The name.
		 */

		virtual std::string GetName() const { return m_TextureResource.FileName.FileName; }

		/**
		 * @fn	virtual ImageLoadFormat Texture::GetLoadFormat() const
		 *
		 * @brief	Gets load format
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The load format.
		 */

		virtual ImageLoadFormat GetLoadFormat() const { return m_LoadFormat; }

		/**
		 * @fn	virtual ktxTexture* Texture::GetKtxData() const = 0;
		 *
		 * @brief	Returns a KTX Texture or nullptr if invalid
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	Null if it fails, else the ktx data.
		 */

		virtual ktxTexture* GetKtxData() const = 0;

		/**
		 * @fn	virtual uchar8_t* Texture::GetImageData() const = 0;
		 *
		 * @brief	Returns a uchar8_t of image data or nullptr if invalid
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	Null if it fails, else the image data.
		 */

		virtual uchar8_t* GetImageData() const = 0;

		std::string m_UniformName = "";

		Resource m_TextureResource;
		
		/** @brief	True if the data was loaded */
		bool m_Loaded = false;

		/** @brief	The height and width */
		uint32_t m_Width = 0, m_Height = 0;

		/** @brief	The channels, internal format, and data format */
		uint32_t m_Channels = 0, m_InternalFormat = 0, m_DataFormat = 0;

		/** @brief	Information describing the image */
		void* m_ImageData = nullptr;

		/** @brief	The load format */
		ImageLoadFormat m_LoadFormat = ImageLoadFormat::STB;

		/** @brief	The properties */
		TextureProperties m_Properties = TextureProperties();

		/** @brief	Information describing the cubemap */
		CubemapInformation m_CubemapInformation = CubemapInformation();
	};

	/**
	 * @class	Texture2D
	 *
	 * @brief	A texture 2d class that inherits from the Texture class. Handles 2D textures
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class Texture2D : public Texture
	{
	public:

		/**
		 * @fn	static Ref<Texture2D> Texture2D::Create(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties);
		 *
		 * @brief	Creates a new Texture2D
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	format	  	Describes the format to use.
		 * @param 	width	  	The width.
		 * @param 	height	  	The height.
		 * @param 	data	  	The data.
		 * @param 	properties	The properties.
		 *
		 * @returns	A Texture2D
		 */

		static Ref<Texture2D> Create(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties);

		/**
		 * @fn	static Ref<Texture2D> LoadImageToMemory(const std::string& filePath, const bool& flipOnLoad = false, const bool& isCubemap = false);
		 *
		 * @brief	Loads a image to memory
		 * @warning Image must be cleared by the user with tnah::Texture2D::Free()
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	filePath  	absolute or relative file path to image.
		 * @param 	flipOnLoad	(Optional) Flips the image on load (STB ONLY)
		 * @param 	isCubemap 	(Optional) Tells the loader the provided image is a cubemap (KTX ONLY}
		 *
		 * @returns	The image to memory.
		 */

		static Ref<Texture2D> LoadImageToMemory(const std::string& filePath, const bool& flipOnLoad = false, const bool& isCubemap = false);

		/**
		 * @fn	static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		 *
		 * @brief	Creates a new Texture2D
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	width 	The width.
		 * @param 	height	The height.
		 *
		 * @returns	A Texture2D
		 */

		static Ref<Texture2D> Create(uint32_t width, uint32_t height);

		/**
		 * @fn	static Ref<Texture2D> Create(const std::string& path, const std::string& textureName = "", bool loadFromMemory = false, void* assimpTexture = nullptr);
		 *
		 * @brief	Creates a new Texture2D
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 		  	path		  	Full pathname of the file.
		 * @param 		  	textureName   	(Optional) Name of the texture.
		 * @param 		  	loadFromMemory	(Optional) True to load from memory.
		 * @param [in,out]	assimpTexture 	(Optional) If non-null, the assimp texture.
		 *
		 * @returns	A Texture2D
		 */

		static Ref<Texture2D> Create(const std::string& path, const std::string& textureName = "", bool loadFromMemory = false, void* assimpTexture = nullptr);

		/**
		 * @fn	virtual void Free() = 0;
		 *
		 * @brief	Frees this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Free() = 0;

		/**
		 * @fn	virtual void Free(void* data) = 0;
		 *
		 * @brief	Frees the given data
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	data	If non-null, the data.
		 */

		virtual void Free(void* data) = 0;

		/**
		 * @fn	virtual uint32_t GetRendererID() const
		 *
		 * @brief	Gets renderer identifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The renderer identifier.
		 */

		virtual uint32_t GetRendererID() const { return m_RendererID; }

		/**
		 * @fn	virtual uint32_t GetTextureSlot() const
		 *
		 * @brief	Gets texture slot
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The texture slot.
		 */

		virtual uint32_t GetTextureSlot() const { return m_Slot; }

		/**
		 * @fn	virtual void SetData(void* data, uint32_t size) = 0;
		 *
		 * @brief	Sets data
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	data	If non-null, the data.
		 * @param 		  	size	The size.
		 */

		virtual void SetData(void* data, uint32_t size) = 0;

		/**
		 * @fn	virtual void Bind(uint32_t slot) const = 0;
		 *
		 * @brief	Binds the given slot
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	slot	The slot.
		 */

		virtual void Bind(uint32_t slot) const = 0;

		/**
		 * @fn	virtual void Bind() const = 0;
		 *
		 * @brief	Binds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Bind() const = 0;

		/** @brief	Identifier for the renderer */
		uint32_t m_RendererID = 0;

		/** @brief	The slot */
		uint32_t m_Slot = 0;
	private:

		/**
		 * @fn	static Ref<Texture2D> LoadKTXImage(const std::string& filePath, const bool& isKtx2 = false);
		 *
		 * @brief	Loads ktx image
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	filePath	Full pathname of the file.
		 * @param 	isKtx2  	(Optional) True if is ktx 2, false if not.
		 *
		 * @returns	The ktx image.
		 */

		static Ref<Texture2D> LoadKTXImage(const std::string& filePath, const bool& isKtx2 = false);

		/**
		 * @fn	static std::string KtxErrorReason(const int& ktxError);
		 *
		 * @brief	Ktx error reason
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	ktxError	The ktx error.
		 *
		 * @returns	A std::string.
		 */

		static std::string KtxErrorReason(const int& ktxError);

		/**
		 * @fn	static Ref<Texture2D> LoadSTBiImage(const std::string& filePath, const bool& flipOnLoad = false);
		 *
		 * @brief	Loads stbi image
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	filePath  	Full pathname of the file.
		 * @param 	flipOnLoad	(Optional) True to flip on load.
		 *
		 * @returns	The st bi image.
		 */

		static Ref<Texture2D> LoadSTBiImage(const std::string& filePath, const bool& flipOnLoad = false);

		/**
		 * @fn	static CubemapInformation FindCubemapInfo(Ref<Texture2D> texture);
		 *
		 * @brief	Searches for the first cubemap information
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	texture	The texture.
		 *
		 * @returns	The found cubemap information.
		 */

		static CubemapInformation FindCubemapInfo(Ref<Texture2D> texture);
	};

	/**
	 * @class	Texture3D
	 *
	 * @brief	A texture 3d class that inherits from the Texture class. Used for 3D Textures like a Skybox
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class Texture3D : public Texture
	{
	public:

		/**
		 * @fn	static Ref<Texture3D> Texture3D::Create(const std::vector<std::string>& paths, const std::string& textureName = "");
		 *
		 * @brief	Creates a new Texture3D
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	paths	   	The paths.
		 * @param 	textureName	(Optional) Name of the texture.
		 *
		 * @returns	A Texture3D
		 */

		static Ref<Texture3D> Create(const std::vector<std::string>& paths, const std::string& textureName = "");

		/**
		 * @fn	static Ref<Texture3D> Texture3D::Create(const Texture3DProperties& properties, const std::string& textureName = "Cubemap");
		 *
		 * @brief	Creates a new Texture3D
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	properties 	The properties.
		 * @param 	textureName	(Optional) Name of the texture.
		 *
		 * @returns	A Texture3D
		 */

		static Ref<Texture3D> Create(const Texture3DProperties& properties, const std::string& textureName = "Cubemap");

		/**
		 * @fn	virtual uint32_t Texture3D::GetRendererID() const
		 *
		 * @brief	Gets renderer identifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The renderer identifier.
		 */

		virtual uint32_t GetRendererID() const { return m_RendererID; }

		/**
		 * @fn	virtual uint32_t Texture3D::GetTextureSlot() const
		 *
		 * @brief	Gets texture slot
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The texture slot.
		 */

		virtual uint32_t GetTextureSlot() const { return m_Slot; }

		/**
		 * @fn	virtual void Texture3D::SetData(void* data, uint32_t size) = 0;
		 *
		 * @brief	Sets data
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	data	If non-null, the data.
		 * @param 		  	size	The size.
		 */

		virtual void SetData(void* data, uint32_t size) = 0;

		/**
		 * @fn	virtual void Texture3D::Bind(uint32_t slot) const = 0;
		 *
		 * @brief	Binds the given slot
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	slot	The slot.
		 */

		virtual void Bind(uint32_t slot) const = 0;

		/**
		 * @fn	virtual void Texture3D::Bind() const = 0;
		 *
		 * @brief	Binds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Bind() const = 0;

		/** @brief	Identifier for the renderer */
		uint32_t m_RendererID = 0;

		/** @brief	The slot */
		uint32_t m_Slot = 0;
		
	};

}
