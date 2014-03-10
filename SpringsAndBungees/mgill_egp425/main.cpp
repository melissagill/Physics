/***********************
Melissa Gill
Spring 2014
Physics System
************************/
#include"main.h"
#include"Game.h"

Game gGame;
Vector2 gWindowSize=Vector2(700,700);
float gCameraAngle=45;
Vector2 gTopRightScreen=Vector2(1.0f*tan(gCameraAngle*3.14159265f/(360)),1.0f*tan(gCameraAngle*3.14159265f/(360)));
Vector2 gBottomLeftScreen=Vector2(1.0f*tan(gCameraAngle*-3.14159265f/(360)),1.0f*tan(gCameraAngle*-3.14159265f/(360)));

float moveSpeed=1;
float speed=2.1f;
bool rotCam=true;
bool rotUnit=true;

bool grav=true;

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	gGame.init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA| GLUT_DEPTH);
	glutInitWindowSize((int)gWindowSize.x,(int)gWindowSize.y);
	glutCreateWindow("GLUT Test");
	glClearColor(.15f,.15f,.15f,1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(gCameraAngle,gWindowSize.x/gWindowSize.y,1.0,1000.0);

	glMatrixMode(GL_MODELVIEW);

	glEnable (GL_DEPTH_TEST);
	
	glutKeyboardFunc(&keyboard);
	glutKeyboardUpFunc(&keyboardUp);
	glutSpecialFunc(&cameraControls);
	//glutMouseFunc(&mouse);
	glutIdleFunc(&update);
	glutMainLoop();

	gGame.cleanup();
	return EXIT_SUCCESS;
}

void update(void)
{
	gGame.update();
	gGame.draw();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '\x1B':
			exit(EXIT_SUCCESS);
			break;
		case 'a':
			gGame.moveCamera(Vector3(-1*moveSpeed,0,0));
			break;
		case 'd':
			gGame.moveCamera(Vector3(moveSpeed,0,0));
			break;
		case 'w':
			gGame.moveCamera(Vector3(0,moveSpeed,0));
			break;
		case 's':
			gGame.moveCamera(Vector3(0,-1*moveSpeed,0));
			break;


		case 'j':
			gGame.rotateCamera(Vector3(0,-1*speed,0));
			break;
		case 'l':
			gGame.rotateCamera(Vector3(0,speed,0));
			break;
		case 'i':
			gGame.rotateCamera(Vector3(-1*speed,0,0));
			break;
		case 'k':
			gGame.rotateCamera(Vector3(speed,0,0));
			break;
		case 'q':
			gGame.moveCamera(Vector3(0,0,moveSpeed));
			break;
		case 'e':
			gGame.moveCamera(Vector3(0,0,-1*moveSpeed));
			break;

		/*case 'x':
			gGame.shoot();
			break;*/
	}
}

void cameraControls(int key, int x, int y)
{
	switch(key)
	{

		case GLUT_KEY_LEFT:
			gGame.moveCamera(Vector3(-1*speed,0,0));
			break;
		case GLUT_KEY_RIGHT:
			gGame.moveCamera(Vector3(speed,0,0));
			break;
		case GLUT_KEY_PAGE_DOWN:
			gGame.moveCamera(Vector3(0,0,speed));
			break;
		case GLUT_KEY_END:
			gGame.moveCamera(Vector3(0,0,-1*speed));
			break;
	}
}

void keyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'r':
			gGame.cleanup();
			gGame.init();
			break;
		case 't':
			gGame.switchTarget();
			break;
		case 'g':
			grav=!grav;
			break;
		case '1':
			gGame.AnchoredBungee(grav);
			break;
		case '2':
			gGame.AnchoredBungeeChain(grav);
			break;
		case '3':
			gGame.FreeFallBungee(grav);
			break;
		case '8':
			gGame.FreeFallSpring(grav);
			break;
		case '9':
			gGame.AnchoredSpringChain(grav);
			break;
		case '0':
			gGame.AnchoredSpring(grav);
			break;
	}
}