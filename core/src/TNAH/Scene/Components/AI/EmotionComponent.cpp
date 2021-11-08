#include "tnahpch.h"
#include "EmotionComponent.h"

namespace tnah
{
	float EmotionComponent::GetArousal() { return m_Arousal; }
	float EmotionComponent::GetValence() { return m_Valence; }

	EmotionComponent::EmotionComponent()
	{
		InitialiseMap();
		UpdateTimer();
	}

	EmotionComponent::EmotionComponent(float valence, float arousal, Mood m)
	{
		InitialiseMap();	
		SetMood(m);
		SetValence(valence);
		SetArousal(arousal);
		UpdateTimer();
	}

	void EmotionComponent::SetArousal(float arousal) 
	{ 
		if (arousal > 1)
			m_Arousal = 1;
		else if (arousal < -1)
			m_Arousal = -1;
		else
			m_Arousal = arousal;
	}
	void EmotionComponent::SetValence(float valence) 
	{
		if (valence > 1)
			m_Valence = 1;
		else if (valence < -1)
			m_Valence = -1;
		else
			m_Valence = valence; 
	}

	void EmotionComponent::IncreaseArousal(float arousal)
	{
		m_Arousal = m_Arousal + (arousal * m_MultiplierPositiveArousal);

		//adjusts arousal if value overflows to ensure accuracy
		if (m_Arousal > 1)
			m_Arousal = 1;
	}

	void EmotionComponent::DecreaseArousal(float arousal)
	{
		m_Arousal = m_Arousal - (arousal * m_MultiplierNegativeArousal);

		//adjusts arousal if value overflows to ensure accuracy
		if (m_Arousal < -1)
			m_Arousal = -1;
	}

	void EmotionComponent::IncreaseValence(float valence)
	{
		m_Valence = m_Valence + (valence * m_MultiplierPositiveValence);

		//adjusts arousal if value overflows to ensure accuracy
		if (m_Valence > 1)
			m_Valence = 1;
	}

	void EmotionComponent::DecreaseValence(float valence)
	{
		m_Valence = m_Valence - (valence * m_MultiplierNegativeValence);

		//adjusts arousal if value overflows to ensure accuracy
		if (m_Valence < -1)
			m_Valence = -1;
	}


	void EmotionComponent::InitialiseMap()
	{
		// High Arousal - Positive Valence
		EmotionMap.insert({ (std::make_pair(1.0f, 0.5f)), Emotion::Excited });
		EmotionMap.insert({ (std::make_pair(0.66f, 0.5f)), Emotion::Delighted });
		EmotionMap.insert({ (std::make_pair(0.33f, 0.5f)), Emotion::Happy });

		// Low Arousal - Positive Valence
		EmotionMap.insert({ (std::make_pair(-0.33f, 0.5f)), Emotion::Content });
		EmotionMap.insert({ (std::make_pair(-0.66f, 0.5f)), Emotion::Relaxed });
		EmotionMap.insert({ (std::make_pair(-1.0f, 0.5f)), Emotion::Calm });

		// High Arousal - Negative Valence
		EmotionMap.insert({ (std::make_pair(1.0f, -0.5f)), Emotion::Tense });
		EmotionMap.insert({ (std::make_pair(0.66f, -0.5f)), Emotion::Angry });
		EmotionMap.insert({ (std::make_pair(0.33f, -0.5f)), Emotion::Frustrated });

		// Low Arousal - Negative Valence
		EmotionMap.insert({ (std::make_pair(-0.33f, -0.5f)), Emotion::Depressed });
		EmotionMap.insert({ (std::make_pair(-0.66f, -0.5)), Emotion::Bored });
		EmotionMap.insert({ (std::make_pair(-1.0f, -0.5)), Emotion::Tired });
	}

	Emotion EmotionComponent::ReturnEmotion(float arousal, float valence)
	{
		std::pair<float, float> emotionVals{ arousal, valence };
		it = EmotionMap.find(emotionVals);

		if (!EmotionMap.count(emotionVals))
			TNAH_CORE_ERROR("Emotion not within map: {0} {1} ", emotionVals.first, emotionVals.second);
		else 
			return it->second;
			

		return Emotion::Neutral;
	}

