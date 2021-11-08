#pragma once

#include "TNAH/Core/Ref.h"
#include "TNAH/Renderer/VertexArray.h"


namespace tnah {

	/**
	 * @class	OpenGLVertexArray
	 *
	 * @brief	An OpenGLVertexArray class that inherits from base class VertexArray.
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 */

	class OpenGLVertexArray : public VertexArray
	{
	public:

		/**
		 * @fn	OpenGLVertexArray::OpenGLVertexArray();
		 *
		 * @brief	Default constructor that generates the vertex array 
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		OpenGLVertexArray();

		/**
		 * @fn	virtual OpenGLVertexArray::~OpenGLVertexArray();
		 *
		 * @brief	Destructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		virtual ~OpenGLVertexArray();

		/**
		 * @fn	void OpenGLVertexArray::Bind() const override;
		 *
		 * @brief	Binds this object
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void Bind() const override;

		/**
		 * @fn	void OpenGLVertexArray::Unbind() const override;
		 *
		 * @brief	Unbinds this object
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void Unbind() const override;

		/**
		 * @fn	void OpenGLVertexArray::SetID(const uint32_t& id) override
		 *
		 * @brief	Sets an identifier
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	id	The identifier.
		 */

		void SetID(const uint32_t& id) override { m_RendererID = id; }

		/**
		 * @fn	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		 *
		 * @brief	Adds a vertex buffer
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	vertexBuffer	Buffer for vertex data.
		 */

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

		/**
		 * @fn	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		 *
		 * @brief	Sets index buffer
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	indexBuffer	Buffer for index data.
		 */

		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		/**
		 * @fn	void OpenGLVertexArray::SetIndexSize(const uint32_t& size) override
		 *
		 * @brief	Sets index size
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	size	The size.
		 */

		void SetIndexSize(const uint32_t& size) override { m_IndexSize = size; }

		/**
		 *
		 * @brief	Gets vertex buffers
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	std::vector<Ref<VertexBuffer>>&
		 */

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

		/**
		 * @fn	virtual const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
		 *
		 * @brief	Gets index buffer
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The index buffer.
		 */

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

		/**
		 * @fn	uint32_t OpenGLVertexArray::GetIndexSize() const override
		 *
		 * @brief	Gets index size
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The index size.
		 */

		uint32_t GetIndexSize() const override { return m_IndexSize; }
		
		void UpdateVertexBuffer() override;
	private:

		/** @brief	Identifier for the renderer */
		uint32_t m_RendererID;

		/** @brief	The vertex contains pointers belonging to multiple vertex buffers */
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;

		/** @brief	Pointer to the Buffer for index data */
		Ref<IndexBuffer> m_IndexBuffer;

		/** @brief	Size of the index */
		uint32_t m_IndexSize = 0;
	};


}

