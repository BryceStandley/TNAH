#include "tnahpch.h"
#include "CollisionDetectionEngine.h"

namespace tnah {
	namespace Physics {


		Ref<CollisionDetectionEngine> CollisionDetectionEngine::Create()
		{
			return Ref<CollisionDetectionEngine>::Create();
		}

		CollisionDetectionEngine::CollisionDetectionEngine()
		{}

		void CollisionDetectionEngine::FixedUpdate(rp3d::PhysicsWorld* physicsWorld, PhysicsTimestep physTime)
		{
			physicsWorld->update(physTime.GetSimulationSpeed());
		}
		
	}
}