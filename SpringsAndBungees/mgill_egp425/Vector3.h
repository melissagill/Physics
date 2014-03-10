/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once

class Vector3
{
	public:
		float x;
		float y;
		float z;

		Vector3(){x=0;y=0;z=0;};
		Vector3(float pX,float pY,float pZ){x=pX;y=pY;z=pZ;};

		void Normalize();
		float Magnitude();
		float MagnitudeSquared();

		float get(int index);
		void set(int index,float value);

		Vector3& operator=(const Vector3 &rhs);
		Vector3& operator+=(const Vector3 &rhs);
		Vector3& operator-=(const Vector3 &rhs);
		Vector3& operator*=(const float &rhs);
		Vector3& operator/=(const float &rhs);

		Vector3 operator+(const Vector3 &rhs);
		Vector3 operator-(const Vector3 &rhs);
		Vector3 operator*(const float &rhs);
		Vector3 operator/(const float &rhs);

		bool operator==(const Vector3 &rhs);
};