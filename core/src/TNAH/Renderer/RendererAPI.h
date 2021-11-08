#pragma once
#include <TNAH/Core/Core.h>
#include "TNAH/Renderer/VertexArray.h"

namespace tnah {

	/**
	 * @enum	CullMode
	 *
	 * @brief	Values that represent cull modes
	 */

	enum class CullMode
	{
		Front = 0,
		Back = 1,
		Front_And_Back = 2,
		Disabled = 3
	};

	

	/**
	* @enum	DepthFunc
	*
	* @brief	Values that represent depth Functions
	*/

	enum class DepthFunc
	{
		Never, Less, Equal, Lequal, Greater, NotEqual, Gequal, Always
	};

	/**
	* @enum	APIEnum
	*
	* @brief	Values that represent API enums
	*/
	enum class APIEnum
	{
		CullFace, DepthTest, DepthMask,
		FrontFace_CW, FrontFace_CCW,
		CubeMap
	};

	/**
	* @enum	DrawMode
	*
	* @brief	Different modes for drawing
	*/
	enum class DrawMode
	{
		Points,
		Lines, Line_Strip, Line_Loop, Line_Strip_Adjacency, Lines_Adjacency,
		Triangle_Strip, Triangle_Fan, Triangles, Triangles_Strip_Adjacency, Triangles_Adjacency,
		Patches
	};

	/**
	* @class	RendererAPI
	*
	* @brief	A renderer API class that provides the functions required to render, regardless of API used
	*
	* @author	Bryce Standley
	* @date	12/09/2021
	*/
	class RendererAPI
	{
	public:

		/**
		 * @enum	API
		 *
		 * @brief	Values that represent apis
		 */

		enum class API
		{
			None = 0, OpenGL = 1
		};
		

		/**
		 * @fn	virtual RendererAPI::~RendererAPI() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~RendererAPI() = default;

		/**
		 * @fn	virtual void RendererAPI::Init() = 0;
		 *
		 * @brief	Initializes this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Init() = 0;

		/**
		 * @fn	virtual void RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		 *
		 * @brief	Sets a viewport
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	x	  	An uint32_t to process.
		 * @param 	y	  	An uint32_t to process.
		 * @param 	width 	The width.
		 * @param 	height	The height.
		 */

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		/**
		 * @fn	virtual void RendererAPI::SetClearColor(const glm::vec4& color) = 0;
		 *
		 * @brief	Sets clear color
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	color	The color.
		 */

		virtual void SetClearColor(const glm::vec4& color) = 0;

		/**
		 * @fn	virtual void RendererAPI::Clear() = 0;
		 *
		 * @brief	Clears this object to its blank/initial state
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Clear() = 0;

		/**
		 * @fn	virtual void RendererAPI::Disable(const APIEnum& value) = 0;
		 *
		 * @brief	Disables the given value
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	value	The value.
		 */

		virtual void Disable(const APIEnum& value) = 0;

		/**
		 * @fn	virtual void RendererAPI::Enable(const APIEnum& value) = 0;
		 *
		 * @brief	Enables the given value
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	value	The value.
		 */

		virtual void Enable(const APIEnum& value) = 0;
		;

		/**
		 * @fn	virtual void RendererAPI::DrawArray(const Ref<VertexArray>& vertexArray, const DrawMode& mode = DrawMode::Triangles) = 0;
		 *
		 * @brief	Draws a vertex array
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexArray The VertexArray object to be bound and drawn from.
		 * @param 	mode The draw mode of the VertexArray. Default to DrawMode::Triangles
		 */

		virtual void DrawArray(const Ref<VertexArray>& vertexArray, const DrawMode& mode = DrawMode::Triangles) = 0;

		/**
		 * @fn	virtual void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, const DrawMode& mode = DrawMode::Triangles, void* indicesStart = nullptr) = 0;
		 *
		 * @brief	Draw indexed
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexArray	Array of vertices.
		 * @param 	mode	The draw mode of the VertexArray. Default to DrawMode::Triangles
		 * @param 	indicesStart	Starting position of the indices. 
		 */

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, const DrawMode& mode = DrawMode::Triangles, void* indicesStart = nullptr) = 0;

		
		
		
		/**
		 * @fn	virtual void RendererAPI::SetWireframe(const bool& enable) = 0;
		 *
		 * @brief	Sets a wireframe
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	enable	True to enable, false to disable.
			*/
		

		virtual void SetWireframe(const bool& enable) = 0;

		/**
		 * @fn	virtual bool RendererAPI::CheckFullScreen(const int& width, const int& height) = 0;
		 *
		 * @brief	Check full screen
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	width 	The width.
		 * @param 	height	The height.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		virtual bool CheckFullScreen(const int& width, const int& height) = 0;

		/**
		 * @fn	virtual void RendererAPI::SetCullMode(const CullMode& mode) = 0;
		 *
		 * @brief	Sets cull mode
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	mode	The mode.
		 */

		virtual void SetCullMode(const CullMode& mode) = 0;

		/**
		 * @fn	virtual void RendererAPI::SetDepthMask(const bool& enabled) = 0;
		 *
		 * @brief	Sets depth mask
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	enabled	True to enable, false to disable.
		 */

		virtual void SetDepthMask(const bool& enabled) = 0;

		/**
		 * @fn	virtual void RendererAPI::SetDepthFunc(const DepthFunc& enabled) = 0;
		 *
		 * @brief	Sets depth function
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	enabled	The enabled.
		 */

		virtual void SetDepthFunc(const DepthFunc& enabled) = 0;

		/**
		 * @fn	static API RendererAPI::GetAPI()
		 *
		 * @brief	Gets api
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	api.
		 */

		static API GetAPI() { return s_API; }

		/**
		 * @fn	static Scope<RendererAPI> RendererAPI::Create();
		 *
		 * @brief	Creates a unique ptr to the API ;
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	A unique ptr to the API;
		 */

		static Scope<RendererAPI> Create();
	
	protected:
		/**
		 * 
		 * \fn int ModeFromDrawMode
		 * 
		 * \brief Gets the mode from a given DrawMode. This is intended to be overwritten by a derived API class.
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param mode The mode to get.
		 * 
		 * \return int value of the API mode.
		 * 
		 */
		virtual int ModeFromDrawMode(const DrawMode& mode) = 0;
	
	private:

		/** @brief	The API */
		static API s_API;
	};

}

