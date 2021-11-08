#include "tnahpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace tnah {

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
		case ShaderDataType::UInt:		return GL_UNSIGNED_INT;
		case tnah::ShaderDataType::Int:      return GL_INT;
		case tnah::ShaderDataType::Int2:     return GL_INT;
		case tnah::ShaderDataType::Int3:     return GL_INT;
		case tnah::ShaderDataType::Int4:     return GL_INT;
		case tnah::ShaderDataType::Bool:     return GL_BOOL;
		}

		TNAH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		TNAH_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::UpdateVertexBuffer()
	{
		glBindVertexArray(m_RendererID);
		m_VertexBuffers.at(0)->Bind();

		uint32_t index = 0;
		const auto& layout = m_VertexBuffers.at(0)->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			if(VertexBuffer::CheckIntShaderDataTypes(element))
			{
				glVertexAttribIPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
			}
			else
			{
				glVertexAttribPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
			}
			
			index++;
		}
	}

}
