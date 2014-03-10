/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include"RigidbodyUnit.h"

class ForceGenerator
{
	protected:
		float mDuration;

	public:
		virtual void updateForce(RigidbodyUnit* unit)=0;
		float Duration(){return mDuration;};
};