#include "tnahpch.h"
#include "PhysicsEvents.h"

namespace tnah {
	namespace Physics {
		
		void PhysicsEvents::onContact(const CollisionCallback::CallbackData &callbackData)
		{
			for(unsigned int i = 0; i < callbackData.getNbContactPairs(); i++)
			{
				PhysicsEngine::GetManager()->GetCollisionDetectionEngine()->RegisterCollision(PhysicsCollision(callbackData.getContactPair(i)));
			}
		}

		void PhysicsEvents::onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData)
		{

		}
	}
}
