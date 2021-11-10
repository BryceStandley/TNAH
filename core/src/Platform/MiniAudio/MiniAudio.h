#pragma once
#include "TNAH/Audio/AudioAPI.h"

namespace tnah {
//TODO Actually set up mini audio

    class MiniAudio : public AudioAPI
    {
    public:
	    bool SetListener(TransformComponent &transforms) const override;


	    bool AddAudioSource(AudioSourceComponent &sound) override;


	    bool UpdateAudioSource(AudioSourceComponent &sound) override;


	    void OnUpdate() override;


	    void UpdateSound(AudioSourceComponent& sound, TransformComponent &transforms) override;


	    bool Active() const override;


	    void Clear() override;
    };
}