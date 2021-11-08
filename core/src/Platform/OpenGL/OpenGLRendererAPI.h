#pragma once

#include "TNAH/Renderer/RendererAPI.h"

namespace tnah {

		/**
		 * @class	OpenGLRendererAPI
		 *
		 * @brief	An OpenGLRendererAPI class that inherits from the RendererAPI base class
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

	class OpenGLRendererAPI : public RendererAPI
	{
	public:

			/**
			 * @fn	void OpenGLRendererAPI::Init() override;
			 *
			 * @brief	Initializes this object
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void Init() override;

			/**
			 * @fn	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
			 *
			 * @brief	Sets the  glViewport
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	x	  	An uint32_t to process.
			 * @param 	y	  	An uint32_t to process.
			 * @param 	width 	The width.
			 * @param 	height	The height.
			 */

		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

			/**
			 * @fn	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) override;
			 *
			 * @brief	Sets clear color
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	color	The color provided in a vec4.
			 */

		void SetClearColor(const glm::vec4& color) override;

			/**
			 * @fn	void OpenGLRendererAPI::Clear() override;
			 *
			 * @brief	Clears this object to its blank/initial state
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void Clear() override;

			/**
			 * @fn	void OpenGLRendererAPI::Disable(const APIEnum& value) override;
			 *
			 * @brief	Disables the given value
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	value	The value.
			 */

		void Disable(const APIEnum& value) override;

			/**
			 * @fn	void OpenGLRendererAPI::Enable(const APIEnum& value) override;
			 *
			 * @brief	Enables the given value
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	value	The value.
			 */

		void Enable(const APIEnum& value) override;
		
			/**
			 * @fn	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) override;
			 *
			 * @brief	Draw indexed using glDrawElements
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	vertexArray	Array of vertices.
			 * @param	mode	Drawing Mode
			 * @param	indicesStart Pointer to the first element of the indices array. Void pointer to be any type
			 */

		void DrawIndexed(const Ref<VertexArray>& vertexArray, const DrawMode& mode = DrawMode::Triangles, void* indicesStart = nullptr) override;

			/**
			 * @fn	void OpenGLRendererAPI::DrawArray(const Ref<VertexArray>& vertexArray) override;
			 *
			 * @brief	Draws an array using glDrawArrays
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	vertexArray	Array of vertices.
			 */

		void DrawArray(const Ref<VertexArray>& vertexArray, const DrawMode& mode) override;

			/**
			 * @fn	void OpenGLRendererAPI::SetWireframe(const bool& enable) override;
			 *
			 * @brief	Sets a wireframe
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	enable	True to enable wireframe, false to disable.
			 */

		void SetWireframe(const bool& enable) override;

			/**
			 * @fn	bool OpenGLRendererAPI::CheckFullScreen(const int& width, const int& height) override;
			 *
			 * @brief	Check full screen
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	width 	The width.
			 * @param 	height	The height.
			 *
			 * @returns	True if it succeeds, false if it fails.
			 */

		bool CheckFullScreen(const int& width, const int& height) override;

			/**
			 * @fn	void OpenGLRendererAPI::SetCullMode(const CullMode& mode) override;
			 *
			 * @brief	Sets cull mode
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	mode	The mode.
			 */

		void SetCullMode(const CullMode& mode) override;

			/**
			 * @fn	void OpenGLRendererAPI::SetDepthMask(const bool& enabled) override;
			 *
			 * @brief	Sets depth mask
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	enabled	True to enable, false to disable.
			 */

		void SetDepthMask(const bool& enabled) override;

			/**
			 * @fn	void OpenGLRendererAPI::SetDepthFunc(const DepthFunc& func) override;
			 *
			 * @brief	Sets depth function
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	func	The function.
			 */

		void SetDepthFunc(const DepthFunc& func) override;
	
		protected:

			/**
			* @fn	void OpenGLRendererAPI::ModeFromDrawMode(const DrawMode& mode) override;
			*
			* @brief	Gets a API specific value based on provided Enum Mode.
			*
			* @note		This is a protected function as it is intended to be implemented per API but not accessed externally.
			*
			* @author	Dylan Blereau
			* @date	7/09/2021
			*
			* @param 	mode The mode enum.
			* @return	The API specific enum int value.
			*/
		int ModeFromDrawMode(const DrawMode& mode) override;
	};

}
