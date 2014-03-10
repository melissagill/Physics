#include"PlanetGravity.h"

PlanetGravity::PlanetGravity(RigidbodyUnit* planet)
{
	mPlanet=planet;
	mDuration=FLT_MAX;
}

void PlanetGravity::updateForce(RigidbodyUnit* unit)
{
	Vector3 dir=mPlanet->getPos()-unit->getPos();
	float sqDist=dir.MagnitudeSquared();
	dir.Normalize();
	Vector3 force= dir * .45f * ((unit->getMass()*mPlanet->getMass())/sqDist);
	unit->addForce(force);
	//mPlanet->addForce(force*-1);//uncomment if each planet only creates a force for those that it doesn't already have a connection with
}