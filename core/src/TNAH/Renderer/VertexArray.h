#pragma once

#include <memory>
#include "TNAH/Renderer/RenderingBuffers.h"

namespace tnah {

	/**
	 * @class	VertexArray
	 *
	 * @brief	VertexArray class that allows for the setup of a VAO
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class VertexArray : public RefCounted
	{
	public:

		/**
		 * @fn	virtual VertexArray::~VertexArray() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~VertexArray() = default;

		/**
		 * @fn	virtual void VertexArray::Bind() const = 0;
		 *
		 * @brief	Binds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Bind() const = 0;

		/**
		 * @fn	virtual void VertexArray::Unbind() const = 0;
		 *
		 * @brief	Unbinds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Unbind() const = 0;

		/**
		 * @fn	virtual void VertexArray::SetID(const uint32_t& id) = 0;
		 *
		 * @brief	Sets an identifier
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	id	The identifier.
		 */

		virtual void SetID(const uint32_t& id) = 0;

		/**
		 * @fn	virtual void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		 *
		 * @brief	Adds a vertex buffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexBuffer	Buffer for vertex data.
		 */

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;


		/**
		 * @fn	virtual void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
		 *
		 * @brief	Sets index buffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	indexBuffer	Buffer for index data.
		 */

		virtual void UpdateVertexBuffer() = 0;

		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		/**
		 * @fn	virtual void VertexArray::SetIndexSize(const uint32_t& size) = 0;
		 *
		 * @brief	Sets index size
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	size	The size.
		 */

		virtual void SetIndexSize(const uint32_t& size) = 0;

		/**
		 * @fn	virtual const std::vector<Ref<VertexBuffer>>& VertexArray::GetVertexBuffers() const = 0;
		 *
		 * @brief	Gets vertex buffers
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The vertex buffers.
		 */

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

		/**
		 * @fn	virtual const Ref<IndexBuffer>& VertexArray::GetIndexBuffer() const = 0;
		 *
		 * @brief	Gets index buffer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The index buffer.
		 */

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		/**
		 * @fn	virtual uint32_t VertexArray::GetIndexSize() const = 0;
		 *
		 * @brief	Gets index size
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The index size.
		 */

		virtual uint32_t GetIndexSize() const = 0;

		

		/**
		 * @fn	static VertexArray* VertexArray::Create();
		 *
		 * @brief	Creates a new VertexArray and binds it for use
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	Null if it fails, else a pointer to a VertexArray.
		 */

		static VertexArray* Create();

		/** @brief	Size of the indices */
		uint32_t m_IndicesSize;
	};

}
