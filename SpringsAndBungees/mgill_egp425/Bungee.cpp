/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#include"Bungee.h"

Bungee::Bungee(RigidbodyUnit* base,float springConstant,float rest)
{
	mBase=base;
	mK=springConstant;
	mRestLength=rest;
	mDuration=FLT_MAX;
}

void Bungee::updateForce(RigidbodyUnit* unit)
{
	Vector3 dir=mBase->getPos()-unit->getPos();
	float dist=dir.Magnitude();
	float deltaL=mRestLength-dist;
	if(deltaL>=0)
		return;
	dir.Normalize();
	Vector3 force=dir*(-mK*deltaL);
	unit->addForce(force);
}