/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include"Gravity.h"

void Gravity::updateForce(RigidbodyUnit* unit)
{
	unit->addForce(RigidbodyUnit::Gravity);
}