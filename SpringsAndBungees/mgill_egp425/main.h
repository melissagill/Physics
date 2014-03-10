/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#pragma once
#include<stdlib.h>
#include<GL/glut.h>
#include<iostream>
#include<time.h>
#include"Vector2.h"

using namespace std;

void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void cameraControls(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void display(void);
void update(void);

extern Vector2 gWindowSize;
extern float gCameraAngle;
extern Vector2 gTopRightScreen;
extern Vector2 gBottomLeftScreen;