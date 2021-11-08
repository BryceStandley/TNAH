#pragma once

#include <chrono>

namespace tnah {

	/**
	 * @class	Timer
	 *
	 * @brief	A timer class used to manage aspects of time
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 */

	class Timer
	{
	public:

		/**
		 * @fn	Timer::Timer()
		 *
		 * @brief	Default constructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		Timer()
		{
			Reset();
		}

		/**
		 * @fn	inline void Timer::Reset()
		 *
		 * @brief	Resets this object
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		inline void Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		/**
		 * @fn	inline float Timer::Elapsed()
		 *
		 * @brief	Gets the elapsed time
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	A float.
		 */

		inline float Elapsed()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
		}

		/**
		 * @fn	inline float Timer::ElapsedMillis()
		 *
		 * @brief	Returns Elapsed milliseconds
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	A float.
		 */

		inline float ElapsedMillis()
		{
			return Elapsed() * 1000.0f;
		}

	private:

		/** @brief	The start */
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};

}