#pragma 
#include "TNAH/Scene/Components/AudioComponents.h"
#include "TNAH/Scene/Components/Components.h"
namespace tnah
{
    /**
     * @class	AudioAPI
     *
     * @brief	An abstract audioAPI class that contains virtual functions that the audio class will inherit
     *
     * @author	Christopher Logan
     * @date	7/09/2021
     */

    class AudioAPI
    {
    public:

        /**
         * @fn	virtual bool AudioAPI::SetListener(TransformComponent &transforms) const = 0;
         *
         * @brief	Sets a listener
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         *
         * @param [in,out]	transforms	The transform.
         *
         * @returns	True if it succeeds, false if it fails.
         */

        virtual bool SetListener(TransformComponent &transforms) const = 0;

        /**
         * @fn	virtual bool AudioAPI::AddAudioSource(AudioSourceComponent &sound) = 0;
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

        virtual bool AddAudioSource(AudioSourceComponent &sound) = 0;

        /**
         * @fn	virtual bool AudioAPI::UpdateAudioSource(AudioSourceComponent &sound) = 0;
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

        virtual bool UpdateAudioSource(AudioSourceComponent &sound) = 0;

        /**
         * @fn	virtual void AudioAPI::OnUpdate() = 0;
         *
         * @brief	Executes the action on update
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         */

        virtual void OnUpdate() = 0;

        /**
         * @fn	virtual void AudioAPI::UpdateSound(AudioSourceComponent& sound, TransformComponent &transforms) = 0;
         *
         * @brief	Updates the sound
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         *
         * @param [in,out]	sound	  	The sound.
         * @param [in,out]	transforms	The transforms.
         */

        virtual void UpdateSound(AudioSourceComponent& sound, TransformComponent &transforms) = 0;

        /**
         * @fn	virtual bool AudioAPI::Active() const = 0;
         *
         * @brief	Actives this object
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         *
         * @returns	True if it succeeds, false if it fails.
         */

        virtual bool Active() const = 0;

        /**
         * @fn	virtual void AudioAPI::Clear() = 0;
         *
         * @brief	Clears this object to its blank/initial state
         *
         * @author	Christopher Logan
         * @date	7/09/2021
         */

        virtual void Clear() = 0;
    };
}

