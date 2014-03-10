/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#include"Game.h"
#include"main.h"
#include<cstring>
#include<string>

void Game::init()
{
	mCameraPos=Vector3(0,0,60);
	mCameraRot=Vector3(0,0,0);
	mTargetIndex=0;
	mFloorHeight=-22.0f;
}

void Game::cleanup()
{
	mConnections.clear();
	for(unsigned int i=0;i<mUnits.size();i++)
		delete mUnits[i];
	mUnits.clear();
	mForceRegistry.clear();
}

void Game::update()
{
	mForceRegistry.updateForces();
	for(unsigned int i=0;i<mUnits.size();i++)
	{
		mUnits[i]->update();
		if(mUnits[i]->getPos().y < mFloorHeight+mUnits[i]->getRadius())
		{
			mUnits[i]->bounce(Vector3(0,1,0),mFloorHeight);
		}
	}
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	//Camera Setup
	glPushMatrix();

	glTranslatef(-(float)mCameraPos.x,-(float)mCameraPos.y,-(float)mCameraPos.z);

	glRotatef((float)mCameraRot.y,0.0f,1.0f,0.0f);
	glRotatef((float)mCameraRot.x,1.0f,0.0f,0.0f);

	Vector3 BUNGEE(1,1,1);
	Vector3 SPRING(0,0,0);
	drawLabel("BUNGEE",Vector3(-12,20,0),BUNGEE);
	drawLabel("SPRING",Vector3(12,20,0),SPRING);
	drawLabel("R: Reset    G: Toggle Gravity    WASDQE: Move Camera    IJKL: Rotate Camera", Vector3(-22,mFloorHeight+3.5f,0),SPRING);
	drawLabel("1: Anchored Bungee  2: Anchored Bungee Chain  3: Bungee Chain",Vector3(-20,mFloorHeight+2,0),SPRING);
	drawLabel("0: Anchored Spring  9: Anchored Spring Chain  8: Spring Chain",Vector3(-20,mFloorHeight+.5f,0),SPRING);

	glColor3f(0.8f,0.8f,0.8f);
	glBegin(GL_QUADS);
		glNormal3f(-500.0f, mFloorHeight, -500.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-500.0f, mFloorHeight, 500.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( 500.0f, mFloorHeight, 500.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 500.0f, mFloorHeight, -500.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-500.0f, mFloorHeight, -500.0f);
    glEnd();

	for(unsigned int i=0;i<mConnections.size();i++)
	{
		glPushMatrix();

		Vector3 end1=mUnits[(unsigned int)mConnections[i].Indices.x]->getPos();
		Vector3 end2=mUnits[(unsigned int)mConnections[i].Indices.y]->getPos();
		glLineWidth(2.0); 
		glColor3f(mConnections[i].Color.x, mConnections[i].Color.y, mConnections[i].Color.z);
		glBegin(GL_LINES);
		glVertex3f(end1.x,end1.y,end1.z);
		glVertex3f(end2.x,end2.y,end2.z);
		glEnd();

		glPopMatrix();
	}

	for(unsigned int i=0;i<mUnits.size();i++)
	{
		mUnits[i]->draw();
	}

	glPopMatrix();
	
	glutSwapBuffers();
}

void Game::drawLabel(string word,Vector3 pos,Vector3 color)
{
	char* buffer=new char[word.length()+1];
	strcpy(buffer, word.c_str());
	int len, i;
	len = (int)strlen(buffer);
	glColor4f(color.x,color.y,color.z,1.0f);
	glRasterPos3f(pos.x,pos.y,pos.z);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]);
	}
}

