/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include<stdlib.h>
#include<GL/glut.h>
#include<iostream>
#include<vector>
#include<math.h>
#include"ForceRegistry.h"
#include"Matrix3.h"
#include"Vector2.h"
#include"Gravity.h"
#include"Spring.h"
#include"Bungee.h"
#include"PlanetGravity.h"

using namespace std;

struct Connection
{
	Vector2 Indices;
	Vector3 Color;
};

class Game
{
	private:
		vector<RigidbodyUnit*> mUnits;
		vector<Connection> mConnections;
		ForceRegistry mForceRegistry;
		int mTargetIndex;

		Vector3 mCameraPos;
		Vector3 mCameraRot;

		float mFloorHeight;

	public:
		Game(){};
		~Game(){};

		void init();
		void cleanup();

		void update();
		void draw();

		void drawLabel(string word,Vector3 pos,Vector3 color);
		
		float checkWorldToScreen(Vector3 pos,float radius);

		void moveCamera(Vector3 dir);
		void rotateCamera(Vector3 rot);
		void switchTarget(int index);
		void centerViewOn(int index);
		void switchTarget();
		RigidbodyUnit* addRigidbodyUnit();
		RigidbodyUnit* addRigidbodyUnit(Vector3 pos,float radius,Vector3 rot=Vector3(),Vector3 scale=Vector3(1,1,1));

		void FreeFallBungee(bool grav);
		void FreeFallSpring(bool grav);
		void AnchoredBungee(bool grav);
		void AnchoredSpring(bool grav);
		void AnchoredSpringChain(bool grav);
		void AnchoredBungeeChain(bool grav);
};
