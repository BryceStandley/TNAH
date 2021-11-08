#pragma once
#include "Emotion.h"

namespace tnah
{
	/**
	 * @class  EmotionComponent
	 *
	 * @brief  The EmotionComponent class repsonsible for the managing of emotions, mood and personality. Can be attached as a component to give a gameobject the ability to have Emotions
	 *
	 * @author Dylan Blereau
	 * @date   3/11/2021
	 */
	class EmotionComponent 
	{
	public:

		/**
		 * @fn  EmotionComponent
		 * 
		 * @brief  Default Constructor
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 */
		EmotionComponent();

		/**
		 * @fn  EmotionComponent
		 * 
		 * @brief  Constructor that takes valence, arousal and a mood 
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param valence - the valence value
		 * @param arousal - the arousal value
		 * @param m - the score of the NPC
		 */
		EmotionComponent(float valence, float arousal, Mood m);

		/**
		 * @fn  GetEmotion
		 * 
		 * @brief  Gets and returns the current emotion
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return Current Emotion
		 */
		Emotion GetEmotion() { return m_State; }

		/**
		 * @fn  SetEmotion
		 * 
		 * @brief  Sets the emotion to the emotion provided as a parameter
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param e
		 */
		void SetEmotion(Emotion e) { m_State = e; }

		/**
		 * @fn  GetMood
		 * 
		 * @brief  Gets and returns the current mood
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return Current Mood
		 */
		Mood GetMood() { return m_Mood; }

		/**
		 * @fn  GetArousal
		 * 
		 * @brief  Gets the arousal of the emotion
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return float - the arousal value
		 */
		float GetArousal();

		/**
		 * @fn  SetArousal
		 * 
		 * @brief  Sets the arousal of the emotion to the given value
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param arousal
		 */
		void SetArousal(float arousal);

		/**
		 * @fn  GetValence
		 * 
		 * @brief Gets the valence value of the emotion
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return the valence value 
		 */
		float GetValence();

		/**
		 * @fn  SetValence
		 * 
		 * @brief  Sets the Valence of the emotion to the given value
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param valence
		 */
		void SetValence(float valence);

		/**
		 * @fn  IncreaseArousal
		 * 
		 * @brief  Increases arousal by the value given
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param arousal
		 */
		void IncreaseArousal(float arousal);

		
		/**
		 * @fn  DecreaseArousal
		 * 
		 * @brief decreases arousal by the value given
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param arousal
		 */
		void DecreaseArousal(float arousal);

		/**
		 * @fn  IncreaseValence
		 * 
		 * @brief increases valence by the value given  
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param valence
		 */
		void IncreaseValence(float valence);

		/**
		 * @fn  DecreaseValence
		 * 
		 * @brief  decreases arousal by the value given
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param valence
		 */
		void DecreaseValence(float valence);

	

		//Returns the Arousal and Valence of a given Emotion
		/**
		 * @fn  ReturnEmotion
		 * 
		 * @brief  Returns the emotion in the emotionMap that corresponds to the given arousal and valence values
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param arousal
		 * @param valence
		 * @return Emotion
		 */
		Emotion ReturnEmotion(float arousal, float valence);

		//checks if emotion is present in map, otherwise adds the emotion to the map 

		/**
		 * @fn  AddEmotion
		 * 
		 * @brief Adds an emotion into the emotionMap using the given arousal, valence and Emotion name (Emotion enum name must be in Enum list to allow for this to work) 
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param arousal
		 * @param valence
		 * @param e
		 */
		void AddEmotion(float arousal, float valence, Emotion e);


		/**
		 * @fn  RemoveEmotion
		 * 
		 * @brief  Removes the emotion from the map that has the matching arousal and valence values
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param arousal
		 * @param valence
		 */
		void RemoveEmotion(float arousal, float valence);

		/**
		 * @fn  AddTrait
		 * 
		 * @brief  Adds a trait to the personality vector
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param t
		 */
		void AddTrait(Trait t);

		/**
		 * @fn  Update
		 * 
		 * @brief  Updates the EmotionComponent with deltaTime
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param dt - DeltaTime
		 */
		void Update(float dt);
		
		/**
		 * @fn  GetScaledArousal
		 * 
		 * @brief  Gets the scaled arousal value
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param value
		 * @return scaled arousal value
		 */
		float GetScaledArousal(float value);