//find the on-screen radius of a sphere
float Game::checkWorldToScreen(Vector3 pos,float radius)
{
	float screenRadius=-1;

	//find the world coordinates of the sphere after applying camera transformations
	pos-=(mCameraPos+mUnits[mTargetIndex]->getPos());
	pos=Matrix3::RotationX(mCameraRot.x,Degrees)*pos;
	pos=Matrix3::RotationY(mCameraRot.y,Degrees)*pos;
	pos*=-1;
	//if the sphere is behind the camera, ignore it; return -1
	if(pos.z<0)
		return screenRadius;

	//find the top-right and bottom-left coordinates at the depth of the sphere based on the frustum angle
	Vector2 topRight=Vector2(pos.z*tan(gCameraAngle*3.14159265f/(360)),pos.z*tan(gCameraAngle*3.14159265f/(360)));
	Vector2 bottomLeft=Vector2(pos.z*tan(gCameraAngle*-3.14159265f/(360)),pos.z*tan(gCameraAngle*-3.14159265f/(360)));

	//get the screen coordinates of the center of the sphere
	Vector2 centerScreenPos;
	centerScreenPos.y=pos.y/(topRight.y-bottomLeft.y);
	centerScreenPos.y*=(gTopRightScreen.y-gBottomLeftScreen.y);
	centerScreenPos.x=pos.x/(topRight.x-bottomLeft.x);
	centerScreenPos.x*=(gTopRightScreen.x-gBottomLeftScreen.x);

	//if the center is off-screen, ignore it; return -1
	if(centerScreenPos.y<gBottomLeftScreen.y || centerScreenPos.y>gTopRightScreen.y
		|| centerScreenPos.x<gBottomLeftScreen.x || centerScreenPos.x>gTopRightScreen.y)
		return screenRadius;

	//add the radius to y-value of the world-coordinate to get the world coordinate of the top of the sphere 
	pos.y+=radius;
	
	//find the on-screen y-position of the top of the sphere, the x-position is the same as the center
	Vector2 topScreenPos=centerScreenPos;
	topScreenPos.y=pos.y/(topRight.y-bottomLeft.y);
	topScreenPos.y*=(gTopRightScreen.y-gBottomLeftScreen.y);

	//find the on-screen radius of the sphere
	screenRadius=topScreenPos.y-centerScreenPos.y;

	return screenRadius;
}

void Game::moveCamera(Vector3 dir)
{
	mCameraPos+=dir;
}

void Game::rotateCamera(Vector3 rot)
{
	mCameraRot+=rot;
}

void Game::switchTarget(int index)
{
	mTargetIndex=index;
	if((unsigned int)mTargetIndex>=mUnits.size())
		mTargetIndex=mUnits.size()-1;
	else if(mTargetIndex<0)
		mTargetIndex=0;
}

void Game::switchTarget()
{
	mTargetIndex++;
	if((unsigned int)mTargetIndex>=mUnits.size())
		mTargetIndex=0;
}

void Game::centerViewOn(int index)
{
	if((index>4 && index!=9) || index==0)
		mTargetIndex=0;
	switchTarget(0);
	mTargetIndex=index;
}

RigidbodyUnit* Game::addRigidbodyUnit()
{
	RigidbodyUnit* unit=new RigidbodyUnit(Vector3(0,0,0),
			Vector3(),
			Vector3(1,1,1),
			1,
			Vector3((float)(rand()%100)/100,(float)(rand()%100)/100,(float)(rand()%100)/100));
	mUnits.push_back(unit);
	return unit;
}

RigidbodyUnit* Game::addRigidbodyUnit(Vector3 pos,float radius,Vector3 rot,Vector3 scale)
{
	RigidbodyUnit* unit=new RigidbodyUnit(pos,rot,scale,radius,
		Vector3((float)(rand()%100)/100,(float)(rand()%100)/100,(float)(rand()%100)/100));
	mUnits.push_back(unit);
	return unit;
}

