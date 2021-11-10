#include "tnahpch.h"
#include "MiniAudio.h"

namespace tnah {

	bool MiniAudio::SetListener(TransformComponent &transforms) const
	{
		return false;
	}

	bool MiniAudio::AddAudioSource(AudioSourceComponent &sound)
	{
		return false;
	}

	bool MiniAudio::UpdateAudioSource(AudioSourceComponent &sound)
	{
		return false;
	}

	void MiniAudio::OnUpdate()
	{

	}

	void MiniAudio::UpdateSound(AudioSourceComponent &sound, TransformComponent &transforms)
	{

	}

	bool MiniAudio::Active() const
	{
		return false;
	}

	void MiniAudio::Clear()
	{

	}


}