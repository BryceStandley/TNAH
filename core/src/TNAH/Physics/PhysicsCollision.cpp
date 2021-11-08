#include "tnahpch.h"
#include "PhysicsCollision.h"

#include "TNAH/Scene/GameObject.h"

namespace tnah {
	namespace Physics {


		PhysicsCollision::PhysicsCollision()
		{}

		PhysicsCollision::PhysicsCollision(rp3d::CollisionCallback::ContactPair contactPair)
		{
			m_TotalContactPoints = contactPair.getNbContactPoints();
			for(uint32_t i = 0; i < m_TotalContactPoints; i++)
			{
				CollisionData col;
			
				auto point = contactPair.getContactPoint(i);
				col.m_Body1ContactPosition = Math::FromRp3dVec3(contactPair.getCollider1()->getLocalToWorldTransform() * point.getLocalPointOnCollider1());
				col.m_Body2ContactPosition =  Math::FromRp3dVec3(contactPair.getCollider2()->getLocalToWorldTransform() * point.getLocalPointOnCollider2());
				col.m_ContactNormal = Math::FromRp3dVec3(point.getWorldNormal());
				col.m_Body1GameObject = static_cast<GameObject*>(contactPair.getBody1()->getUserData());
				col.m_Body2GameObject = static_cast<GameObject*>(contactPair.getBody2()->getUserData());
				col.m_Body1RigidBody = col.m_Body1GameObject->GetComponent<RigidBodyComponent>().Body;
				col.m_Body2RigidBody = col.m_Body2GameObject->GetComponent<RigidBodyComponent>().Body;
				col.m_PenetrationDepth = static_cast<float>(point.getPenetrationDepth());
				m_CollisionData.push(col);
				
			}
		}
	}
}