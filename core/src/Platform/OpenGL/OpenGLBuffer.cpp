#include "tnahpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace tnah {
	/***********************************************************************/
	//Vertex Buffer
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case tnah::ShaderDataType::Float:    return GL_FLOAT;
		case tnah::ShaderDataType::Float2:   return GL_FLOAT;
		case tnah::ShaderDataType::Float3:   return GL_FLOAT;
		case tnah::ShaderDataType::Float4:   return GL_FLOAT;
		case tnah::ShaderDataType::Mat3:     return GL_FLOAT;
		case tnah::ShaderDataType::Mat4:     return GL_FLOAT;
		case tnah::ShaderDataType::Int:      return GL_INT;
		case tnah::ShaderDataType::Int2:     return GL_INT;
		case tnah::ShaderDataType::Int3:     return GL_INT;
		case tnah::ShaderDataType::Int4:     return GL_INT;
		case tnah::ShaderDataType::Bool:     return GL_BOOL;
		}

		TNAH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	

	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		glGenBuffers(1, &m_RendererID);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, uint32_t size)
	{
		auto f = static_cast<float*>(vertices);
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, f, GL_DYNAMIC_DRAW);
	}
	

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(uint32_t size, const void* data, DrawType type, TypeMode mode) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GetDrawMode(type, mode));
	}

	int OpenGLVertexBuffer::GetDrawMode(DrawType type, TypeMode mode)
	{
		if(type == DrawType::STATIC && mode == TypeMode::DRAW) return GL_STATIC_DRAW;
		if(type == DrawType::STATIC && mode == TypeMode::COPY) return GL_STATIC_COPY;
		if(type == DrawType::STATIC && mode == TypeMode::READ) return GL_STATIC_READ;

		if(type == DrawType::DYNAMIC && mode == TypeMode::DRAW) return GL_DYNAMIC_DRAW;
		if(type == DrawType::DYNAMIC && mode == TypeMode::COPY) return GL_DYNAMIC_COPY;
		if(type == DrawType::DYNAMIC && mode == TypeMode::READ) return GL_DYNAMIC_READ;

		if(type == DrawType::STREAM && mode == TypeMode::DRAW) return GL_STREAM_DRAW;
		if(type == DrawType::STREAM && mode == TypeMode::COPY) return GL_STREAM_COPY;
		if(type == DrawType::STREAM && mode == TypeMode::READ) return GL_STREAM_READ;

		return 0;
	}

	void OpenGLVertexBuffer::CreateLayout(uint32_t location, BufferElement element, uint32_t stride)
	{
		glEnableVertexAttribArray(location);
		if(element.Type == ShaderDataType::Int || element.Type == ShaderDataType::Int2 || element.Type == ShaderDataType::Int3 || element.Type == ShaderDataType::Int4)
		{
			glVertexAttribIPointer(location,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				stride,
				(const void*)element.Offset);
		}
		else
		{
			glVertexAttribPointer(location,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				stride,
				(const void*)element.Offset);
		}
	}

	void OpenGLVertexBuffer::DisableLayout(uint32_t location)
	{
		glDisableVertexAttribArray(location);
	}


	/***********************************************************************/
	//Index Buffer

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count), m_DataType(IndexBufferDataType::Int)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count)
		: m_Count(count), m_RendererID(0), m_DataType(IndexBufferDataType::Int)
	{
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(void* indices, uint32_t count)
		: m_Count(count), m_DataType(IndexBufferDataType::Int)
	{
		auto i = static_cast<uint32_t*>(indices);
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), i, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	int OpenGLIndexBuffer::GetDataType() const
	{
		switch(m_DataType)
		{
		case IndexBufferDataType::Byte:
			return GL_UNSIGNED_BYTE;
		case IndexBufferDataType::Short:
			return GL_UNSIGNED_SHORT;
		case IndexBufferDataType::Int:
			return GL_UNSIGNED_INT;
		default: return GL_UNSIGNED_INT;
		}
	}

	/***********************************************************************/
	//FrameBuffer
	
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec, uint32_t colorAttachments, uint32_t depthAttachments)
		:m_Specification(spec)
	{
		Invalidate(colorAttachments, depthAttachments);
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec, uint32_t colorAttachments, std::vector<ColorAttachmentSpecs> colorSpecs)
			:m_Specification(spec), m_ColorSpecifications(colorSpecs)
	{
		Invalidate(colorAttachments, 1);
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec,
		const RenderbufferSpecification& renderSpec)
			:m_Specification(spec)
	{
		Invalidate(0, 0, renderSpec);
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void OpenGLFramebuffer::Bind(uint32_t attachmentSlot)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		SelectDrawToBuffer(FramebufferDrawMode::Color, attachmentSlot);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Rebuild(const FramebufferSpecification& spec)
	{
		m_Specification = spec;
		glDeleteFramebuffers(1, &m_RendererID);
		for(auto c : m_ColorAttachments)
		{
			glDeleteTextures(1, &c);
		}
		for(auto d : m_DepthAttachments)
		{
			glDeleteTextures(1, &d);
		}
		m_ColorAttachments.clear();
		m_DepthAttachments.clear();
		
		Invalidate();
	}

	void OpenGLFramebuffer::SelectDrawToBuffer(const FramebufferDrawMode& mode, uint32_t attachmentNumber)
	{
		switch (mode)
		{
			case FramebufferDrawMode::Depth: break;
			case FramebufferDrawMode::Color: glDrawBuffer(GL_COLOR_ATTACHMENT0 + attachmentNumber); break;
			case FramebufferDrawMode::Stencil: break;
			case FramebufferDrawMode::Render: break;
			default: glDrawBuffer(GL_COLOR_ATTACHMENT0 + attachmentNumber);
		}
		m_ActiveColorAttachment = attachmentNumber;
	}

	void OpenGLFramebuffer::DrawToNext()
	{
		if(m_ActiveColorAttachment + 1 > m_ColorAttachments.size())
		{
			// loop back to the start
			SelectDrawToBuffer(FramebufferDrawMode::Color, 0);
			return;
		}

		SelectDrawToBuffer(FramebufferDrawMode::Color, m_ActiveColorAttachment + 1);
	}

	void OpenGLFramebuffer::SetRenderbufferSpecification(uint32_t bufferSlot, const RenderbufferSpecification& spec)
	{
		//TODO: remove buffer slot
		m_RenderbufferSpecification = spec;
	}

	void OpenGLFramebuffer::Invalidate(uint32_t color, uint32_t depth, RenderbufferSpecification renderSpec)
	{
		// check the framebuffer size, cant be less than 1x1
		bool errorW = false; bool errorH = false;
		if(m_Specification.Width <= 0)
		{
			m_Specification.Width = 1;
			errorW = true;
		}
		if(m_Specification.Height <= 0)
		{
			m_Specification.Height = 1;
			errorH = true;
		}
		
		if(errorW || errorH)
		{
			//Generate a warning about framebuffer resets
			std::string error = "Framebuffer minimum dimensions <= 1. \t";
			error += (errorW ? "Width reset to {0} \t" : "Width = {0} \t");
			error += (errorH ? "Height reset to {1}" : "Height = {1}");
			TNAH_CORE_WARN(error, m_Specification.Width, m_Specification.Height);
		}
		
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		for(uint32_t i = 0; i < color; i++)
		{
			uint32_t id;
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			const auto format = GetFormatFromSpec(m_Specification);
			glTexImage2D(GL_TEXTURE_2D, 0, format, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, id, 0);
			m_ColorAttachments.emplace_back(id);
		}

		if(depth > 0)
		{
			for(uint32_t i = 0; i < depth; i++)
			{
				uint32_t id;
				glGenTextures(1, &id);
				glBindTexture(GL_TEXTURE_2D, id);
				//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, id, 0);

				m_DepthAttachments.emplace_back(id);
			}
		}
		else if(renderSpec.IsValid)
		{
			
			m_RenderbufferSpecification = renderSpec;
			m_Renderbuffer = Renderbuffer::Create(renderSpec);
			m_Renderbuffer->AttachToFramebuffer();
		}

		TNAH_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete!")
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t OpenGLFramebuffer::GetColorAttachment(uint32_t attachmentNumber) const
	{
		if(attachmentNumber > m_ColorAttachments.size())
		{
			// if the color attachments are empty, return 0 else return the last attachment
			return (m_ColorAttachments.empty() ? 0 : m_ColorAttachments.back());	
		}

		return m_ColorAttachments[attachmentNumber];
	}

	uint32_t OpenGLFramebuffer::GetDepthAttachmentID(uint32_t attachmentNumber) const
	{
		if(attachmentNumber > m_DepthAttachments.size())
		{
			// if the color attachments are empty, return 0 else return the last attachment
			return (m_DepthAttachments.empty() ? 0 : m_DepthAttachments.back());	
		}

		return m_DepthAttachments[attachmentNumber];
	}
	
	int OpenGLFramebuffer::GetFormatFromSpec(const FramebufferSpecification& spec)
	{
		switch(spec.Format)
		{
			case FramebufferFormat::SDR:
				return GL_RGBA8;
			case FramebufferFormat::HDR:
				return GL_RGBA16F;
			default:
				return GL_RGBA8;
		}
	}

	/***********************************************************************/
	//Render Buffer
	
	OpenGLRenderBuffer::~OpenGLRenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_RendererID);
	}
	
	void OpenGLRenderBuffer::Bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
	}

	void OpenGLRenderBuffer::Unbind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void OpenGLRenderBuffer::Rebuild(const RenderbufferSpecification& spec)
	{
		m_Specification = spec;
		glDeleteRenderbuffers(1, &m_RendererID);
		Invalidate();
	}

	void OpenGLRenderBuffer::AttachToFramebuffer()
	{
		const auto fbFormat = (GLenum)GetFramebufferFormatFromSpecification(m_Specification);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, fbFormat, GL_RENDERBUFFER, m_RendererID);
	}


	OpenGLRenderBuffer::OpenGLRenderBuffer(const RenderbufferSpecification& spec)
		:m_Specification(spec)
	{
		Invalidate();
	}

	void OpenGLRenderBuffer::Invalidate()
	{
		glGenRenderbuffers(1, &m_RendererID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);

		const auto format = (GLenum)GetFormatFromSpecification(m_Specification);
		glRenderbufferStorage(GL_RENDERBUFFER, format, m_Specification.Width, m_Specification.Height);

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	int OpenGLRenderBuffer::GetFormatFromSpecification(const RenderbufferSpecification& spec)
	{
		switch (spec.Format)
		{
			case RenderbufferFormat::Depth16: return GL_DEPTH_COMPONENT16;
			case RenderbufferFormat::Depth24: return GL_DEPTH_COMPONENT24;
			case RenderbufferFormat::Depth32F: return GL_DEPTH_COMPONENT32F;
			case RenderbufferFormat::Depth24_Stencil8: return GL_DEPTH24_STENCIL8;
			case RenderbufferFormat::Depth32F_Stencil8:  return GL_DEPTH32F_STENCIL8;
			case RenderbufferFormat::Stencil8:  return GL_STENCIL_INDEX8;
			default: return GL_DEPTH24_STENCIL8;
		}
	}

	int OpenGLRenderBuffer::GetFramebufferFormatFromSpecification(const RenderbufferSpecification& spec)
	{
		switch(spec.Format)
		{
			case RenderbufferFormat::Depth16: return GL_DEPTH_ATTACHMENT;
			case RenderbufferFormat::Depth24: return GL_DEPTH_ATTACHMENT;
			case RenderbufferFormat::Depth32F: return GL_DEPTH_ATTACHMENT;
			case RenderbufferFormat::Depth24_Stencil8: return GL_DEPTH_STENCIL_ATTACHMENT;
			case RenderbufferFormat::Depth32F_Stencil8: return GL_DEPTH_STENCIL_ATTACHMENT;
			case RenderbufferFormat::Stencil8: return GL_STENCIL_ATTACHMENT;
			default: return GL_DEPTH_STENCIL_ATTACHMENT;
		}
	}


}
