#pragma once
#include "TNAH/Renderer/Light.h"

namespace tnah {

	/**********************************************************************************************//**
	 * @class	PointLight
	 *
	 * @brief	A point light 
	 *
	 * @author	Bryce Standley
	 * @date	10/09/2021
	 *
	 **************************************************************************************************/
	class PointLight : public Light
	{
	public:

		/**********************************************************************************************//**
		 * @fn	PointLight::PointLight()
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 **************************************************************************************************/
		PointLight();

		/**********************************************************************************************//**
		 * @fn	PointLight::PointLight(const float& constant, const float& linear, const float& quadratic);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 * 
		 * @param constant
		 * @param linear
		 * @param quadratic
		 * 
		 *
		 **************************************************************************************************/
		PointLight(const float& constant, const float& linear, const float& quadratic);

		/**********************************************************************************************//**
		 * @fn	PointLight::~PointLight();
		 *
		 * @brief	Deconstructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 *
		 *
		 **************************************************************************************************/
		virtual ~PointLight() {}

		/**********************************************************************************************//**
		 * @fn	void PointLight::SetUpLight(const float& constant, const float& linear, const float& quadratic);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param constant
		 * @param linear
		 * @param quadratic
		 *
		 *
		 **************************************************************************************************/
		void SetUpLight(const float& constant, const float& linear, const float& quadratic);
	};
}
