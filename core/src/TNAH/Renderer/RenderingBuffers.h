#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TNAH/Core/Ref.h"

namespace tnah {

	/**
	 * @enum	ShaderDataType
	 *
	 * @brief	Values that represent shader data types
	 */

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool,
		UInt
	};

	/**
	 * @fn	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	 *
	 * @brief	Shader data type size
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 *
	 * @param 	type	The type.
	 *
	 * @returns	An uint32_t.
	 */

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::UInt:		return 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
			case ShaderDataType::None: break;
		default: break;
		}

		TNAH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	/**
	 * @struct	BufferElement
	 *
	 * @brief	A buffer element.
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	struct BufferElement
	{

		/** @brief	The name */
		std::string Name;

		/** @brief	The type */
		ShaderDataType Type;

		/** @brief	The size */
		uint32_t Size;

		/** @brief	The offset */
		size_t Offset;

		/** @brief	True if normalized */
		bool Normalized;

		/**
		 * @fn	BufferElement() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		BufferElement() = default;

		/**
		 * @fn	BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	type	  	The type.
		 * @param 	name	  	The name.
		 * @param 	normalized	(Optional) True if normalized.
		 */

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		/**
		 * @fn	uint32_t GetComponentCount() const
		 *
		 * @brief	Gets component count
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The component count.
		 */

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3; // 3* float3
				case ShaderDataType::Mat4:    return 4; // 4* float4
				case ShaderDataType::UInt:		return 3;
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
				default: break;
			}

			TNAH_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	/**
	* @class	VertexBufferLayout
	*
	* @brief	A buffer layout class responsible for handling the contents of a buffer
	*
	* @author	Bryce Standley
	* @date	12/09/2021
	*/
	class VertexBufferLayout
	{
	public:
		/**
		* @fn	VertexBufferLayout::VertexBufferLayout()
		*
		* @brief	Default constructor
		*
		* @author	Bryce Standley
		* @date	12/09/2021
		*/
		VertexBufferLayout() {}

		/**
		* @fn	VertexBufferLayout::VertexBufferLayout(std::initializer_list<BufferElement> elements)
		*
		* @brief	Constructor
		*
		* @author	Bryce Standley
		* @date	12/09/2021
		*
		* @param 	elements	The elements.
		*/
		VertexBufferLayout(std::initializer_list<BufferElement> elements)

			: m_Elements(elements)
		{
			CalculateOffsetsAndStride(m_Elements, m_Stride);
		}

		/**
		 * @fn	uint32_t VertexBufferLayout::GetStride() const
		 *
		 * @brief	Gets the stride
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The stride.
		 */

		uint32_t GetStride() const { return m_Stride; }

		/**
		 * @fn	const std::vector<BufferElement>& VertexBufferLayout::GetElements() const
		 *
		 * @brief	Gets the elements
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The elements.
		 */

		const std::vector<BufferElement>& GetElements() const { return m_Elements; }


		/**
		 * @fn	std::vector<BufferElement>::iterator VertexBufferLayout::begin()
		 *
		 * @brief	Gets an iterator from the begin point of a vector
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	A std::vector<BufferElement>::iterator.
		 */


		std::vector<BufferElement>& GetElements() { return m_Elements; }
		void SetStride(const uint32_t& stride) { m_Stride = stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }

		/**
		 * @fn	std::vector<BufferElement>::iterator VertexBufferLayout::end()
		 *
		 * @brief	Gets an iterator from the end point of a vector
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	A std::vector<BufferElement>::iterator.
		 */

		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		/**
		 * @fn	std::vector<BufferElement>::const_iterator VertexBufferLayout::begin() const
		 *
		 * @brief	Gets a const iterator from the begin point of a vector
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	A std::vector<BufferElement>::const_iterator.
		 */

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }

		/**
		 * @fn	std::vector<BufferElement>::const_iterator VertexBufferLayout::end() const
		 *
		 * @brief	Gets a const iterator from the end point of a vector
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	A std::vector&lt;BufferElement&gt;::const_iterator.
		 */

		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:

		/**
		 * @fn	static void VertexBufferLayout::CalculateOffsetsAndStride(std::vector<BufferElement>& elements, uint32_t& stride)
		 *
		 * @brief	Calculates the offsets and stride
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	elements	The elements.
		 * @param [in,out]	stride  	The stride.
		 */

		static void CalculateOffsetsAndStride(std::vector<BufferElement>& elements, uint32_t& stride)
		{
			size_t offset = 0;
			stride = 0;
			for (auto& element : elements)
			{
				element.Offset = offset;
				offset += element.Size;
				stride += element.Size;
			}
		}
	private:

		/** @brief	The elements */
		std::vector<BufferElement> m_Elements;

		/** @brief	The stride */
		uint32_t m_Stride = 0;

		friend class VertexBuffer;
	};

	/**
	 * @enum	DrawType
	 *
	 * @brief	Values that represent draw types
	 */

	enum class DrawType
	{
		STREAM, STATIC, DYNAMIC
	};

	/**
	 * @enum	TypeMode
	 *
	 * @brief	Values that represent type modes
	 */

	enum class TypeMode
	{
		DRAW, READ, COPY
	};


	/**
	 * @struct	BufferDrawMode
	 *
	 * @brief	A draw mode.
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	struct BufferDrawMode

	{
		DrawType Type = DrawType::STATIC;
		TypeMode Mode = TypeMode::DRAW;
	};

	/**
	 * @class	VertexBuffer
	 *
	 * @brief	VertexBuffer class that abstracts the opengl calls required to use a vbo 
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class VertexBuffer : public RefCounted
	{
	public:

		/**
		 * @fn	virtual VertexBuffer::~VertexBuffer() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~VertexBuffer() = default;

		/**
		 * @fn	virtual void VertexBuffer::Bind() const = 0;
		 *
		 * @brief	Binds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Bind() const = 0;

		/**
		 * @fn	virtual void VertexBuffer::Unbind() const = 0;
		 *
		 * @brief	Unbinds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Unbind() const = 0;

		/**
		 * @fn	virtual void VertexBuffer::SetData(uint32_t size, const void* data, DrawType type = DrawType::STATIC, TypeMode mode = TypeMode::DRAW) const = 0;
		 *
		 * @brief	Sets data
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	size	The size.
		 * @param 	data	The data.
		 * @param 	type	(Optional) The draw type.
		 * @param 	mode	(Optional) The type mode.
		 */

		virtual void SetData(uint32_t size, const void* data, DrawType type = DrawType::STATIC, TypeMode mode = TypeMode::DRAW) const = 0;

		/**
		 * @fn	virtual void VertexBuffer::CreateLayout(uint32_t location, BufferElement element, uint32_t stride) = 0;
		 *
		 * @brief	Creates a layout
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	location	The location.
		 * @param 	element 	The element.
		 * @param 	stride  	The stride.
		 */

		virtual void CreateLayout(uint32_t location, BufferElement element, uint32_t stride) = 0;

		/**
		 * @fn	virtual void VertexBuffer::DisableLayout(uint32_t location) = 0;
		 *
		 * @brief	Disables the layout
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	location	The location.
		 */

		virtual void DisableLayout(uint32_t location) = 0;


		/**
		 * @fn	virtual const VertexBufferLayout& VertexBuffer::GetLayout() const = 0;
		 *
		 * @brief	Gets the layout
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The layout.
		 */
		virtual const VertexBufferLayout& GetLayout() const = 0;

		/**
		 * @fn	virtual void VertexBuffer::SetLayout(const VertexBufferLayout& layout) = 0;
		 *
		 * @brief	Sets a layout
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	layout	The layout.
		 */
		virtual void SetLayout(const VertexBufferLayout& layout) = 0;

		/**
		 * @fn	static Ref<VertexBuffer> VertexBuffer::Create();
		 *
		 * @brief	Creates a new VertexBuffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	A VertexBuffer
		 */
		static Ref<VertexBuffer> Create();

		
		

		
		static bool CheckIntShaderDataTypes(const BufferElement& element);
		
		/**
		 * @fn	static Ref<VertexBuffer> VertexBuffer::Create(float* verticies, uint32_t size);
		 *
		 * @brief	Creates a new VertexBuffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	verticies	If non-null, the verticies.
		 * @param 		  	size	 	The size.
		 *
		 * @returns	A VertexBuffer
		 */

		static Ref<VertexBuffer> Create(float* verticies, uint32_t size);

		/**
		 * @fn	static Ref<VertexBuffer> VertexBuffer::Create(void* verticies, uint32_t size);
		 *
		 * @brief	Creates a new VertexBuffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	verticies	If non-null, the verticies.
		 * @param 		  	size	 	The size.
		 *
		 * @returns	A VertexBuffer
		 */

		static Ref<VertexBuffer> Create(void* verticies, uint32_t size);
	};

	/**
	 * @class	IndexBuffer
	 *
	 * @brief	Class that allows for the creation of Index Buffers (IBO)
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */


	enum class IndexBufferDataType
	{
		Byte = 0, Short = 1, Int = 2
	};
	
	// Currently tnah only supports 32-bit index buffers

	class IndexBuffer : public RefCounted
	{
	public:

		/**
		 * @fn	virtual IndexBuffer::~IndexBuffer() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~IndexBuffer() = default;

		/**
		 * @fn	virtual void IndexBuffer::Bind() const = 0;
		 *
		 * @brief	Binds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Bind() const = 0;

		/**
		 * @fn	virtual void IndexBuffer::Unbind() const = 0;
		 *
		 * @brief	Unbinds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Unbind() const = 0;

		/**
		 * @fn	virtual uint32_t IndexBuffer::GetCount() const = 0;
		 *
		 * @brief	Gets the count
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The count.
		 */
		virtual uint32_t GetCount() const = 0;


		virtual int GetDataType() const = 0;
		
		/**
		 * @fn	static Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size);
		 *
		 * @brief	Creates a new IndexBuffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	indices	If non-null, the indices.
		 * @param 		  	size   	The size.
		 *
		 * @returns	An IndexBuffer
		 */

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t size);

		/**
		 * @fn	static Ref<IndexBuffer> IndexBuffer::Create(void* indices, uint32_t size);
		 *
		 * @brief	Creates a new IndexBuffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	indices	If non-null, the indices.
		 * @param 		  	size   	The size.
		 *
		 * @returns	An IndexBuffer
		 */

		static Ref<IndexBuffer> Create(void* indices, uint32_t size);

		/**
		 * @fn	static Ref<IndexBuffer> IndexBuffer::Create(uint32_t size);
		 *
		 * @brief	Creates an empty index buffer with a size.
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	size	The size.
		 *
		 * @returns	An IndexBuffer
		 */

		static Ref<IndexBuffer> Create(uint32_t size);
	};

	/**
	 * @enum	RenderbufferFormat
	 *
	 * @brief	Values that represent renderbuffer formats
	 */

	enum class RenderbufferFormat
	{
		Depth16, Depth24, Depth32F,
		Depth24_Stencil8, Depth32F_Stencil8,
		Stencil8
		
	};

	/**
	 * @struct	RenderbufferSpecification
	 *
	 * @brief	A renderbuffer specification.
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	struct RenderbufferSpecification
	{

		/** @brief	The width */
		uint32_t Width = 0;

		/** @brief	The height */
		uint32_t Height = 0;

		/** @brief	Describes the format to use */
		RenderbufferFormat Format = RenderbufferFormat::Depth24_Stencil8;
		
		/** @brief	The samples */
		uint32_t Samples = 1;

		/** @brief	True to swap chain target */
		bool SwapChainTarget = false;

		/** @brief	True if is valid, false if not */
		bool IsValid = true;

		/**
		 * @fn	RenderbufferSpecification() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		RenderbufferSpecification() = default;

		/**
		 * @fn	RenderbufferSpecification(uint32_t valid)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	valid	The valid.
		 */

		RenderbufferSpecification(uint32_t valid)
			:IsValid(false) {}
	};

	/**
	 * @enum	FramebufferFormat
	 *
	 * @brief	Values that represent framebuffer formats
	 */

	enum class FramebufferFormat
	{
		SDR, HDR
	};

	/**
	 * @struct	FramebufferSpecification
	 *
	 * @brief	A framebuffer specification.
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	struct FramebufferSpecification
	{

		/** @brief	The width */
		uint32_t Width = 0;

		/** @brief	The height */
		uint32_t Height = 0;

		/** @brief	Describes the format to use */
		FramebufferFormat Format = FramebufferFormat::SDR;

		/** @brief	The samples */
		uint32_t Samples = 1;

		/** @brief	True to swap chain target */
		bool SwapChainTarget = false;
	};

	struct ColorAttachmentSpecs
	{

		/** @brief	The width */
		uint32_t Width = 0;

		/** @brief	The height */
		uint32_t Height = 0;

		/** @brief	Describes the format to use */
		FramebufferFormat Format = FramebufferFormat::SDR;

	};

	/**
	 * @enum	FramebufferDrawMode
	 *
	 * @brief	Values that represent framebuffer draw modes
	 */

	enum class FramebufferDrawMode
	{
		Depth, Color, Stencil, Render
	};

	/**
	 * @class	Framebuffer
	 *
	 * @brief	A framebuffer class
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class Framebuffer : public RefCounted
	{
	public:

		/**
		 * @fn	virtual Framebuffer::~Framebuffer() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~Framebuffer() = default;

		/**
		 * @fn	virtual const FramebufferSpecification& Framebuffer::GetSpecification() const = 0;
		 *
		 * @brief	Gets the specification
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The specification.
		 */

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		/**
		 * @fn	virtual void Framebuffer::DrawToNext() = 0;
		 *
		 * @brief	Draw to next
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void DrawToNext() = 0;

		/**
		 * @fn	virtual uint32_t Framebuffer::GetColorAttachment() const = 0;
		 *
		 * @brief	Gets color attachment
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The color attachment.
		 */

		virtual uint32_t GetColorAttachment() const = 0;

		/**
		 * @fn	virtual uint32_t Framebuffer::GetColorAttachment(uint32_t attachmentNumber) const = 0;
		 *
		 * @brief	Gets color attachment
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	attachmentNumber	The attachment number.
		 *
		 * @returns	The color attachment.
		 */

		virtual uint32_t GetColorAttachment(uint32_t attachmentNumber) const = 0;

		/**
		 * @fn	virtual uint32_t Framebuffer::GetTotalColorAttachments() const = 0;
		 *
		 * @brief	Gets total color attachments
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The total color attachments.
		 */

		virtual uint32_t GetTotalColorAttachments() const = 0;

		/**
		 * @fn	virtual uint32_t Framebuffer::GetDepthAttachmentID() const = 0;
		 *
		 * @brief	Gets depth attachment identifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The depth attachment identifier.
		 */

		virtual uint32_t GetDepthAttachmentID() const = 0;

		/**
		 * @fn	virtual uint32_t Framebuffer::GetDepthAttachmentID(uint32_t attachmentNumber) const = 0;
		 *
		 * @brief	Gets depth attachment identifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	attachmentNumber	The attachment number.
		 *
		 * @returns	The depth attachment identifier.
		 */

		virtual uint32_t GetDepthAttachmentID(uint32_t attachmentNumber) const = 0;

		/**
		 * @fn	virtual uint32_t Framebuffer::GetTotalDepthAttachments() const = 0;
		 *
		 * @brief	Gets total depth attachments
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The total depth attachments.
		 */

		virtual uint32_t GetTotalDepthAttachments() const = 0;

		/**
		 * @fn	virtual uint32_t Framebuffer::GetRenderBufferID() const = 0;
		 *
		 * @brief	Gets render buffer identifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The render buffer identifier.
		 */

		virtual uint32_t GetRenderBufferID() const = 0;

		/**
		 * @fn	virtual void Framebuffer::SetRenderbufferSpecification(uint32_t bufferSlot, const RenderbufferSpecification& spec) = 0;
		 *
		 * @brief	Sets renderbuffer specification
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	bufferSlot	The buffer slot.
		 * @param 	spec	  	The specifier.
		 */

		virtual void SetRenderbufferSpecification(uint32_t bufferSlot, const RenderbufferSpecification& spec) = 0;

		/**
		 * @fn	virtual uint32_t Framebuffer::GetRendererID() const = 0;
		 *
		 * @brief	Gets renderer identifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The renderer identifier.
		 */

		virtual uint32_t GetRendererID() const = 0;

		/**
		 * @fn	virtual void Framebuffer::Bind(uint32_t attachmentSlot = 0) = 0;
		 *
		 * @brief	Binds the given attachment slot
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	attachmentSlot	(Optional) The attachment slot.
		 */

		virtual void Bind(uint32_t attachmentSlot = 0) = 0;

		/**
		 * @fn	virtual void Framebuffer::Unbind() = 0;
		 *
		 * @brief	Unbinds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Unbind() = 0;

		/**
		 * @fn	virtual void Framebuffer::Rebuild(const FramebufferSpecification& spec) = 0;
		 *
		 * @brief	Rebuilds the given specifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	spec	The specifier.
		 */

		virtual void Rebuild(const FramebufferSpecification& spec) = 0;

		/**
		 * @fn	static Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec, uint32_t colorAttachments = 1, uint32_t depthAttachments = 1);
		 *
		 * @brief	Creates a new FrameBuffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	spec				The specifier.
		 * @param 	colorAttachments	(Optional) The color attachments.
		 * @param 	depthAttachments	(Optional) The depth attachments.
		 *
		 * @returns	A FrameBuffer
		 */

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec, uint32_t colorAttachments = 1, uint32_t depthAttachments = 1);

		/**
		 * @fn	static Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec, uint32_t colorAttachments, std::vector<ColorAttachmentSpecs> colorSpecs);
		 *
		 * @brief	Creates a new FrameBuffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	spec				The specifier.
		 * @param 	colorAttachments	The color attachments.
		 * @param 	colorSpecs			The color specs.
		 *
		 * @returns	A FrameBuffer
		 */

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec, uint32_t colorAttachments, std::vector<ColorAttachmentSpecs> colorSpecs);

		/**
		 * @fn	static Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec, const RenderbufferSpecification& renderSpec);
		 *
		 * @brief	Creates a new FrameBuffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	spec	  	The specifier.
		 * @param 	renderSpec	Information describing the render.
		 *
		 * @returns	A FrameBuffer
		 */

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec, const RenderbufferSpecification& renderSpec);

		/**
		 * @fn	virtual void Framebuffer::SelectDrawToBuffer(const FramebufferDrawMode& mode = FramebufferDrawMode::Color, uint32_t attachmentNumber = 0) = 0;
		 *
		 * @brief	Select draw to buffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	mode				(Optional) The mode.
		 * @param 	attachmentNumber	(Optional) The attachment number.
		 */

		virtual void SelectDrawToBuffer(const FramebufferDrawMode& mode = FramebufferDrawMode::Color, uint32_t attachmentNumber = 0) = 0;

		/**
		 * @fn	virtual int Framebuffer::GetFormatFromSpec(const FramebufferSpecification& spec) = 0;
		 *
		 * @brief	Gets format from specifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	spec	The specifier.
		 *
		 * @returns	The format from specifier.
		 */

		virtual int GetFormatFromSpec(const FramebufferSpecification& spec) = 0;
	};

	/**
	 * @class	Renderbuffer
	 *
	 * @brief	A renderbuffer class. Inherits from RefCounted to allow the class to use Ref pointer
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class Renderbuffer : public RefCounted
	{
	public:

		/**
		 * @fn	virtual Renderbuffer::~Renderbuffer() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~Renderbuffer() = default;

		/**
		 * @fn	virtual uint32_t Renderbuffer::GetRendererID() const = 0;
		 *
		 * @brief	Gets renderer identifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The renderer identifier.
		 */

		virtual uint32_t GetRendererID() const = 0;

		/**
		 * @fn	virtual void Renderbuffer::Bind() = 0;
		 *
		 * @brief	Binds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Bind() = 0;

		/**
		 * @fn	virtual void Renderbuffer::Unbind() = 0;
		 *
		 * @brief	Unbinds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Unbind() = 0;

		/**
		 * @fn	virtual void Renderbuffer::Rebuild(const RenderbufferSpecification& spec) = 0;
		 *
		 * @brief	Rebuilds the given specifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	spec	The specifier.
		 */

		virtual void Rebuild(const RenderbufferSpecification& spec) = 0;

		/**
		 * @fn	virtual void Renderbuffer::AttachToFramebuffer() = 0;
		 *
		 * @brief	Attach to framebuffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void AttachToFramebuffer() = 0;

		/**
		 * @fn	static Ref<Renderbuffer> Renderbuffer::Create(const RenderbufferSpecification& spec);
		 *
		 * @brief	Creates a new RenderBuffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	spec	The specifier.
		 *
		 * @returns	A RenderBuffer
		 */

		static Ref<Renderbuffer> Create(const RenderbufferSpecification& spec);

		/**
		 * @fn	virtual int Renderbuffer::GetFormatFromSpecification(const RenderbufferSpecification& spec) = 0;
		 *
		 * @brief	Gets format from specification
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	spec	The specifier.
		 *
		 * @returns	The format from specification.
		 */

		virtual int GetFormatFromSpecification(const RenderbufferSpecification& spec) = 0;

		/**
		 * @fn	virtual int Renderbuffer::GetFramebufferFormatFromSpecification(const RenderbufferSpecification& spec) = 0;
		 *
		 * @brief	Gets framebuffer format from specification
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	spec	The specifier.
		 *
		 * @returns	The framebuffer format from specification.
		 */

		virtual int GetFramebufferFormatFromSpecification(const RenderbufferSpecification& spec) = 0;
	private:
		

		friend class Framebuffer;
		
	};

}
