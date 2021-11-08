#include <tnahpch.h>
#include "Camera.h"

namespace tnah {

	Camera::Camera(const glm::mat4& projectionMatrix)
		: m_ProjectionMatrix(projectionMatrix)
	{
	}


	Camera* Camera::Main = new Camera();

	void Camera::SetMainCamera(Camera& other)
	{
		Main = &other;
	}

}