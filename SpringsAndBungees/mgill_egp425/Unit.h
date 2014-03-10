/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include<iostream>
#include"Vector3.h"

using namespace std;

class Unit
{
	protected:
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;
		Vector3 mColor;

		float mRadius;

	public:
		Unit(Vector3 position,Vector3 rotation,Vector3 scale,float radius,Vector3 color);
		~Unit(){};

		virtual void update();
		void draw();

		Vector3 getPos(){return mPosition;};
		Vector3 getRot(){return mRotation;};
		Vector3 getColor(){return mColor;};
		void move(Vector3 offset);
		void rotate(Vector3 rot);
		float getRadius(){return mRadius;};

		void setScale(Vector3 scale){mScale=scale;};
		Vector3 getScale(){return mScale;};
};