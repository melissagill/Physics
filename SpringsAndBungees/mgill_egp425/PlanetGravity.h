#pragma once
#include"ForceGenerator.h"

class PlanetGravity:public ForceGenerator
{
	private:
		RigidbodyUnit* mPlanet;

	public:
		PlanetGravity(RigidbodyUnit* planet);
		~PlanetGravity(){};
		void updateForce(RigidbodyUnit* unit);
};