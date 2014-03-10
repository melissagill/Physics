/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#include"QuickForce.h"

QuickForce::QuickForce(Vector3 force)
{
	mForce=force;
	mDuration=RigidbodyUnit::Time;
}

void QuickForce::updateForce(RigidbodyUnit* unit)
{
	unit->addForce(mForce);
}