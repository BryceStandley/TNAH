#pragma once
#include <tnahpch.h>
namespace tnah
{
	using MouseCode = uint16_t;

	/**
	 * @namespace tnah::Mouse {}
	 *
	 * @brief Mouse sub-namespace
	 *
	 */
	namespace Mouse
	{
		/**
		 * @enum MouseCode
		 *
		 * @brief	Values that represent mouseCodes
		 */

		enum MouseCode
		{
			// From glfw3.h
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2,
			ButtonAny = Button0 | Button1 | Button2 | Button3 | Button4 | Button5 | Button6 | Button7
		};
	}
}