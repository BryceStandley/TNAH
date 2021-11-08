#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Core/FileStructures.h"
#include "ComponentIdentification.h"

namespace tnah {

	/**********************************************************************************************//**
	 * @class	AudioSourceComponent
	 *
	 * @brief	An audio source component.
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 **************************************************************************************************/

	class AudioSourceComponent
	{
	public:

		/**********************************************************************************************//**
		 * @fn	AudioSourceComponent::AudioSourceComponent(Resource file = {"defaultsoundfile.wav"}, float minDistance = 1.0f, float volume = 1.0f, bool threeDim = true, bool loop = false)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	file	   	(Optional) The file.
		 * @param 	minDistance	(Optional) The minimum distance.
		 * @param 	volume	   	(Optional) The volume.
		 * @param 	threeDim   	(Optional) True to three dim.
		 * @param 	loop	   	(Optional) True to loop.
		 **************************************************************************************************/

		AudioSourceComponent(Resource file = {"defaultsoundfile.wav"}, float minDistance = 1.0f, float volume = 0.5f, bool threeDim = true, bool loop = false)
		: m_MinDistance(minDistance), m_Volume(volume), m_Loop(loop), m_SourceReference(0),
		m_PlayReference(0), m_Playing(false), m_Loaded(false), m_Shoot(false), m_3D(threeDim),m_StartLoad(true), m_Paused(false) {m_File = file;}

		/**********************************************************************************************//**
		 * @fn	bool AudioSourceComponent::GetStartLoad() const
		 *
		 * @brief	Gets start load
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool GetStartLoad() const { return m_StartLoad; }

		/**********************************************************************************************//**
		 * @fn	void AudioSourceComponent::SetStartLoad(const bool b)
		 *
		 * @brief	Sets start load
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	b	True to b.
		 **************************************************************************************************/

		void SetStartLoad(const bool b) {m_StartLoad = b;}


		/** @brief	Source reference */
		int m_SourceReference;


		/** @brief	The play reference */
		int m_PlayReference;


		/** @brief	The minimum distance */
		float m_MinDistance;


		/** @brief	The volume */
		float m_Volume;


		/** @brief	True to loop */
		bool m_Loop;


		/** @brief	True to playing */
		bool m_Playing;


		/** @brief	True if paused */
		bool m_Paused;


		/** @brief	True if the data was loaded */
		bool m_Loaded;


		/** @brief	True to shoot */
		bool m_Shoot;


		/** @brief	True if 3D */
		bool m_3D;


		/** @brief	The file */
		Resource m_File;

		

	private:

		/** @brief	True to start load */
		bool m_StartLoad;
		friend class EditorUI;
		inline static std::string s_SearchString = "audio source component";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::AudioSource},
{{ComponentCategory::Audio}}
		};
	};

	/**********************************************************************************************//**
	 * @class	AudioListenerComponent
	 *
	 * @brief	An audio listener component.
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 **************************************************************************************************/

	class AudioListenerComponent
	{
	public:

		/**********************************************************************************************//**
		 * @fn	AudioListenerComponent::AudioListenerComponent(bool active = false)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	active	(Optional) True to active.
		 **************************************************************************************************/

		AudioListenerComponent(bool active = false) : m_ActiveListing(active) {}

		


		/** @brief	True to active listing */
		bool m_ActiveListing;

	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "audio listener component";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::AudioListener},
{{ComponentCategory::Audio}}
		};
	};

}
