/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#include"Spring.h"

Spring::Spring(RigidbodyUnit* base,float springConstant,float rest)
{
	mBase=base;
	mK=springConstant;
	mRestLength=rest;
	mDuration=FLT_MAX;
}

void Spring::updateForce(RigidbodyUnit* unit)
{
	Vector3 dir=mBase->getPos()-unit->getPos();
	float dist=dir.Magnitude();
	dir.Normalize();
	float deltaL=mRestLength-dist;
	Vector3 force=dir*(-mK*deltaL);
	unit->addForce(force);
}