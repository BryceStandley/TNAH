#pragma once
#include <glm/glm.hpp>

namespace tnah {

	/**
	 * @class	Camera
	 *
	 * @brief	A camera class responsible for setting up the application camera 
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class Camera
	{
	public:

		/**
		 * @fn	Camera::Camera() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		Camera() = default;

		/**
		 * @fn	Camera::Camera(const glm::mat4& projectionMatrix);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	projectionMatrix	The projection matrix.
		 */

		Camera(const glm::mat4& projectionMatrix);

		/**
		 * @fn	virtual Camera::~Camera() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~Camera() = default;

		/**
		 * @fn	const glm::mat4& Camera::GetProjectionMatrix() const
		 *
		 * @brief	Gets projection matrix
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The projection matrix.
		 */

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

		/**
		 * @fn	void Camera::SetProjectionMatrix(const glm::mat4& projectionMatrix)
		 *
		 * @brief	Sets projection matrix
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	projectionMatrix	The projection matrix.
		 */

		void SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }

		/**
		 * @fn	float Camera::GetExposure() const
		 *
		 * @brief	Gets the exposure
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The exposure.
		 */

		float GetExposure() const { return m_Exposure; }

		/**
		 * @fn	float& Camera::GetExposure()
		 *
		 * @brief	Gets the exposure
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The exposure.
		 */

		float& GetExposure() { return m_Exposure; }

		/**
		 * @fn	const glm::mat4& Camera::GetViewProjectionMatrix() const
		 *
		 * @brief	Gets view projection matrix
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The view projection matrix.
		 */

		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjection; }

		/** @brief	Pointer to the main camera */
		static Camera* Main;
	protected:

		/**
		 * @fn	static void Camera::SetMainCamera(Camera& other);
		 *
		 * @brief	Sets main camera
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	other	The other.
		 */

		static void SetMainCamera(Camera& other);


		/** @brief	The main camera */
		static Camera* MainCamera;

		/** @brief	The projection matrix */
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

		/** @brief	The exposure */
		float m_Exposure = 0.8f;

		/** @brief	The invert transform view matrix */
		glm::mat4 m_InvertTransformViewMatrix = glm::mat4(1.0f);

		/** @brief	The view matrix */
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

		/** @brief	The view projection matrix */
		glm::mat4 m_ViewProjection = m_ProjectionMatrix * m_ViewMatrix;

		friend class Scene;
	};

	



}
