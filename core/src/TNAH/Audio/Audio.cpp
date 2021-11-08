#include "tnahpch.h"
#include "Audio.h"

namespace tnah
{
    AudioAPI * Audio::m_AudioEngine = new Klang();

    void Audio::Shutdown()
    {
        printf("This is called");
        delete m_AudioEngine;
        m_AudioEngine = nullptr;
    }

    bool Audio::Init()
    {
        if(m_AudioEngine)
            return true;
        else
            return false;
    }
    
    bool Audio::SetListener(TransformComponent &transform)
    {
        return m_AudioEngine->SetListener(transform);
    }
    bool Audio::AddAudioSource(AudioSourceComponent &sound)
    {
        return m_AudioEngine->AddAudioSource(sound);
    }
    bool Audio::UpdateAudioSource(AudioSourceComponent &sound)
    {
        return m_AudioEngine->UpdateAudioSource(sound);
    }
 
    void Audio::OnUpdate()
    {
        m_AudioEngine->OnUpdate();
    }
    
    void Audio::UpdateSound(AudioSourceComponent& sound, TransformComponent &transform)
    {
        m_AudioEngine->UpdateSound(sound, transform);
    }
    
    bool Audio::Active()
    {
        return m_AudioEngine->Active();
    }

    void Audio::Clear()
    {
        m_AudioEngine->Clear();
    }

}