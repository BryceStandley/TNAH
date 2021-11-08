#pragma once
#include "TNAH/Audio/AudioAPI.h"
#pragma warning(push, 0)
#include <IrrKlang/irrKlang.h>
#include <vector>
#include <unordered_map>
#include <string>
#pragma warning(pop)

typedef std::pair<u_int, irrklang::ISoundSource*> AudioSourcePair;
typedef std::unordered_map<std::string, irrklang::ISoundSource*> AudioSources;
typedef std::vector<irrklang::ISound*> AudioPlaying;
typedef std::vector<std::string> AudioKeys;

namespace  tnah
{
        /**
         * @class	Klang
         *
         * @brief	A derived IrrKlang class that inherits from the base class AudioAPI. Responsible for the in-game audio.
         *
         * @author	Christopher Logan
         * @date	6/09/2021
         */

    class Klang final : public AudioAPI
    {
    public:

            /**
             * @fn	Klang();
             *
             * @brief	Default constructor
             *
             * @author	Christopher Logan
             * @date	6/09/2021
             */

        Klang();

            /**
             * @fn	~Klang();
             *
             * @brief	Destructor
             *
             * @author	Christopher Logan
             * @date	6/09/2021
             */

        virtual ~Klang();

            /**
             * @fn	bool SetListener(TransformComponent &transform) const override;
             *
             * @brief	Sets a audio listeners position to the transform
             *
             * @author	Christopher Logan
             * @date	6/09/2021
             *
             * @param [in,out]	transform	The transform component.
             *
             * @returns	True if it succeeds, false if it fails.
             */

        bool SetListener(TransformComponent &transform) const override;

            /**
             * @fn	bool AddAudioSource(AudioSourceComponent&sound) override;
             *
             * @brief	Adds an audio source to the audio source unordered_map, returns false if it doesn't load and returns true if loads in or is already loaded in.
             *
             * @author	Christopher Logan
             * @date	6/09/2021
             *
             * @param [in,out]	sound	The sound component.
             *
             * @returns	True if it succeeds, false if it fails.
             */

        bool AddAudioSource(AudioSourceComponent&sound) override;

            /**
             * @fn	bool UpdateAudioSource(AudioSourceComponent&sound) override;
             *
             * @brief	Updates the audio source file
             *
             * @author	Christopher Logan
             * @date	6/09/2021
             *
             * @param [in,out]	sound	The sound component.
             *
             * @returns	True if it succeeds, false if it fails.
             */

        bool UpdateAudioSource(AudioSourceComponent&sound) override;

            /**
             * @fn	void OnUpdate() override;
             *
             * @brief	Updates the audio class
             *
             * @author	Christopher Logan
             * @date	7/09/2021
             */

        void OnUpdate() override;

            /**
             * @fn	void UpdateSound(AudioSourceComponent& sound, TransformComponent &transform) override;
             *
             * @brief	Updates the sound
             *
             * @author	Christopher Logan
             * @date	7/09/2021
             *
             * @param [in,out]	sound	 	The sound component.
             * @param [in,out]	transform	The transform component.
             */

        void UpdateSound(AudioSourceComponent& sound, TransformComponent &transform) override;

            /**
             * @fn	bool Active() const override
             *
             * @brief	Checks if sound engine is active
             *
             * @author	Christopher Logan
             * @date	7/09/2021
             *
             * @returns	True if it succeeds, false if it fails.
             */

        bool Active() const override {return m_Engine;}

            /**
             * @fn	void Clear() override;
             *
             * @brief	Clears this object to its blank/initial state
             *
             * @author	Christopher Logan
             * @date	6/09/2021
             */

        void Clear() override;
        
    private:

            /**
             * @fn	bool PlayAudioSource(AudioSourceComponent& sound, TransformComponent &transform);
             *
             * @brief	Plays the audio source if returned bool is true, doesn't if false
             *
             * @author	Christopher Logan
             * @date	6/09/2021
             *
             * @param [in,out]	sound	 	The sound component.
             * @param [in,out]	transform	The transform component.
             *
             * @returns	True if it succeeds, false if it fails.
             */

        bool PlayAudioSource(AudioSourceComponent& sound, TransformComponent &transform);


            /** @brief	Represents the audio source */
        AudioSources m_Source;


            /** @brief	Represents the playing of the audio source */
        AudioPlaying m_Playing;


            /** @brief	The audio keys */
        AudioKeys m_Keys;

            /** @brief	A pointer to the sound engine */
        irrklang::ISoundEngine* m_Engine;
    };    
};