void Game::FreeFallBungee(bool grav)
{
	Connection connection;
	Vector3 BUNGEE(1,1,1);
	Vector3 SPRING(0,0,0);
	ForceRegistration* reg;
	Gravity* gravity=new Gravity();

	RigidbodyUnit* unit=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	float unitIndex=(float)mUnits.size()-1;
	RigidbodyUnit* unit2=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	float unit2Index=(float)mUnits.size()-1;

	if(grav)
	{
		reg=new ForceRegistration(unit,gravity);
		mForceRegistry.add(reg);
		reg=new ForceRegistration(unit2,gravity);
		mForceRegistry.add(reg);
	}

	Bungee* bungee=new Bungee(unit2,1.2f,5.0f);
	reg=new ForceRegistration(unit,bungee);
	mForceRegistry.add(reg);
	bungee=new Bungee(unit,1.2f,5.0f);
	reg=new ForceRegistration(unit2,bungee);

	mForceRegistry.add(reg);
	connection.Indices.x=unit2Index;
	connection.Indices.y=unitIndex;
	connection.Color=BUNGEE;
	mConnections.push_back(connection);
	
	unit=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	unitIndex=(float)mUnits.size()-1;

	if(grav)
	{
		reg=new ForceRegistration(unit,gravity);
		mForceRegistry.add(reg);
	}

	bungee=new Bungee(unit2,1.2f,5.0f);
	reg=new ForceRegistration(unit,bungee);
	mForceRegistry.add(reg);
	bungee=new Bungee(unit,1.2f,5.0f);
	reg=new ForceRegistration(unit2,bungee);

	mForceRegistry.add(reg);
	connection.Indices.x=unit2Index;
	connection.Indices.y=unitIndex;
	connection.Color=BUNGEE;
	mConnections.push_back(connection);
}

void Game::FreeFallSpring(bool grav)
{
	Connection connection;
	Vector3 BUNGEE(1,1,1);
	Vector3 SPRING(0,0,0);
	ForceRegistration* reg;
	Gravity* gravity=new Gravity();

	RigidbodyUnit* unit=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	float unitIndex=(float)mUnits.size()-1;
	RigidbodyUnit* unit2=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	float unit2Index=(float)mUnits.size()-1;

	if(grav)
	{
		reg=new ForceRegistration(unit,gravity);
		mForceRegistry.add(reg);
		reg=new ForceRegistration(unit2,gravity);
		mForceRegistry.add(reg);
	}

	Spring* spring=new Spring(unit2,1.2f,5.0f);
	reg=new ForceRegistration(unit,spring);
	mForceRegistry.add(reg);
	spring=new Spring(unit,1.2f,5.0f);
	reg=new ForceRegistration(unit2,spring);
	mForceRegistry.add(reg);

	connection.Indices.x=unit2Index;
	connection.Indices.y=unitIndex;
	connection.Color=SPRING;
	mConnections.push_back(connection);
	
	unit=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	unitIndex=(float)mUnits.size()-1;
	
	if(grav)
	{
		reg=new ForceRegistration(unit,gravity);
		mForceRegistry.add(reg);
	}

	spring=new Spring(unit2,1.2f,5.0f);
	reg=new ForceRegistration(unit,spring);
	mForceRegistry.add(reg);
	spring=new Spring(unit,1.2f,5.0f);
	reg=new ForceRegistration(unit2,spring);
	mForceRegistry.add(reg);

	connection.Indices.x=unit2Index;
	connection.Indices.y=unitIndex;
	connection.Color=SPRING;
	mConnections.push_back(connection);
}

void Game::AnchoredBungee(bool grav)
{
	Connection connection;
	Vector3 BUNGEE(1,1,1);
	Vector3 SPRING(0,0,0);
	ForceRegistration* reg;
	Gravity* gravity=new Gravity();

	float anchorX=-12;
	if(grav)
		anchorX=-15;

	RigidbodyUnit* anchor=addRigidbodyUnit(Vector3(anchorX,10,0),1);
	float anchorIndex=(float)mUnits.size()-1;
	RigidbodyUnit* unit=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	float unitIndex=(float)mUnits.size()-1;

	if(grav)
	{
		reg=new ForceRegistration(unit,gravity);
		mForceRegistry.add(reg);
	}

	Bungee* bungee=new Bungee(anchor,1.2f,5.0f);
	reg=new ForceRegistration(unit,bungee);
	mForceRegistry.add(reg);

	connection.Indices.x=anchorIndex;
	connection.Indices.y=unitIndex;
	connection.Color=BUNGEE;
	mConnections.push_back(connection);
}

