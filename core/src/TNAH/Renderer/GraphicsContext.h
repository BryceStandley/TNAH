#pragma once

namespace tnah {

	/**
	 * @class	GraphicsContext
	 *
	 * @brief	The graphics context
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class GraphicsContext
	{
	public:

		/**
		 * @fn	virtual GraphicsContext::~GraphicsContext() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~GraphicsContext() = default;

		/**
		 * @fn	virtual void GraphicsContext::Init() = 0;
		 *
		 * @brief	Initializes this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Init() = 0;

		/**
		 * @fn	virtual void GraphicsContext::SwapBuffers() = 0;
		 *
		 * @brief	Swap buffers
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void SwapBuffers() = 0;

		/**
		 * @fn	static Scope<GraphicsContext> GraphicsContext::Create(void* window);
		 *
		 * @brief	Creates a new Scope&lt;GraphicsContext&gt;
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	window	If non-null, the window.
		 *
		 * @returns	A Scope&lt;GraphicsContext&gt;
		 */

		static Scope<GraphicsContext> Create(void* window);
	};

}