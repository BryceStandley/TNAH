#pragma once

#include "TNAH/Renderer/RenderingBuffers.h"

namespace tnah {

	/**
	 * @class	OpenGLVertexBuffer
	 *
	 * @brief	OpenGLVertexBuffer class that inherits from the VertexBuffer class
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 */

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		/**
		* @fn	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size);
		*
		* @brief	Constructor
		*
		* @author	Dylan Blereau
		* @date	7/09/2021
		*/

		OpenGLVertexBuffer();
		

			/**
			 * @fn	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size);
			 *
			 * @brief	Constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param [in,out]	vertices	If non-null, the vertices.
			 * @param 		  	size		The size of the buffer.
			 */

		OpenGLVertexBuffer(float* vertices, uint32_t size);

			/**
			 * @fn	OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, uint32_t size);
			 *
			 * @brief	Constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param [in,out]	vertices	If non-null, the vertices.
			 * @param 		  	size		The size of the buffer.
			 */

		OpenGLVertexBuffer(void* vertices, uint32_t size);

			
			/**
			 * @fn	virtual OpenGLVertexBuffer::~OpenGLVertexBuffer();
			 *
			 * @brief	Destructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		virtual ~OpenGLVertexBuffer();

		/**
		 * @fn	void OpenGLVertexBuffer::Bind() const override;
		 *
		 * @brief	Binds the buffer
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void Bind() const override;

		/**
		 * @fn	void OpenGLVertexBuffer::Unbind() const override;
		 *
		 * @brief	Unbinds the buffer
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void Unbind() const override;

			/**
			 * @fn	const BufferLayout& OpenGLVertexBuffer::GetLayout() const override
			 *
			 * @brief	Gets the layout of the buffer
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @returns	The layout.
			 */

		const VertexBufferLayout& GetLayout() const override { return m_Layout; }

			/**
			 * @fn	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout) override
			 *
			 * @brief	Sets the layout of a buffer
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	layout	The layout.
			 */

		void SetLayout(const VertexBufferLayout& layout) override { m_Layout = layout; }

		void SetData(uint32_t size, const void* data, DrawType type = DrawType::STATIC, TypeMode mode = TypeMode::DRAW) const override;
		static int GetDrawMode(DrawType type, TypeMode mode);
		void CreateLayout(uint32_t location, BufferElement element, uint32_t stride) override;


	public:
		void DisableLayout(uint32_t location) override;
	private:
			/** @brief	Identifier for the renderer */
		uint32_t m_RendererID;