	void EmotionComponent::AddEmotion(float arousal, float valence, Emotion e)
	{
		std::pair<float, float> emotionVals{ arousal,valence };
		if (EmotionMap.count(emotionVals))
			TNAH_CORE_ERROR("Values aready in map: {0} {1} ", emotionVals.first, emotionVals.second);
		/*else
			std::cout << "Added to map" << std::endl;*/
		EmotionMap.insert({ emotionVals, e });
	}

	void EmotionComponent::RemoveEmotion(float arousal, float valence)
	{
		std::pair<float, float> emotionVals{ arousal, valence };
		/*if (EmotionMap.count(emotionVals))
			std::cout << "Emotion removed from map" << std::endl;
		else
			std::cout << "Emotion not in map" << std::endl;*/
		EmotionMap.erase(emotionVals);

	}

	float EmotionComponent::GetScaledArousal(float value)
	{
		float scaledValue = 0;
		if (value >= 0)
		{
			if (value <= 1.0f && value > 0.66f)
				scaledValue = 1.0f;
			else if (value <= 0.66f && value > 0.33f)
				scaledValue = 0.66f;
			else
				scaledValue = 0.33f;
		}
		else
		{
			if (value >= -1.0f && value < -0.66f)
				scaledValue = -1.0f;
			else if (value >= -0.66f && value < -0.33f)
				scaledValue = -0.66f;
			else
				scaledValue = -0.33f;
		}
		return scaledValue;
	}

	float EmotionComponent::GetScaledValence(float value)
	{
		float scaledValue = 0;
		if (value >= 0)
		{
			scaledValue = 0.5f;
		}
		else
		{
			scaledValue = -0.5f;
		}
		return scaledValue;
	}

	void EmotionComponent::AddTrait(Trait t)
	{
		if (m_Traits.size() > 3)
			TNAH_CORE_WARN("Object already has 3 traits");
		else if (std::find(m_Traits.begin(), m_Traits.end(), t) != m_Traits.end())
			TNAH_CORE_WARN("Trait exits");
		else
		{
			m_Traits.push_back(t);
			switch (t)
			{
			case Trait::Happy:
				m_MultiplierPositiveArousal += 0.05f; //more likely to feel positive
				m_MultiplierPositiveValence += 0.05f;
				
				m_MultiplierNegativeArousal -= 0.05f; //less likely to feel negative
				m_MultiplierNegativeValence -= 0.05f;
				break;

			case Trait::Delighted:

				m_MultiplierPositiveArousal += 0.1f; //more likely to feel positive
				m_MultiplierPositiveValence += 0.1f;

				m_MultiplierNegativeArousal -= 0.1f; //less likely to feel negative
				m_MultiplierNegativeValence -= 0.1f;
				break;


			case Trait::Cheerful:
				m_MultiplierPositiveArousal += 0.15f; //more likely to feel positive
				m_MultiplierPositiveValence += 0.15f;

				m_MultiplierNegativeArousal -= 0.15f; //less likely to feel negative
				m_MultiplierNegativeValence -= 0.15f;
				break;

			case Trait::Sad:
				m_MultiplierPositiveArousal -= 0.15f; //arousal more likely to decrease
				m_MultiplierPositiveValence -= 0.15f; //less likely to feel positive

				m_MultiplierNegativeArousal += 0.15f; // negative arousal more likely to increase
				m_MultiplierNegativeValence += 0.15f; //more likely to feel negative
				break;

			case Trait::Bland:
				m_MultiplierPositiveArousal -= 0.1f; //arousal more likely to decrease
				m_MultiplierPositiveValence -= 0.1f; //less likely to feel positive

				m_MultiplierNegativeArousal += 0.1f; // negative arousal more likely to increase
				m_MultiplierNegativeValence += 0.1f; //more likely to feel negative
				break;

			case Trait::Depressed:
				m_MultiplierPositiveArousal -= 0.05f; //arousal more likely to decrease
				m_MultiplierPositiveValence -= 0.05f; //less likely to feel positive

				m_MultiplierNegativeArousal += 0.05f; // negative arousal more likely to increase
				m_MultiplierNegativeValence += 0.05f; //more likely to feel negative
				break;

			case Trait::Patient:
				m_MultiplierNegativeArousal -= 0.05f; //arousal more likely to decrease
				break;

			case Trait::Peaceful:
				m_MultiplierNegativeArousal -= 0.1f; //arousal more likely to decrease
				m_MultiplierPositiveValence += 0.1f; // more likely to feel positive
				break;

			case Trait::Carefree:
				m_MultiplierNegativeArousal -= 0.15f; //arousal more likely to decrease
				m_MultiplierPositiveValence += 0.15f; // more likely to feel positive
				break;

			case Trait::Impatient:
				m_MultiplierPositiveArousal += 0.05f; //arousal more likely to increase
				break;

			case Trait::Aggressive:
				m_MultiplierPositiveArousal += 0.1f; //arousal more likely to increase
				m_MultiplierNegativeValence += 0.1f; //more likely to feel negative
				break;

			case Trait::Paranoid:
				m_MultiplierPositiveArousal += 0.15f; //arousal more likely to increase
				m_MultiplierNegativeValence += 0.15f; //more likely to feel negative
				break;
			}
		}
	}

