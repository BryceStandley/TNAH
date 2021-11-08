#pragma once

#include "TNAH/Renderer/Camera.h"

namespace tnah {
	class TransformComponent;
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	public:
		/**
		 * 
		 * \fn void SetPerspective
		 * 
		 * \brief Sets the perspective of the camera
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param verticalFOV
		 * \param nearClip
		 * \param farClip
		 * 
		 * 
		 */
		void SetPerspective(float verticalFOV, float nearClip = 0.01f, float farClip = 1000.0f);

		/**
		 * 
		 * \fn void SetOrthographic
		 * 
		 * \brief Sets the orthographic settings of the camea
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param size
		 * \param nearClip
		 * \param farClip
		 * 
		 * 
		 */
		void SetOrthographic(float size, float nearClip = -1.0f, float farClip = 1.0f);

		/**
		 * 
		 * \fn void SetViewportSize
		 * 
		 * \brief Sets the viewport size
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param width
		 * \param height
		 * 
		 * 
		 */
		void SetViewportSize(uint32_t width, uint32_t height);

		/**
		 * 
		 * \fn glm::vec2 GetViewportSize
		 * 
		 * \brief Gets the viewport size
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		glm::vec2 GetViewportSize() const {return glm::vec2(m_ViewportWidth, m_ViewportHeight);}

		/**
		 * 
		 * \fn void SetPerspectiveVerticalFOV
		 * 
		 * \brief Sets the perspective field of view
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param verticalFov
		 * 
		 * 
		 */
		void SetPerspectiveVerticalFOV(float verticalFov) { m_PerspectiveFOV = glm::radians(verticalFov); }

		/**
		 * 
		 * \fn float GetPerspectiveVerticalFOV
		 * 
		 * \brief Gets the perspective field of view
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		float GetPerspectiveVerticalFOV() const { return glm::degrees(m_PerspectiveFOV); }

		/**
		 * 
		 * \fn void SetPerspectiveNearClip
		 * 
		 * \brief Sets the perspective near clip plane
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param nearClip
		 * 
		 * 
		 */
		void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; }

		/**
		 * 
		 * \fn float GetPerspectiveNearClip
		 * 
		 * \brief Gets the perspective near clip plane
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }

		/**
		 * 
		 * \fn void SetPerspectiveFarClip
		 * 
		 * \brief Sets the perspective far clip plane
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param farClip
		 * 
		 * 
		 */
		void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; }

		/**
		 * 
		 * \fn float GetPerspectiveFarClip
		 * 
		 * \brief Gets the perspective far clip plane
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }

		/**
		 * 
		 * \fn void SetOrthographicSize
		 * 
		 * \brief Sets the orthographic size
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param size
		 * 
		 * 
		 */
		void SetOrthographicSize(float size) { m_OrthographicSize = size; }

		/**
		 * 
		 * \fn float GetOrthographicSize
		 * 
		 * \brief Gets the orthographic size
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		float GetOrthographicSize() const { return m_OrthographicSize; }

		/**
		 * 
		 * \fn void SetOrthographicNearClip
		 * 
		 * \brief Sets the othographic near clip plane
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param nearClip
		 * 
		 * 
		 */
		void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; }

		/**
		 * 
		 * \fn float GetOrthographicNearClip
		 * 
		 * \brief Sets the othographic near clip plane
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		float GetOrthographicNearClip() const { return m_OrthographicNear; }

		/**
		 * 
		 * \fn void SetOrthographicFarClip
		 * 
		 * \brief Sets the othograohic far clip plane
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param farClip
		 * 
		 * 
		 */
		void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip; }

		/**
		 * 
		 * \fn float GetOrthographicFarClip
		 * 
		 * \brief Gets the othographic far clip plane
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		float GetOrthographicFarClip() const { return m_OrthographicFar; }

		/**
		 * 
		 * \fn void SetProjectionType
		 * 
		 * \brief Sets the projection type of the camera
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param type
		 * 
		 * 
		 */
		void SetProjectionType(ProjectionType type) { m_ProjectionType = type; }

		/**
		 * 
		 * \fn ProjectionType GetProjectionType
		 * 
		 * \brief Gets the projection type of the camera
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		ProjectionType GetProjectionType() const { return m_ProjectionType; }

		/**
		 * 
		 * \fn const glm::mat4 & GetViewMatrix
		 * 
		 * \brief Gets the view matrix of the camera
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		/**
		 * 
		 * \fn const glm::mat4 & GetInvertedTransformViewMatrix
		 * 
		 * \brief Gets the view matrix from the camera derived from its inverted transform component
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		const glm::mat4& GetInvertedTransformViewMatrix() const { return m_InvertTransformViewMatrix; }

		/**
		 * 
		 * \fn void OnUpdate
		 * 
		 * \brief Updates the camera
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param transform
		 * 
		 * 
		 */
		void OnUpdate(TransformComponent& transform);

		/**
		 * 
		 * \fn void OnCameraChange
		 * 
		 * \brief Updates view and projection matrix values when the camera moves or changes
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param transform
		 * 
		 * 
		 */
		void OnCameraChange(TransformComponent& transform);

		/**
		 * 
		 * \fn glm::quat GetOrientation
		 * 
		 * \brief Gets the orientation of the camera
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param transform
		 * 
		 * \return 
		 * 
		 */
		glm::quat GetOrientation(TransformComponent& transform);
	private:
		/**  @brief The projection type of the camera */
		ProjectionType m_ProjectionType = ProjectionType::Perspective;

		/**  @brief The width type of the cameras viewport */
		uint32_t m_ViewportWidth = 1280;
		/**  @brief The height type of the cameras viewport */
		uint32_t m_ViewportHeight = 720;
		
		/**  @brief The field of view type of the camera in radians */
		float m_PerspectiveFOV = glm::radians(60.0f);
		/**  @brief The projection near and far clip planes of the camera */
		float m_PerspectiveNear = 0.1f, m_PerspectiveFar = 10000.0f;

		/**  @brief The orthographic size of the camera */
		float m_OrthographicSize = 10.0f;

		/**  @brief The orthographic near and far clip planes of the camera */
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		friend class EditorUI;
		friend class Serializer;
	};
}