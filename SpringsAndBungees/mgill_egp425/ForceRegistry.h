/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include"ForceRegistration.h"
#include<vector>

using namespace std;

class ForceRegistry
{
	private:
		vector<ForceRegistration*> ActiveForces;

		void remove(int index);

	public:
		ForceRegistry(){};
		~ForceRegistry(){};

		void add(ForceRegistration* force);
		void clear();
		void updateForces();
};