	void EmotionComponent::Update(float dt)
	{
		Emotion em = ReturnEmotion(GetScaledArousal(GetArousal()), GetScaledValence(GetValence()));
		m_State = em;
		IncreaseArousal(0.0001f * dt);
		DecreaseArousal(0.0001f * dt);
		IncreaseValence(0.0001f * dt);
		DecreaseValence(0.0001f * dt);
		UpdateMood(dt);
	}

	void EmotionComponent::SetMood(Mood m)
	{
		switch (m)
		{
		case Mood::Happy:
			m_MultiplierPositiveArousal += 0.25f; //arousal more likely to be positive
			m_MultiplierPositiveValence += 0.25; // easier to feel positive

			m_MultiplierNegativeArousal -= 0.25f; //less likely to have negative arousal
			m_MultiplierNegativeValence -= 0.25f; //less likely to feel negative

			m_Mood = m;
			break;
		case Mood::Angry:
			m_MultiplierPositiveArousal += 0.25f; //arousal more likely to be positive
			m_MultiplierPositiveValence -= 0.25f; // harder to feel positive

			m_MultiplierNegativeArousal -= 0.25f; // less likely to have negative arousal
			m_MultiplierNegativeValence += 0.25f; // easier to feel negative

			m_Mood = m;
			break;
		case Mood::Sad:
			m_MultiplierPositiveArousal -= 0.25f; //arousal more likely to be negative
			m_MultiplierPositiveValence -= 0.25f; // harder to feel positive 

			m_MultiplierNegativeArousal += 0.25f; // more likely to feel negative arousal
			m_MultiplierNegativeValence += 0.25f; // easier to feel negative

			m_Mood = m;
			break;
		case Mood::Relaxed:
			m_MultiplierPositiveArousal -= 0.25f; //arousal more likely to be negative
			m_MultiplierPositiveValence += 0.25f; //easier to feel positive

			m_MultiplierNegativeArousal += 0.25f; //more likely to feel negative arousal
			m_MultiplierNegativeValence -= 0.25f; //harder to feel negative
			
			m_Mood = m;
			break;

		default:
			break;
		}

	}

