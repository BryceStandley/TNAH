#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Scene/Components/AudioComponents.h"
#include "Platform/IrrKlang/Klang.h"

namespace tnah
{
    /**
     * @class	Audio
     *
     * @brief	An audio class responisble for handling the audio engine
     *
     * @author	Christopher Logan
     * @date	7/09/2021
     */

    class Audio
    {
    public:

        /**
         * @fn	static bool Audio::Init();
         *
         * @brief	Initializes this object
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Init();

        /**
         * @fn	static void Audio::Shutdown();
         *
         * @brief	Shuts down this object and frees any resources it is using
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         */

        static void Shutdown();

        /**
         * @fn	static bool Audio::SetListener(TransformComponent &transforms);
         *
         * @brief	Sets a listener to a given transform component
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         *
         * @param [in,out]	transforms	The transforms.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool SetListener(TransformComponent &transforms);

        /**
         * @fn	static bool Audio::AddAudioSource(AudioSourceComponent &sound);
         *
         * @brief	Adds an audio source
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         *
         * @param [in,out]	sound	The sound.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool AddAudioSource(AudioSourceComponent &sound);

        /**
         * @fn	static bool Audio::UpdateAudioSource(AudioSourceComponent &sound);
         *
         * @brief	Updates the audio source described by sound
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         *
         * @param [in,out]	sound	The sound.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool UpdateAudioSource(AudioSourceComponent &sound);

        /**
         * @fn	static void Audio::OnUpdate();
         *
         * @brief	Executes the 'update' action
         *

         * @author	Christopher Logan
         * @date	7/09/2021
         */

        static void OnUpdate();

        /**
         * @fn	static void Audio::UpdateSound(AudioSourceComponent& sound, TransformComponent &transforms);
         *
         * @brief	Updates the sound
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         *
         * @param [in,out]	sound	  	The sound.
         * @param [in,out]	transforms	The transforms.
         */

        static void UpdateSound(AudioSourceComponent& sound, TransformComponent &transforms);

        /**
         * @fn	static bool Audio::Active();
         *
         * @brief	Activatea this object
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         *
         * @returns	True if it succeeds, false if it fails.
         */

        static bool Active();

        /**
         * @fn	static void Audio::Clear();
         *
         * @brief	Clears this object to its blank/initial state
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         */

        static void Clear();
    private:

        /** @brief	The audio engine */
        static AudioAPI * m_AudioEngine;
    };
};