void Game::AnchoredSpring(bool grav)
{
	Connection connection;
	Vector3 BUNGEE(1,1,1);
	Vector3 SPRING(0,0,0);
	ForceRegistration* reg;
	Gravity* gravity=new Gravity();

	float anchorX=12;
	if(grav)
		anchorX=15;

	RigidbodyUnit* anchor2=addRigidbodyUnit(Vector3(anchorX,10,0),1);
	float anchor2Index=(float)mUnits.size()-1;
	RigidbodyUnit* unit2=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	float unit2Index=(float)mUnits.size()-1;
	
	if(grav)
	{
		reg=new ForceRegistration(unit2,gravity);
		mForceRegistry.add(reg);
	}
	
	Spring* spring=new Spring(anchor2,1.2f,5.0f);
	reg=new ForceRegistration(unit2,spring);
	mForceRegistry.add(reg);

	connection.Indices.x=anchor2Index;
	connection.Indices.y=unit2Index;
	connection.Color=SPRING;
	mConnections.push_back(connection);
}

void Game::AnchoredBungeeChain(bool grav)
{
	Connection connection;
	Vector3 BUNGEE(1,1,1);
	Vector3 SPRING(0,0,0);
	ForceRegistration* reg;
	Gravity* gravity=new Gravity();

	float anchorX=-6;
	if(grav)
		anchorX=-9;
	
	RigidbodyUnit* anchor2=addRigidbodyUnit(Vector3(anchorX,10,0),1);
	float anchor2Index=(float)mUnits.size()-1;
	RigidbodyUnit*unit2=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	float unit2Index=(float)mUnits.size()-1;
	RigidbodyUnit*unit=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	float unitIndex=(float)mUnits.size()-1;

	if(grav)
	{
		reg=new ForceRegistration(unit,gravity);
		mForceRegistry.add(reg);
		reg=new ForceRegistration(unit2,gravity);
		mForceRegistry.add(reg);
	}
	
	Bungee* spring=new Bungee(anchor2,2.0f,3.0f);
	reg=new ForceRegistration(unit2,spring);
	mForceRegistry.add(reg);

	connection.Indices.x=anchor2Index;
	connection.Indices.y=unit2Index;
	connection.Color=BUNGEE;
	mConnections.push_back(connection);

	spring=new Bungee(unit2,2.0f,1.0f);
	reg=new ForceRegistration(unit,spring);
	mForceRegistry.add(reg);
	spring=new Bungee(unit,2.0f,1.0f);
	reg=new ForceRegistration(unit2,spring);
	mForceRegistry.add(reg);

	connection.Indices.x=unitIndex;
	connection.Indices.y=unit2Index;
	connection.Color=BUNGEE;
	mConnections.push_back(connection);
}

void Game::AnchoredSpringChain(bool grav)
{
	Connection connection;
	Vector3 BUNGEE(1,1,1);
	Vector3 SPRING(0,0,0);
	ForceRegistration* reg;
	Gravity* gravity=new Gravity();

	float anchorX=6;
	if(grav)
		anchorX=9;
	
	RigidbodyUnit* anchor2=addRigidbodyUnit(Vector3(anchorX,10,0),1);
	float anchor2Index=(float)mUnits.size()-1;
	RigidbodyUnit*unit2=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	float unit2Index=(float)mUnits.size()-1;
	RigidbodyUnit*unit=addRigidbodyUnit(Vector3((float)(rand()%40-20),(float)(rand()%40-20),(float)(rand()%30-15)),1);
	float unitIndex=(float)mUnits.size()-1;

	if(grav)
	{
		reg=new ForceRegistration(unit,gravity);
		mForceRegistry.add(reg);
		reg=new ForceRegistration(unit2,gravity);
		mForceRegistry.add(reg);
	}
	
	Spring* spring=new Spring(anchor2,2.0f,3.0f);
	reg=new ForceRegistration(unit2,spring);
	mForceRegistry.add(reg);

	connection.Indices.x=anchor2Index;
	connection.Indices.y=unit2Index;
	connection.Color=SPRING;
	mConnections.push_back(connection);

	spring=new Spring(unit,2.0f,1.0f);
	reg=new ForceRegistration(unit2,spring);
	mForceRegistry.add(reg);
	spring=new Spring(unit2,2.0f,1.0f);
	reg=new ForceRegistration(unit,spring);
	mForceRegistry.add(reg);

	connection.Indices.x=unitIndex;
	connection.Indices.y=unit2Index;
	connection.Color=SPRING;
	mConnections.push_back(connection);
}