/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include<cfloat>
#include"ForceGenerator.h"

struct ForceRegistration
{
	RigidbodyUnit* Unit;
	ForceGenerator* Force;
	float Duration;

	ForceRegistration(RigidbodyUnit* unit, ForceGenerator* force)
	{
		Unit=unit;
		Force=force;
		Duration=Force->Duration();
	};

	ForceRegistration(RigidbodyUnit* unit, ForceGenerator* force, float duration)
	{
		Unit=unit;
		Force=force;
		Duration=duration;
	};

	~ForceRegistration() {delete Force;};
};