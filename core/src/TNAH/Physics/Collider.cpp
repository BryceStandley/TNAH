#include "tnahpch.h"
#include "Collider.h"
#include "Rigidbody.h"

namespace tnah::Physics {


	Collider::Collider()
	{}

	Collider::Collider(rp3d::CollisionShape* collider, Type type)
		:m_Collider(collider), m_Type(type)
	{
		
		switch (m_Type)
		{
			case Type::Box:
				InitializeBox();
				break;
			case Type::Sphere:
				InitializeSphere();
				break;
			case Type::Capsule:
				InitializeCapsule();
				break;
			default:
				break;
		}
	}

	Ref<Collider> Collider::Create(rp3d::CollisionShape* collider, Type type)
	{
		return Ref<Collider>::Create(collider, type);
	}

	void Collider::InitializeBox()
	{
		rp3d::BoxShape* box = static_cast<rp3d::BoxShape*>(m_Collider);

		const auto fullExtents = Math::FromRp3dVec3(box->getHalfExtents() * 2.0f);

		//Volume of a cube/box: V = length * width * height
		m_Volume =  fullExtents.x * fullExtents.y * fullExtents.z;
		m_Mass.SetMass(m_Density * m_Volume);

		//Generate a inertia tensor for the shape
		float factor = 1.0f / 3.0f * m_Mass.Mass;
		//Todo Check if we really should be using half or full extents
		auto x = box->getHalfExtents().x * box->getHalfExtents().x;
		auto y = box->getHalfExtents().y * box->getHalfExtents().y;
		auto z = box->getHalfExtents().z * box->getHalfExtents().z;
		auto tensor = glm::vec3(factor * (y + z), factor * (x + z), factor * (x + y));
		m_InertiaTensor.LocalInertiaTensor = tensor;
		
	}

	void Collider::InitializeSphere()
	{
		rp3d::SphereShape* sphere = static_cast<rp3d::SphereShape*>(m_Collider);

		//Volume of a Sphere: V = (4/3)πr3
		m_Volume = (4/3) * glm::pi<float>() * (float)glm::pow(sphere->getRadius(), 3);
		m_Mass.SetMass(m_Density * m_Volume);

		//Generate a inertia tensor for the shape
		float diag = 0.4f * m_Mass.Mass * (float)glm::pow(sphere->getRadius(),2);
		auto tensor = glm::vec3(diag, diag, diag);
		m_InertiaTensor.LocalInertiaTensor = tensor;
		
	}

	void Collider::InitializeCapsule()
	{
		rp3d::CapsuleShape* capsule = static_cast<rp3d::CapsuleShape*>(m_Collider);
			
		// Volume of a Capsule: V = πr2((4/3)r + a)
		m_Volume = glm::pi<float>() * (float)glm::pow(capsule->getRadius(), 2) * ((float)(4.0f/3.0f) * glm::pi<float>() + (float)capsule->getHeight());
		m_Mass.SetMass(m_Density * m_Volume);

		//Generate a inertia tensor for the shape
		// The inertia tensor formula for a capsule can be found in : Game Engine Gems, Volume 1
		float mass = m_Mass.Mass;
		float height = capsule->getHeight();
		float radius = capsule->getRadius();
		float radiusSqr = (float)glm::pow(capsule->getRadius(), 2);
		float heightSqr = (float)glm::pow(height, 2);
		float radiusDoubleSqr = radiusSqr + radiusSqr;
		float fac1 = 2.0f * radius / (4.0f * radius + 3.0f * height);
		float fac2 = 3.0f * height / (4.0f * radius + 3.0f * height);
		float sum1 = 0.4f * radiusDoubleSqr;
		float sum2 = 0.75f * height * radius + 0.5f * heightSqr;
		float sum3 = 0.25f * radiusSqr + (1.0f / 12.0f) * heightSqr;
		float Ixxzz = fac1 * mass * (sum1 + sum2) + fac2 * mass * sum3;
		float Iyy = fac1 * mass * sum1 + fac2 * mass * 0.25f * radiusDoubleSqr;
		auto tensor = glm::vec3(Ixxzz, Iyy, Ixxzz);
		m_InertiaTensor.LocalInertiaTensor = tensor;
	}

	glm::vec3 Collider::GetLocalColliderInertiaTensor()
	{
		return m_InertiaTensor.LocalInertiaTensor;
	}
}
