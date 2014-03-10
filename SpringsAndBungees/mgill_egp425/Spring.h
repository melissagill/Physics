/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include"ForceGenerator.h"

class Spring:public ForceGenerator
{
	private:
		float mRestLength;
		float mK;
		RigidbodyUnit* mBase;
		
	public:
		Spring(RigidbodyUnit* base,float springConstant=1,float rest=0);
		~Spring(){};
		void updateForce(RigidbodyUnit* unit);
};