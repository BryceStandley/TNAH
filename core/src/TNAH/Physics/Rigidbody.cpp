#include "tnahpch.h"
#include "Rigidbody.h"

namespace tnah::Physics {
	
	RigidBody::RigidBody()
	{
		m_BodyType = BodyType::Dynamic;
	}

	RigidBody::RigidBody(TransformComponent& transform, BodyMass mass, BodyType type)
		:m_BodyType(type), m_BodyMass(mass)
	{
		m_Position = transform.Position;
		m_Orientation = glm::quat(transform.QuatRotation);
	}

	Ref<RigidBody> RigidBody::Create(TransformComponent& transform, BodyMass mass, BodyType type)
	{
		return Ref<RigidBody>::Create(transform, mass, type);
	}

	void RigidBody::OnUpdate(TransformComponent& transform)
	{
		m_Position = transform.Position;
		m_Orientation = glm::normalize(m_Orientation + transform.QuatRotation);
	}

	void RigidBody::AddForce(const glm::vec3& force)
	{
		if(m_BodyType != BodyType::Static || m_BodyType != BodyType::Kinematic)
			m_Force += force;
	}

	void RigidBody::AddTorque(const glm::vec3& torque)
	{
		if(m_BodyType != BodyType::Static || m_BodyType != BodyType::Kinematic)
			m_Torque += torque;
	}

	void RigidBody::AddCollider(Ref<Collider> collider)	
	{
		m_Colliders[m_TotalColliders] = collider;
		m_TotalColliders++;
		if(m_BodyType == BodyType::Dynamic)
		{
			UpdateBodyProperties();
		}
		else
		{
			m_BodyMass.SetMass(std::numeric_limits<float>::max());
		}
	
	}

	void RigidBody::UpdateBodyProperties()
	{
		//Get and update the Centre of Mass for the body. Both local and world
		const auto oldWorldCOM = m_BodyMass.WorldCentreOfMass;
		const auto localCOM = CalculateCentreOfMass();
		const glm::vec3 worldCOM = (m_Orientation * localCOM) + m_Position;
		m_BodyMass.WorldCentreOfMass = worldCOM;

		if(m_BodyType == BodyType::Dynamic)
		{
			m_LinearVelocity.Velocity += glm::cross(m_AngularVelocity.Velocity, worldCOM - oldWorldCOM);
		}
		
		CalculateLocalInertiaTensor();
	}

	void RigidBody::RecalculateWorldInertiaTensor()
	{
		glm::mat3 rot = glm::mat3_cast(m_Orientation);
		m_InertiaTensor.WorldInverseInertiaTensor[0][0] = rot[0][0] * m_InertiaTensor.LocalInverseInertiaTensor.x;
		m_InertiaTensor.WorldInverseInertiaTensor[0][1] = rot[1][0] * m_InertiaTensor.LocalInverseInertiaTensor.x;
		m_InertiaTensor.WorldInverseInertiaTensor[0][2] = rot[2][0] * m_InertiaTensor.LocalInverseInertiaTensor.x;
		
		m_InertiaTensor.WorldInverseInertiaTensor[1][0] = rot[0][1] * m_InertiaTensor.LocalInverseInertiaTensor.y;
		m_InertiaTensor.WorldInverseInertiaTensor[1][1] = rot[1][1] * m_InertiaTensor.LocalInverseInertiaTensor.y;
		m_InertiaTensor.WorldInverseInertiaTensor[1][2] = rot[2][1] * m_InertiaTensor.LocalInverseInertiaTensor.y;
		
		m_InertiaTensor.WorldInverseInertiaTensor[2][0] = rot[0][2] * m_InertiaTensor.LocalInverseInertiaTensor.z;
		m_InertiaTensor.WorldInverseInertiaTensor[2][1] = rot[1][2] * m_InertiaTensor.LocalInverseInertiaTensor.z;
		m_InertiaTensor.WorldInverseInertiaTensor[2][2] = rot[2][2] * m_InertiaTensor.LocalInverseInertiaTensor.z;

		m_InertiaTensor.WorldInverseInertiaTensor = rot * m_InertiaTensor.WorldInverseInertiaTensor;
	}

