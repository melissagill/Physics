/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include"ForceGenerator.h"

class QuickForce:public ForceGenerator
{
	private:
		Vector3 mForce;

	public:
		QuickForce(Vector3 force);
		~QuickForce(){};
		void updateForce(RigidbodyUnit* unit);
};