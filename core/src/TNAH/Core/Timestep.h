#pragma once

namespace tnah {

	/**
	 * @class	Timestep
	 *
	 * @brief	A timestep class that handles the time
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	class Timestep
	{
	public:

		/**
		 * @fn	Timestep::Timestep(float time = 0.0f)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	time	(Optional) The time.
		 */

		Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}

		/**
		 * @fn	operator Timestep::float() const
		 *
		 * @brief	Cast that converts the given  to a float
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The result of the operation.
		 */

		operator float() const { return m_Time; }

		/**
		 * @fn	float Timestep::GetSeconds() const
		 *
		 * @brief	Gets the seconds
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The seconds.
		 */

		float GetSeconds() const { return m_Time; }

		/**
		 * @fn	float Timestep::GetMilliseconds() const
		 *
		 * @brief	Gets the milliseconds of time
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The milliseconds.
		 */

		float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};

}