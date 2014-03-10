/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include"ForceGenerator.h"

class Gravity:public ForceGenerator
{
	public:
		Gravity(){mDuration=FLT_MAX;}
		~Gravity(){};
		
		void updateForce(RigidbodyUnit* unit);
};