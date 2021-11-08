#pragma once

namespace tnah
{
	/**
	 * @brief each emotional state is represented in this enum class
	 */
    enum class Emotion 
	{
	Neutral = 0,
	Excited, Delighted, Happy, // High Arousal - Positive Valence
	Content, Relaxed, Calm, // Low Arousal - Positive Valence
	Tense, Angry, Frustrated, // High Arousal - Negative Valence
	Depressed, Bored, Tired,  // Low Arousal - Negative Valence
	};

	/**
	 * @fn  inline std::ostream& operator<<(std::ostream& os, Emotion e) 
	 * 
	 * @brief  Used to allow for the printing of Emotion states
	 * 
	 * @author Dylan Blereau
	 * @date   2/11/2021
	 * 
	 * @param os - output stream object 
	 * @param e - refers to the Emotion states
	 * @return - output stream 
	 */
	inline std::ostream& operator<<(std::ostream& os, Emotion e) 
	{
		switch (e) 
		{
		case Emotion::Happy: 
			return os << "Happy";
		case Emotion::Delighted:
			return os << "Delighted";
		case Emotion::Excited:
			return os << "Excited";
		case Emotion::Calm:
			return os << "Calm";
		case Emotion::Relaxed:
			return os << "Relaxed";
		case Emotion::Content:
			return os << "Content";
		case Emotion::Frustrated:
			return os << "Frustrated";
		case Emotion::Angry:
			return os << "Angry";
		case Emotion::Tense:
			return os << "Tense";
		case Emotion::Tired:
			return os << "Tired";
		case Emotion::Bored:
			return os << "Bored";
		case Emotion::Depressed:
			return os << "Depressed";

		default:
			return os << "Neutral";
		}
	}

	/**
	 * @enum Mood
	 *
	 * @brief each mood state is represented in this enum class
	 */
	enum class Mood 
	{
		Neutral = 0,
		Happy, // High Arousal - Positive Valence
		Angry, // High Arousal - Negative Valence
		Sad, // Low Arousal - Negative Valence 
		Relaxed // Low Arousal - Positive Valence
	};

	/**
	 * @fn  inline std::ostream& operator<<(std::ostream& os, Mood m)
	 *
	 * @brief  Used to allow for the printing of Mood states
	 *
	 * @author Dylan Blereau
	 * @date   2/11/2021
	 *
	 * @param os - output stream object
	 * @param m - refers to the Mood states
	 * @return - output stream
	 */
	inline std::ostream& operator<<(std::ostream& os, Mood m)
	{
		switch (m)
		{
		case Mood::Happy:
			return os << "Happy";
		case Mood::Angry:
			return os << "Delighted";
		case Mood::Sad:
			return os << "Excited";
		case Mood::Relaxed:
			return os << "Calm";
	
		default:
			return os << "Neutral";
		}
	}

	/**
	 * @enum Trait
	 *
	 * @brief each character trait is represented in this enum class
	 */
	enum class Trait
	{
		Neutral,

		Cheerful, Delighted, Happy, // High Arousal - Positive Valence
		Depressed, Bland, Sad, // Low Arousal - Negative Valence


		Carefree, Peaceful, Patient, // Low Arousal - Positive Valence
		Paranoid, Aggressive, Impatient // High Arousal - Negative Valence
	};

	/**
	 * @fn  inline std::ostream& operator<<(std::ostream& os, Trait t)
	 *
	 * @brief  Used to allow for the printing of character traits
	 *
	 * @author Dylan Blereau
	 * @date   2/11/2021
	 *
	 * @param os - output stream object
	 * @param t - refers to the character Traits
	 * @return - output stream
	 */
	inline std::ostream& operator<<(std::ostream& os, Trait t)
	{
		switch (t)
		{
		case Trait::Happy:
			return os << "Happy";
		case Trait::Delighted:
			return os << "Delighted";
		case Trait::Cheerful:
			return os << "Cheerful";
		case Trait::Sad:
			return os << "Sad";
		case Trait::Bland:
			return os << "Bland";
		case Trait::Depressed:
			return os << "Depressed";
		case Trait::Patient:
			return os << "Patient";
		case Trait::Peaceful:
			return os << "Peaceful";
		case Trait::Carefree:
			return os << "Carefree";
		case Trait::Impatient:
			return os << "Impatient";
		case Trait::Aggressive:
			return os << "Aggressive";
		case Trait::Paranoid:
			return os << "Paranoid";

		default:
			return os << "Neutral";
		}
	}
}
