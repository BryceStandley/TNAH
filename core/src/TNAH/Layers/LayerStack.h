#pragma once

#include "TNAH/Core/Core.h"
#include "Layer.h"

#include <vector>

namespace tnah {

	/**
	 * @class	LayerStack
	 *
	 * @brief	The LayerStack class is used to store multiple layers, while allowing for them to be added and removed 
	 *
	 * @author	Dylan Blereau
	 * @date	10/09/2021
	 */

	class LayerStack
	{
	public:

		/**
		 * @fn	LayerStack::LayerStack() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		LayerStack() = default;

		/**
		 * @fn	LayerStack::~LayerStack();
		 *
		 * @brief	Destructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		~LayerStack();

		/**
		 * @fn	void LayerStack::PushLayer(Layer* layer);
		 *
		 * @brief	Pushes a layer 
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param [in,out]	layer	If non-null, the layer.
		 */

		void PushLayer(Layer* layer);

		/**
		 * @fn	void LayerStack::PushOverlay(Layer* overlay);
		 *
		 * @brief	Pushes an overlay
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param [in,out]	overlay	If non-null, the overlay.
		 */

		void PushOverlay(Layer* overlay);

		/**
		 * @fn	void LayerStack::PopLayer(Layer* layer);
		 *
		 * @brief	Pops(Removes) the layer described by layer
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param [in,out]	layer	If non-null, the layer.
		 */

		void PopLayer(Layer* layer);

		/**
		 * @fn	void LayerStack::PopOverlay(Layer* overlay);
		 *
		 * @brief	Pops(Remove) the overlay described by overlay
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param [in,out]	overlay	If non-null, the overlay.
		 */

		void PopOverlay(Layer* overlay);

		/**
		 * @fn	std::vector<Layer*>::iterator LayerStack::begin()
		 *
		 * @brief	Gets the beginning of the iterator
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else a std::vector&lt;Layer*&gt;::iterator.
		 */

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

		/**
		 * @fn	std::vector<Layer*>::iterator LayerStack::end()
		 *
		 * @brief	Gets the end of the iterator
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else a std::vector&lt;Layer*&gt;::iterator.
		 */

		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

		/**
		 * @fn	std::vector<Layer*>::reverse_iterator LayerStack::rbegin()
		 *
		 * @brief	Gets the rbegin of the reverse iterator
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else a std::vector&lt;Layer*&gt;::reverse_iterator.
		 */

		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }

		/**
		 * @fn	std::vector<Layer*>::reverse_iterator LayerStack::rend()
		 *
		 * @brief	Gets the rend of the reverse iterator
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else a std::vector&lt;Layer*&gt;::reverse_iterator.
		 */

		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		/**
		 * @fn	std::vector<Layer*>::const_iterator LayerStack::begin() const
		 *
		 * @brief	Gets the begin of the iterator
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else a std::vector&lt;Layer*&gt;::const_iterator.
		 */

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }

		/**
		 * @fn	std::vector<Layer*>::const_iterator LayerStack::end() const
		 *
		 * @brief	Gets the end of the iterator
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else a std::vector&lt;Layer*&gt;::const_iterator.
		 */

		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }

		/**
		 * @fn	std::vector<Layer*>::const_reverse_iterator LayerStack::rbegin() const
		 *
		 * @brief	Gets the rbegin of the reverse iterator
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else a std::vector&lt;Layer*&gt;::const_reverse_iterator.
		 */

		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }

		/**
		 * @fn	std::vector<Layer*>::const_reverse_iterator LayerStack::rend() const
		 *
		 * @brief	Gets the rend of the reverse iterator
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else a std::vector&lt;Layer*&gt;::const_reverse_iterator.
		 */

		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};


}