	void EmotionComponent::UpdateMood(float dt)
	{
		if(internalTimer <= 0)
		{
			switch (m_Mood)
			{
			case Mood::Happy:
				m_MultiplierPositiveArousal -= 0.25f; //arousal more likely to be positive
				m_MultiplierPositiveValence -= 0.25; // easier to feel positive

				m_MultiplierNegativeArousal += 0.25f; //less likely to have negative arousal
				m_MultiplierNegativeValence += 0.25f; //less likely to feel negative
				break;
			case Mood::Angry:
				m_MultiplierPositiveArousal -= 0.25f; //arousal more likely to be positive
				m_MultiplierPositiveValence += 0.25f; // harder to feel positive

				m_MultiplierNegativeArousal += 0.25f; // less likely to have negative arousal
				m_MultiplierNegativeValence -= 0.25f; // easier to feel negative
				break;
			case Mood::Sad:
				m_MultiplierPositiveArousal += 0.25f; //arousal more likely to be negative
				m_MultiplierPositiveValence += 0.25f; // harder to feel positive 

				m_MultiplierNegativeArousal -= 0.25f; // more likely to feel negative arousal
				m_MultiplierNegativeValence -= 0.25f; // easier to feel negative
				break;
			case Mood::Relaxed:
				m_MultiplierPositiveArousal += 0.25f; //arousal more likely to be negative
				m_MultiplierPositiveValence -= 0.25f; //easier to feel positive

				m_MultiplierNegativeArousal -= 0.25f; //more likely to feel negative arousal
				m_MultiplierNegativeValence += 0.25f; //harder to feel negative
				break;

			default:
				break;
			}
			Mood temp = Mood::Neutral;
		
			switch (m_State)
			{
			case Emotion::Happy:
			case Emotion::Excited:
			case Emotion::Delighted:
				temp = Mood::Happy;
				break;
			case Emotion::Frustrated:
			case Emotion::Angry:
			case Emotion::Tense:
				temp = Mood::Angry;
				break;
			case Emotion::Bored:
			case Emotion::Depressed:
			case Emotion::Tired:
				temp = Mood::Sad;
				break;
			case Emotion::Calm:
			case Emotion::Content:
			case Emotion::Relaxed:
				temp = Mood::Relaxed;
				break;
			default:
				break;
			}
		
			SetMood(temp);
			UpdateTimer();
		}
		else
		{
			internalTimer -= dt;
		}
	}


	
	std::string EmotionComponent::GetCurrentEmotionAsString()
	{
		switch (GetEmotion())
		{
			case Emotion::Happy:
				return "Happy";
		case Emotion::Angry:
			return "Angry";
			case Emotion::Bored:
				return "Bored";
		case Emotion::Calm:
			return "Calm";
		case Emotion::Content:
			return "Content";
			case Emotion::Delighted:
				return "Delighted";
			case Emotion::Depressed:
				return "Depressed";
			case Emotion::Excited:
				return "Excited";
			case Emotion::Frustrated:
				return "Frustrated";
			case Emotion::Relaxed:
				return "Relaxed";
			case Emotion::Tense:
				return  "Tense";
			case Emotion::Tired:
				return "Tired";
			default:
				return "Error";
		}
	}

	std::string EmotionComponent::GetCurrentMoodAsString()
	{
		switch (GetMood())
		{
		case Mood::Happy:
			return "Happy";
		case Mood::Relaxed:
			return "Relaxed";
		case Mood::Angry:
			return "Angry";
		case Mood::Sad:
			return "Sad";
		default:
			return "Error";
		}
	}

	std::string EmotionComponent::GetTraitAsString(int pos)
	{
		std::string trait = "Trait: ";
			switch (m_Traits[pos])
			{
			case Trait::Happy:
				return "Happy";
			case Trait::Delighted:
				return "Delighted";
			case Trait::Cheerful:
				return "Cheerful";
			case Trait::Sad:
				return "Sad";
			case Trait::Bland:
				return "Bland";
			case Trait::Depressed:
				return "Depressed";
			case Trait::Patient:
				return "Patient";
			case Trait::Peaceful:
				return "Peaceful";
			case Trait::Carefree:
				return "Carefree";
			case Trait::Impatient:
				return "Impatient";
			case Trait::Aggressive:
				return "Aggressive";
			case Trait::Paranoid:
				return "Paranoid";
			default:
				return "Error";
			}
	}

	std::string EmotionComponent::GetTraitsAsString()
	{
		int i = 0;
		std::string comma = ", ";
		std::string traitList = "Traits: ";

		for (itr = m_Traits.begin(); itr < m_Traits.end(); itr++)
		{
			std::string trait = GetTraitAsString(i);
			traitList = traitList + trait + comma;
			i++;

		}
		traitList.resize(traitList.size() - 2);
		return traitList;
	}

}