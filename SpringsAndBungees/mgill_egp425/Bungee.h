/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include"ForceGenerator.h"

class Bungee:public ForceGenerator
{
	private:
		float mRestLength;
		float mK;
		RigidbodyUnit* mBase;

	public:
		Bungee(RigidbodyUnit* base,float springConstant=1,float rest=0);
		~Bungee(){};
		void updateForce(RigidbodyUnit* unit);
};