		/**
		 * @fn  GetScaledValence
		 * 
		 * @brief  Gets the scaled valence value
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param value
		 * @return scaled valence value
		 */
		float GetScaledValence(float value);


		/**
		 * @fn  GetPositiveValenceMultiplier
		 * 
		 * @brief  Gets the positve valence multiplier
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return the Positive Valence multiplier
		 */
		float GetPositiveValenceMultiplier() { return m_MultiplierPositiveValence; }

		/**
		 * @fn  GetNegativeValenceMultiplier
		 * 
		 * @brief  Gets the negative valence multiplier
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return the negative valence multiplier
		 */
		float GetNegativeValenceMultiplier() { return m_MultiplierNegativeValence; }

		/**
		 * @fn  GetPositiveArosualMultiplier
		 * 
		 * @brief  Gets the positive arousal multiplier
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return the positive arousal multiplier
		 */
		float GetPositiveArosualMultiplier() { return m_MultiplierPositiveArousal; }

		/**
		 * @fn  GetNegativeArousalMultiplier
		 * 
		 * @brief  Gets the negative arousal multiplier
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return the negative arousal multiplier
		 */
		float GetNegativeArousalMultiplier() { return m_MultiplierNegativeArousal; }


		/**
		 * @fn  SetMood
		 * 
		 * @brief  Sets the mood to the given mood value
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param m - refers to the mood being set
		 */
		void SetMood(Mood m);

		/**
		 * @fn  GetCurrentEmotionAsString
		 * 
		 * @brief  Gets the current emotion and returns it as a string
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return string that references the current emotion
		 */
		std::string GetCurrentEmotionAsString();

		/**
		 * @fn  GetCurrentMoodAsString
		 * 
		 * @brief  Gets the current mood and returns it as a string
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return string that contains the name of the current mood
		 */
		std::string GetCurrentMoodAsString();

		/**
		 * @fn  GetTraitAsString
		 * 
		 * @brief  Gets the trait at the given position and returns it as a string
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param pos - the positon in the personality trait vector you want to get 
		 * @return string that contains the name of the trait at the given position
		 */
		std::string GetTraitAsString(int pos);

		/**
		 * @fn  GetTraitsAsString
		 * 
		 * @brief  Calls the GetTraitAsString function numerous times to get all the active traits as a string
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @return a string for each trait currently active
		 */
		std::string GetTraitsAsString();
	

		/**
		 * @fn  UpdateTimer
		 * 
		 * @brief  Updates the internalTimer back to its default value
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 */
		void UpdateTimer() {internalTimer = 15.0f;}
	private:

		/**
		 * @fn  InitialiseMap
		 * 
		 * @brief  Initialises the map with all the emotions used
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 */
		void InitialiseMap();

		/**
		 * @fn  UpdateMood
		 * 
		 * @brief  Updates the mood when required
		 * 
		 * @author Dylan Blereau
		 * @date   3/11/2021
		 * 
		 * @param dt - deltaTime
		 */
		void UpdateMood(float dt);

		/// A map containing all available emotions, with the key being the Emotion valence and arousal
		std::map <std::pair<float,float>, Emotion> EmotionMap;

		/// an iterator for the emotion map
		std::map <std::pair<float, float>, Emotion>::iterator it = EmotionMap.begin();

		/// arousal value
		float m_Arousal = 0.0f;

		/// valence value
		float m_Valence = 0.0f;

		/// positive valence multiplier
		float m_MultiplierPositiveValence = 1.0f;

		/// negative valence multiplier
		float m_MultiplierNegativeValence = 1.0f;	

		/// positive arousal multiplier
		float m_MultiplierPositiveArousal = 1.0f;

		/// negative arousal multiplier
		float m_MultiplierNegativeArousal = 1.0f;
	
		/// Current Emotional State
		Emotion m_State = Emotion::Neutral;

		/// Current Mood
		Mood m_Mood = Mood::Neutral;

		/// Vector of all traits of the AI - AKA its Personality
		std::vector<Trait> m_Traits;

		/// iterator
		std::vector<Trait>::iterator itr;

		/// internal timer used to assist with changing moods
		float internalTimer = 0;
};
}
