#pragma once

#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>
#include <entt.hpp>
#pragma warning(pop)

namespace tnah {
	namespace Physics {
		
		/**
		* @class	PhysicsEvents
		*
		* @brief	The physics event class that inherits from the react physics 3d eventListener class
		*
		* @author	Christopher Logan
		* @date	11/09/2021
		*/

		class PhysicsEvents : public rp3d::EventListener
		{
		public:
		
			/**
			* @fn	void PhysicsEvents::onContact(const CallbackData& callbackData) override;
			*
			* @brief	Event callback overriding React. Naming must be the same as React.
			*
			* @author	Christopher Logan
			* @date	11/09/2021
			*
			* @param 	callbackData	Information describing the callback.
			*/

			void onContact(const CallbackData& callbackData) override;

			/**
			* @fn	void PhysicsEvents::onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) override;
			*
			* @brief	Event callback overriding React. Naming must be the same as React.
			*
			* @author	Christopher Logan
			* @date	11/09/2021
			*
			* @param 	callbackData	Information describing the callback.
			*/

			void onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) override;
		};
	}
}