	void RigidBody::ApplyCollisionImpulse(const glm::vec3& linearVelocity, const glm::vec3& angularVelocity)
	{
		m_LinearVelocity.Velocity = linearVelocity;
		m_AngularVelocity.Velocity = angularVelocity;
	}

	void RigidBody::ResetValues()
	{
		m_Force = {0.0f, 0.0f, 0.0f};
		m_Torque = {0.0f, 0.0f, 0.0f};
		m_LinearVelocity = {0.0f, 0.0f, 0.0f};
		m_AngularVelocity = {0.0f, 0.0f, 0.0f};
		m_Position = {0,0,0};
		m_Orientation = {0,0,0,0};
	}

	void RigidBody::Sleep()
	{
		m_IsSleeping = true;

		m_Force = {0.0f, 0.0f, 0.0f};
		m_Torque = {0.0f, 0.0f, 0.0f};
		m_LinearVelocity.Velocity = {0,0,0};
		m_AngularVelocity.Velocity = {0,0,0};
		m_ConstrainedLinearVelocity.Velocity = {0,0,0};
		m_ConstrainedAngularVelocity.Velocity = {0,0,0};

		m_SleepTimeAccumulator = 0.0f;
	}

	glm::vec3 RigidBody::CalculateLocalInertiaTensor()
	{
		auto localCOM = m_BodyMass.LocalCentreOfMass;
		glm::mat3 tempLocalInertiaTensor = glm::mat3(1.0f);

		// calc inertia tensor using colliders
		for(auto c : m_Colliders)
		{
			auto col = c.second;

			glm::vec3 shapeInertiaTensor = col->GetLocalColliderInertiaTensor();
			auto rot = glm::mat3_cast(col->GetColliderOrientation());
			auto rotTranspose = glm::transpose(rot);
			rotTranspose[0] *= shapeInertiaTensor.x;
			rotTranspose[1] *= shapeInertiaTensor.y;
			rotTranspose[2] *= shapeInertiaTensor.z;
			glm::mat3 inertiaTensor = rot * rotTranspose;

			// shift to the rigidbody COM with parallel axis theorem
			glm::vec3 offset = col->GetColliderPosition() - localCOM;
			auto offsetSqr = glm::length2(offset);
			glm::mat3 offsetMatrix = glm::mat3(0.0f);
			offsetMatrix[0][0] = offsetSqr;
			offsetMatrix[1][1] = offsetSqr;
			offsetMatrix[2][2] = offsetSqr;

			offsetMatrix[0] += offset * (-offset.x);
			offsetMatrix[1] += offset * (-offset.y);
			offsetMatrix[2] += offset * (-offset.z);
			offsetMatrix *= col->GetColliderMass().Mass;

			tempLocalInertiaTensor += inertiaTensor + offsetMatrix;
		}

		float x = tempLocalInertiaTensor[0][0];
		float y = tempLocalInertiaTensor[1][1];
		float z = tempLocalInertiaTensor[2][2];
		m_InertiaTensor.SetLocalInertiaTensor({x,y,z});
		return m_InertiaTensor.LocalInertiaTensor;
	}

	glm::vec3 RigidBody::CalculateCentreOfMass()
	{
		float totalMass = 0;
		glm::vec3 localCOM = {0,0,0};
		for(auto col : m_Colliders)
		{
			auto mass =  col.second->GetColliderMass().Mass;
			totalMass += mass;
			localCOM += mass * col.second->GetColliderPosition();
		}

		if(totalMass > 0.0f)
		{
			m_BodyMass.SetMass(totalMass);
		}

		m_BodyMass.LocalCentreOfMass = localCOM;
		return localCOM;

	}
}
