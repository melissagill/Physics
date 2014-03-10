/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include<math.h>
#include"Unit.h"

class RigidbodyUnit:public Unit
{
	private:
		Vector3 mForce;
		Vector3 mVelocity;

		float mInverseMass;
		float mMass;

	public:
		static Vector3 Gravity;
		static float Time;
		static float Dampening;

		RigidbodyUnit(Vector3 position,Vector3 rotation,Vector3 scale,float radius,Vector3 color);
		RigidbodyUnit(Vector3 position,Vector3 rotation,Vector3 scale,float radius,float mass,Vector3 color);
		~RigidbodyUnit(){};

		void update();

		void setVelocity(Vector3 vel);
		Vector3 getVelocity(){return mVelocity;};

		void addForce(Vector3 force);
		void bounce(Vector3 dir,float lim);

		void setMass(float mass);
		Vector3 getMomentum();

		float getMass();
		float getInvMass();
};