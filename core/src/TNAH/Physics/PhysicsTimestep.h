#pragma once

namespace tnah
{
    /**
     * @class	PhysicsTimestep
     *
     * @brief	The physics timestep class is designed to make sure the frame rate of the physics is 60 frames per second
     *
     * @author	Christopher Logan
     * @date	11/09/2021
     */

    class PhysicsTimestep
    {
    public:
        PhysicsTimestep() = default;
        /**
         * @fn	PhysicsTimestep::PhysicsTimestep(float framerate)
         *
         * @brief	Constructor
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
         * @param 	framerate	The framerate.
         */

        PhysicsTimestep(float framerate)
            : m_TotalTime(0), m_SimSpeed(1.0f/framerate), m_Accumulator(0)
        {}

        /**
         * @fn	inline void PhysicsTimestep::AddFrameTime(const float frameTime)
         *
         * @brief	Adds a frame time
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
         * @param 	frameTime	The frame time.
         */

        inline void AddFrameTime(const float frameTime) { m_Accumulator += frameTime; }

        /**
         * @fn	inline bool PhysicsTimestep::FixedUpdateCheck() const
         *
         * @brief	Determines if we can fixed update check
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
         * @returns	True if it succeeds, false if it fails.
         */

        inline bool FixedUpdateCheck() const { return m_Accumulator >= m_SimSpeed; }

        /**
         * @fn	inline void PhysicsTimestep::Update()
         *
         * @brief	Updates this object
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         */

        inline void Update() { m_TotalTime += m_SimSpeed; m_Accumulator -= m_SimSpeed; }

        /**
         * @fn	float PhysicsTimestep::GetAplha() const
         *
         * @brief	Gets the aplha
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
        * @returns	The aplha.
         */

        float GetAplha() const { return m_Accumulator / m_SimSpeed; }

        /**
         * @fn	void PhysicsTimestep::SetAccumulator(const float a)
         *
         * @brief	Sets an accumulator
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
         * @param 	a	A float to process.
         */

        void SetAccumulator(const float a) { m_Accumulator = a; }

        /**
         * @fn	float PhysicsTimestep::GetAccumulator() const
         *
         * @brief	Gets the accumulator
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
         * @returns	The accumulator.
         */

        float GetAccumulator() const { return m_Accumulator; }

        /**
         * @fn	void PhysicsTimestep::SetTotalTime(const float time)
         *
         * @brief	Sets total time
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
         * @param 	time	The time.
         */

        void SetTotalTime(const float time) { m_TotalTime = time; }

        /**
         * @fn	float PhysicsTimestep::GetTotalTime() const
         *
         * @brief	Gets total time
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
         * @returns	The total time.
         */

        float GetTotalTime() const { return m_TotalTime; }

        /**
         * @fn	void PhysicsTimestep::SetSimulationSpeed(const float speed)
         *
         * @brief	Sets simulation speed
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
         * @param 	speed	The speed.
         */

        void SetSimulationSpeed(const float speed) { m_SimSpeed = speed; }

        /**
         * @fn	void PhysicsTimestep::SetSimulationFrameRate(float frames)
         *
         * @brief	Sets simulation frame rate
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
         * @param 	frames	The frames.
         */

        void SetSimulationFrameRate(float frames) { m_SimSpeed = 1.0f / frames; }

        /**
         * @fn	float PhysicsTimestep::GetSimulationSpeed() const
         *
         * @brief	Gets simulation speed
         *
         * @author	Christopher Logan
         * @date	11/09/2021
         *
         * @returns	The simulation speed.
         */

        float GetSimulationSpeed() const { return m_SimSpeed; }

    private:

        /** @brief	The total time */
        float m_TotalTime;

        /** @brief	The simulation speed */
        float m_SimSpeed;

        /** @brief	The accumulator */
        float m_Accumulator;
    };
}

