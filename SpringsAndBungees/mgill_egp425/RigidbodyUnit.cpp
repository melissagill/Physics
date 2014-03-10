/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#include"RigidbodyUnit.h"
#include"main.h"

Vector3 RigidbodyUnit::Gravity=Vector3(0,-9.8f,0);
float RigidbodyUnit::Time=.04f;
float RigidbodyUnit::Dampening=.999f;

RigidbodyUnit::RigidbodyUnit(Vector3 position,Vector3 rotation,Vector3 scale,float radius,Vector3 color)
	:Unit(position,rotation,scale,radius,color)
{
	mMass=(mRadius*mRadius*mRadius*3.1415926f*4.0f)/3;
	mInverseMass=1/mMass;
}

RigidbodyUnit::RigidbodyUnit(Vector3 position,Vector3 rotation,Vector3 scale,float radius,float mass,Vector3 color)
	:Unit(position,rotation,scale,radius,color)
{
	mMass=mass;
	mInverseMass=1/mMass;
}

void RigidbodyUnit::update()
{
	mPosition+=mVelocity*Time;

	Vector3 acc=mForce*mInverseMass;
	mVelocity=(mVelocity*Dampening)+(acc*Time);
	mForce=Vector3();
}

void RigidbodyUnit::addForce(Vector3 force)
{
	mForce+=force;
}

void RigidbodyUnit::bounce(Vector3 dir,float lim)
{
	if(dir.x==1)
	{
		mPosition.x=lim+mRadius;
		mVelocity.x*=-1;
	}
	else if(dir.y==1)
	{
		mPosition.y=lim+mRadius;
		mVelocity.y*=-1;
	}
	else if(dir.z==1)
	{
		mPosition.z=lim+mRadius;
		mVelocity.z*=1;
	}
}

void RigidbodyUnit::setVelocity(Vector3 vel)
{
	mVelocity=vel;
}

void RigidbodyUnit::setMass(float mass)
{
	mMass=mass;
	mInverseMass=1/mass;
}

Vector3 RigidbodyUnit::getMomentum()
{
	return mVelocity*(1/mInverseMass);
}

float RigidbodyUnit::getMass()
{
	return mMass;
}

float RigidbodyUnit::getInvMass()
{
	return mInverseMass;
}