			/** @brief	The buffer layout */
		VertexBufferLayout m_Layout;
	};

		/**
		 * @class	OpenGLIndexBuffer
		 *
		 * @brief	OpenGLIndexBuffer class that inherits from the IndexBuffer class.
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:

			/**
			 * @fn	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count);
			 *
			 * @brief	Constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	count	Number of vertices.
			 */

		OpenGLIndexBuffer(uint32_t count);

			/**
			 * @fn	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
			 *
			 * @brief	Constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param [in,out]	indices	If non-null, the indices.
			 * @param 		  	count  	Number of vertices.
			 */

		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

			/**
			 * @fn	OpenGLIndexBuffer::OpenGLIndexBuffer(void* indices, uint32_t count);
			 *
			 * @brief	Constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param [in,out]	indices	If non-null, the indices.
			 * @param 		  	count  	Number of.
			 */

		OpenGLIndexBuffer(void* indices, uint32_t count);

			/**
			 * @fn	virtual OpenGLIndexBuffer::~OpenGLIndexBuffer();
			 *
			 * @brief	Destructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		virtual ~OpenGLIndexBuffer();

			/**
			 * @fn	void OpenGLIndexBuffer::Bind() const override;
			 *
			 * @brief	Binds the index buffer
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void Bind() const override;

		/**
		 * @fn	void OpenGLIndexBuffer::Unbind() const override;
		 *
		 * @brief	Unbinds the index buffer
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void Unbind() const override;

			/**
			 * @fn	uint32_t OpenGLIndexBuffer::GetCount() const override
			 *
			 * @brief	Gets the count
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @returns	The count.
			 */

		uint32_t GetCount() const override { return m_Count; }
		int GetDataType() const override;
		private:

		IndexBufferDataType m_DataType;
		
			/** @brief	Identifier for the renderer */
		uint32_t m_RendererID;

			/** @brief	Number of */
		uint32_t m_Count;
	};

		/**
		 * @class	OpenGLFramebuffer
		 *
		 * @brief	An OpenGLFrameBuffer class that inherits from the FrameBuffer base class
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

	class OpenGLFramebuffer : public Framebuffer
	{
	public:

			/**
			 * @fn	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec, uint32_t colorAttachments = 1, uint32_t depthAttachments = 1);
			 *
			 * @brief	Constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	spec				The specifier.
			 * @param 	colorAttachments	(Optional) The color attachments.
			 * @param 	depthAttachments	(Optional) The depth attachments.
			 */

		OpenGLFramebuffer(const FramebufferSpecification& spec, uint32_t colorAttachments = 1, uint32_t depthAttachments = 1);

			/**
			 * @fn	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec, uint32_t colorAttachments, std::vector<ColorAttachmentSpecs> colorSpecs);
			 *
			 * @brief	Constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	spec				The specifier.
			 * @param 	colorAttachments	The color attachments.
			 * @param 	colorSpecs			The color specs.
			 */

		OpenGLFramebuffer(const FramebufferSpecification& spec, uint32_t colorAttachments, std::vector<ColorAttachmentSpecs> colorSpecs);

			/**
			 * @fn	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec, const RenderbufferSpecification& renderSpec);
			 *
			 * @brief	Constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	spec	  	The specifier.
			 * @param 	renderSpec	Information describing the render.
			 */

		OpenGLFramebuffer(const FramebufferSpecification& spec, const RenderbufferSpecification& renderSpec);

			/**
			 * @fn	virtual OpenGLFramebuffer::~OpenGLFramebuffer();
			 *
			 * @brief	Destructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		virtual ~OpenGLFramebuffer();

			/**
			 * @fn	void OpenGLFramebuffer::Bind(uint32_t attachmentSlot = 0) override;
			 *
			 * @brief	Binds the given attachment slot
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	attachmentSlot	(Optional) The attachment slot.
			 */

		void Bind(uint32_t attachmentSlot = 0) override;

			/**
			 * @fn	void OpenGLFramebuffer::Unbind() override;
			 *
			 * @brief	Unbinds the frameBuffer
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void Unbind() override;

			/**
			 * @fn	void OpenGLFramebuffer::Rebuild(const FramebufferSpecification& spec) override;
			 *
			 * @brief	Rebuilds the given specifier
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	spec	The specifier.
			 */

		void Rebuild(const FramebufferSpecification& spec) override;

			/**
			 * @fn	const FramebufferSpecification& OpenGLFramebuffer::GetSpecification() const override
			 *
			 * @brief	Gets the FrameBuffer specification
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @returns	The specification.
			 */

		const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

			/**
			 * @fn	void OpenGLFramebuffer::DrawToNext() override;
			 *
			 * @brief	Draws to the buffer
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void DrawToNext() override;

			/**
			 * @fn	uint32_t OpenGLFramebuffer::GetRendererID() const override
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
			 * @fn	uint32_t OpenGLFramebuffer::GetColorAttachment() const override
			 *
			 * @brief	Gets color attachment
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @returns	The color attachment.
			 */

		uint32_t GetColorAttachment() const override { return GetColorAttachment(0); }

			/**
			 * @fn	uint32_t OpenGLFramebuffer::GetColorAttachment(uint32_t attachmentNumber) const override;
			 *
			 * @brief	Gets color attachment
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	attachmentNumber	The attachment number.
			 *
			 * @returns	The color attachment.
			 */

		uint32_t GetColorAttachment(uint32_t attachmentNumber) const override;

			/**
			 * @fn	uint32_t OpenGLFramebuffer::GetTotalColorAttachments() const override
			 *
			 * @brief	Gets total color attachments
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @returns	The total color attachments.
			 */

		uint32_t GetTotalColorAttachments() const override { return (uint32_t)m_ColorAttachments.size(); }

			/**
			 * @fn	uint32_t OpenGLFramebuffer::GetDepthAttachmentID() const override
			 *
			 * @brief	Gets depth attachment identifier
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @returns	The depth attachment identifier.
			 */

		uint32_t GetDepthAttachmentID() const override { return GetDepthAttachmentID(0); }

			/**
			 * @fn	uint32_t OpenGLFramebuffer::GetDepthAttachmentID(uint32_t attachmentNumber) const override;
			 *
			 * @brief	Gets depth attachment identifier
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	attachmentNumber	The attachment number.
			 *
			 * @returns	The depth attachment identifier.
			 */

		uint32_t GetDepthAttachmentID(uint32_t attachmentNumber) const override;

			/**
			 * @fn	uint32_t OpenGLFramebuffer::GetTotalDepthAttachments() const override
			 *
			 * @brief	Gets total depth attachments
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @returns	The size of total depth attachments.
			 */

		uint32_t GetTotalDepthAttachments() const override { return (uint32_t)m_DepthAttachments.size(); }

			/**
			 * @fn	uint32_t OpenGLFramebuffer::GetRenderBufferID() const override
			 *
			 * @brief	Gets render buffer identifier
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @returns	The render buffer identifier.
			 */

		uint32_t GetRenderBufferID() const override { return m_Renderbuffer->GetRendererID(); }

			/**
			 * @fn	void OpenGLFramebuffer::SetRenderbufferSpecification(uint32_t bufferSlot, const RenderbufferSpecification& spec) override;
			 *
			 * @brief	Sets renderbuffer specification
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	bufferSlot	The buffer slot.
			 * @param 	spec	  	The specifier.
			 */

		void SetRenderbufferSpecification(uint32_t bufferSlot, const RenderbufferSpecification& spec) override;

			/**
			 * @fn	void OpenGLFramebuffer::SelectDrawToBuffer(const FramebufferDrawMode& mode, uint32_t attachmentNumber) override;
			 *
			 * @brief	Select draw to buffer mode
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	mode				The mode of the FrameBuffer.
			 * @param 	attachmentNumber	The attachment number.
			 */

		void SelectDrawToBuffer(const FramebufferDrawMode& mode, uint32_t attachmentNumber) override;

			/**
			 * @fn	int OpenGLFramebuffer::GetFormatFromSpec(const FramebufferSpecification& spec) override;
			 *
			 * @brief	Gets format from specifier
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	spec	The specifier.
			 *
			 * @returns	The format from specifier.
			 */

		int GetFormatFromSpec(const FramebufferSpecification& spec) override;

	private:

			/**
			 * @fn	void OpenGLFramebuffer::Invalidate(uint32_t color = 1, uint32_t depth = 1, RenderbufferSpecification renderSpec = {0} );
			 *
			 * @brief	Resets and regenerates frame buffer with new properties
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	color	  	(Optional) The color.
			 * @param 	depth	  	(Optional) The depth.
			 * @param 	renderSpec	(Optional) Information describing the render.
			 */

		void Invalidate(uint32_t color = 1, uint32_t depth = 1, RenderbufferSpecification renderSpec = {0} );
		

			/** @brief	Identifier for the renderer */
		uint32_t m_RendererID;

			/** @brief	The specification of the framebuffer */
		FramebufferSpecification m_Specification;
		
			/** @brief	A vector of color specifications */
		std::vector<ColorAttachmentSpecs> m_ColorSpecifications;

			/** @brief	A vector of color attachments */
		std::vector<uint32_t> m_ColorAttachments;

			/** @brief	A vector of depth attachments */
		std::vector<uint32_t> m_DepthAttachments;

			
			/** @brief	A pointer to the renderbuffer */
		Ref<Renderbuffer> m_Renderbuffer;


			/** @brief	The renderbuffer specification */
		RenderbufferSpecification m_RenderbufferSpecification;


			/** @brief	The active color attachment */
		uint32_t m_ActiveColorAttachment = 0;
		
	};

		/**
		 * @class	OpenGLRenderBuffer
		 *
		 * @brief	OpenGLRenderBuffer class that inherits from the RenderBuffer base class
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

	class OpenGLRenderBuffer : public Renderbuffer
	{
	public:

			/**
			 * @fn	virtual OpenGLRenderBuffer::~OpenGLRenderBuffer();
			 *
			 * @brief	Destructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		virtual ~OpenGLRenderBuffer();

			/**
			 * @fn	OpenGLRenderBuffer::OpenGLRenderBuffer(const RenderbufferSpecification& spec);
			 *
			 * @brief	Constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	spec	The specifier.
			 */

		OpenGLRenderBuffer(const RenderbufferSpecification& spec);

			/**
			 * @fn	uint32_t OpenGLRenderBuffer::GetRendererID() const override
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
			 * @fn	void OpenGLRenderBuffer::Bind() override;
			 *
			 * @brief	Binds the render buffer
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void Bind() override;

			/**
			 * @fn	void OpenGLRenderBuffer::Unbind() override;
			 *
			 * @brief	Unbinds the render buffer
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void Unbind() override;

			/**
			 * @fn	void OpenGLRenderBuffer::Rebuild(const RenderbufferSpecification& spec) override;
			 *
			 * @brief	Rebuilds the given specifier
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	spec	The specifier.
			 */

		void Rebuild(const RenderbufferSpecification& spec) override;

			/**
			 * @fn	void OpenGLRenderBuffer::AttachToFramebuffer() override;
			 *
			 * @brief	Attaches the render buffer to framebuffer
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void AttachToFramebuffer() override;

			/**
			 * @fn	int OpenGLRenderBuffer::GetFormatFromSpecification(const RenderbufferSpecification& spec) override;
			 *
			 * @brief	Gets format from specification
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	spec	The specifier.
			 *
			 * @returns	The format from specification.
			 */

		int GetFormatFromSpecification(const RenderbufferSpecification& spec) override;

			/**
			 * @fn	int OpenGLRenderBuffer::GetFramebufferFormatFromSpecification(const RenderbufferSpecification& spec) override;
			 *
			 * @brief	Gets framebuffer format from specification
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	spec	The specifier.
			 *
			 * @returns	The framebuffer format from specification.
			 */

		int GetFramebufferFormatFromSpecification(const RenderbufferSpecification& spec) override;

	private:

		/**
		* @fn	void OpenGLRenderBuffer::Invalidate();
		*
		* @brief	Resets and regenerates frame buffer with new properties
		*
		* @author	Dylan Blereau
		* @date	7/09/2021
		*/

		void Invalidate();
		
	
	private:

		/** @brief	Identifier for the renderer */
		uint32_t m_RendererID;


		/** @brief	The specification */
		RenderbufferSpecification m_Specification;
	};
}