/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#include"ForceRegistry.h"

void ForceRegistry::remove(int index)
{
	delete ActiveForces[index];
	ActiveForces.erase(ActiveForces.begin()+index);
}

void ForceRegistry::add(ForceRegistration* force)
{
	ActiveForces.push_back(force);
}

void ForceRegistry::clear()
{
	/*for(unsigned int i=0;i<ActiveForces.size();i++)
		delete ActiveForces[i];*/
	ActiveForces.clear();
}

void ForceRegistry::updateForces()
{
	for(unsigned int i=0;i<ActiveForces.size();i++)
	{
		if(ActiveForces[i]->Duration<=0)
		{
			remove(i);
			i--;
			continue;
		}

		ActiveForces[i]->Force->updateForce(ActiveForces[i]->Unit);

		if(ActiveForces[i]->Duration<FLT_MAX)
		{
			ActiveForces[i]->Duration-=RigidbodyUnit::Time;

		}
	}
}