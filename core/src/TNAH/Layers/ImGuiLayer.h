#pragma once
#include "Layer.h"
#include "TNAH/Events/ApplicationEvent.h"
#include "TNAH/Events/KeyEvent.h"
#include "TNAH/Events/MouseEvent.h"

namespace tnah {

	class TNAH_API ImGuiLayer : public Layer
	{
	public:

		/**
		 * @fn	ImGuiLayer::ImGuiLayer();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		ImGuiLayer();

		/**
		 * @fn	ImGuiLayer::~ImGuiLayer();
		 *
		 * @brief	Destructor
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		~ImGuiLayer();

		/**
		 * @fn	virtual void ImGuiLayer::OnAttach() override;
		 *
		 * @brief	Executes on attach of the layer
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		virtual void OnAttach() override;

		/**
		 * @fn	virtual void ImGuiLayer::OnDetach() override;
		 *
		 * @brief	Executes on imgui layer detach
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		virtual void OnDetach() override;

		/**
		 * @fn	void ImGuiLayer::Begin();
		 *
		 * @brief	Begins the imgui layer
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		void Begin();

		/**
		 * @fn	void ImGuiLayer::End();
		 *
		 * @brief	Ends the layer
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		void End();

		/**
		 * @fn	virtual void ImGuiLayer::OnEvent(Event& event) override;
		 *
		 * @brief	Executes on event
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 *
		 * @param [in,out]	event	The event.
		 */

		virtual void OnEvent(Event& event) override;

		/**
		 * @fn	virtual void ImGuiLayer::OnImGuiRender() override;
		 *
		 * @brief	Executes on imgui render
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		virtual void OnImGuiRender() override;

		/**
		 * @fn	void ImGuiLayer::SetDarkThemeColors();
		 *
		 * @brief	Sets dark theme colors
		 *
		 * @author	Dylan Blereau
		 * @date	10/09/2021
		 */

		void SetDarkThemeColors();

	private:

		/** @brief	True to block events */
		bool m_BlockEvents = true;

		/** @brief	The time */
		float m_Time = 0.0f;

	};



}
