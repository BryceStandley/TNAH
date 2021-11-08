#include "tnahpch.h"
#include "Klang.h"
#include "TNAH/Core/Math.h"

namespace tnah
{
    Klang::Klang() : m_Engine(irrklang::createIrrKlangDevice())
    {
        
    }
    
    Klang::~Klang()
    {
        Klang::Clear();

        //Make sure it is gonzo
        delete m_Engine;
        m_Engine = nullptr;
    }

    bool Klang::SetListener(TransformComponent &transform) const
    {
        if(m_Engine)
        {
            m_Engine->setListenerPosition(Math::ConvertVec3ToVec3df(transform.Position),
                Math::ConvertVec3ToVec3df(transform.Forward), irrklang::vec3df(0, 0, 0),
                Math::ConvertVec3ToVec3df(transform.Up));
            
            return true;
        }
        return false;
    }
    
    bool Klang::AddAudioSource(AudioSourceComponent& sound)
    {
        const std::string key(sound.m_File.RelativeDirectory.c_str());

        //The file is already loaded in
        if(m_Source[key] != nullptr)
            return true;
        
        irrklang::ISoundSource* source(m_Engine ->addSoundSourceFromFile(key.c_str()));
        
        if(source)
        {
            m_Source[key] = source;
            m_Keys.push_back(key);
            source->setDefaultVolume(sound.m_Volume);
            source->setDefaultMinDistance(sound.m_MinDistance);
            //sound.m_SourceReference = (int)m_Source.size()-1;
            return true;
        }
        
        return false;
    }

    bool Klang::UpdateAudioSource(AudioSourceComponent& sound)
    {
        auto& source = m_Source[sound.m_File.RelativeDirectory.c_str()];
        if(source)
        {
            source->setDefaultVolume(sound.m_Volume);
            source->setDefaultMinDistance(sound.m_MinDistance);
            return true;
        }

        return false;
    }

    void Klang::OnUpdate()
    {
        m_Engine->update();
    }

    //Can probably become private
    bool Klang::PlayAudioSource(AudioSourceComponent& sound, TransformComponent &transform)
    {
        auto & source = m_Source[sound.m_File.RelativeDirectory.c_str()];
        if(source)
        {
            irrklang::ISound * play;
            
            if(sound.m_3D)
                play = m_Engine->play3D(source, Math::ConvertVec3ToVec3df(transform.Position), sound.m_Loop, false, true);
            else
                play = m_Engine->play2D(source, sound.m_Loop, false, true);
            
            if(play)
            {
                m_Playing.push_back(play);
                sound.m_PlayReference = (int)m_Playing.size()-1;
                sound.m_Playing = true;
                return true;
            }   
        }
        
        return false;
    }

    void Klang::UpdateSound(AudioSourceComponent& sound, TransformComponent &transform)
    {
        if(sound.m_Shoot && !sound.m_Playing)
        {
            PlayAudioSource(sound, transform);
            sound.m_Shoot = false;
        }
        else if(sound.m_Playing)
        {
            //Might not need this line no more
            if(m_Playing.size() > 0)
            {
                auto& play = m_Playing[sound.m_PlayReference];
                if(play)
                {
                    if(play->isFinished())
                    {
                        AudioPlaying::iterator itr;
                        itr = remove(m_Playing.begin(), m_Playing.end(), play);
                        play->drop();
                        m_Playing.erase(itr);
                        sound.m_Playing = false;
                        sound.m_PlayReference = NULL;
                    }
                    else
                    {
                        if(sound.m_3D)
                        {
                            play->setPosition(Math::ConvertVec3ToVec3df(transform.Position));
                            play->setMinDistance(sound.m_MinDistance);
                        }

                        play->setVolume(sound.m_Volume);
                        play->setIsPaused(sound.m_Paused);
                        play->setIsLooped(sound.m_Loop);
                    }
                }
            }   
        }
    }

    void Klang::Clear()
    {
        for(auto playing : m_Playing)
        {
            playing->drop();
        }
        
        m_Playing.erase(m_Playing.begin(), m_Playing.end());

        //Drop is IrrKlang way of deleting memory, but will only fully delete it if it isnt being used by another file, in most cases it will delete, but all will be deleted by the end of the map
        for(auto points : m_Keys)
        {
            if(m_Source[points])
            m_Source[points]->drop();
        }
        
        m_Source.clear();
        
        m_Keys.erase(m_Keys.begin(), m_Keys.end());
    }

}