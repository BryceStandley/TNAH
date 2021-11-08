#include "tnahpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "TNAH/Scene/Components/Components.h"

namespace tnah {

	void SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveFOV = glm::radians(verticalFOV);
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		switch (m_ProjectionType)
		{
		case ProjectionType::Perspective:
			m_ProjectionMatrix = glm::perspective(m_PerspectiveFOV, (float)width / (float)height, m_PerspectiveNear, m_PerspectiveFar);
			m_ViewportWidth = width;
			m_ViewportHeight = height;
			
			break;
		case ProjectionType::Orthographic:
			float aspect = (float)width / (float)height;
			m_ViewportWidth = width;
			m_ViewportHeight = height;
			float w = m_OrthographicSize * aspect;
			float h = m_OrthographicSize;
			m_ProjectionMatrix = glm::ortho(-w * 0.5f, w * 0.5f, -h * 0.5f, h * 0.5f);
			m_ViewportWidth = (uint32_t)w;
			m_ViewportHeight = (uint32_t)h;
			break;
		}
	}



	void SceneCamera::OnUpdate(TransformComponent& transform)
	{
		OnCameraChange(transform);
	}

	void SceneCamera::OnCameraChange(TransformComponent& transform)
	{
		m_ProjectionMatrix = glm::perspective(m_PerspectiveFOV, (float)m_ViewportWidth / (float)m_ViewportHeight, m_PerspectiveNear, m_PerspectiveFar);
		glm::vec3 r = transform.Right;
		m_InvertTransformViewMatrix = glm::inverse(transform.GetTransform());
		m_ViewMatrix = glm::lookAt(transform.Position, transform.Position + transform.Forward, transform.Up);
		m_ViewProjection = m_ProjectionMatrix * m_ViewMatrix;
	}

	glm::quat SceneCamera::GetOrientation(TransformComponent& transform)
	{
		return glm::quat(glm::vec3(-transform.Rotation.x, -transform.Rotation.y, 0));
	}
}
