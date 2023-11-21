#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "../../include/point.h"
#include "../../include/engine/world.h"
#include "../../include/tinyxml2/tinyxml2.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include </opt/homebrew/opt/devil/include/IL/il.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#endif


using namespace tinyxml2;
using namespace std;

World world;
int window;
int timebase = 0, frames = 0;
int group;
bool axis = true;
bool debug = false;
bool viewFrustumCulling = false;


void showFPS(int triangles){
	frames++;
    int fps;
    int time = glutGet(GLUT_ELAPSED_TIME);

    if (time - timebase > 1000){
        fps = frames*1000.0 / (time-timebase);
        timebase = time; frames = 0;
        char title[45];
        sprintf(title, "CG@G48 | %d FPS | %d Triangles", fps, triangles);
        glutSetWindowTitle(title);
    }
}


void renderText() {
	// save projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// set projection so that coordinates match window pixels
	gluOrtho2D(0, world.window.width, world.window.height, 0);
	glMatrixMode(GL_MODELVIEW);

	// disable depth test (assuming text is written in the end)
	glDisable(GL_DEPTH_TEST);

	// set modelview matrix
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2d(10, 20); // text position in pixels

	// render text
	char text[100];
	sprintf(text, "Position: (%f, %f, %f)   |   LookAt: (%f, %f, %f)", world.camera.position.x, world.camera.position.y, world.camera.position.z, 
																       world.camera.lookAt.x, world.camera.lookAt.y, world.camera.lookAt.z);

	for (char *c = text; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

	// Restore matrices and reenable depth test
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}


void showAxis(){
	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1500.0f, 0.0f, 0.0f);
	glVertex3f(1500.0f, 0.0f, 0.0f);
	
	// Y axis in green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1500.0f, 0.0f);
	glVertex3f(0.0f, 1500.0f, 0.0f);
	
	// Z axis in blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -1500.0f);
	glVertex3f(0.0f, 0.0f, 1500.0f);

	glColor3f(255.0f, 255.0f, 255.0f);
		
	glEnd();

	glEnable(GL_LIGHTING);
}


void changeSize(int w, int h){

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	Projection projection = world.camera.projection;

	gluPerspective(projection.fov, ratio, projection.near, projection.far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void){
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	
	if(world.camera.mode == EXPLORER){
		Point *p = world.getGroupPosition(world.camera.groupIndex);
		world.camera.updateExplorer(Point(p->x, p->y, p->z));
	}

	Camera camera = world.camera;

	gluLookAt(camera.position.x, camera.position.y, camera.position.z,
			  camera.lookAt.x  , camera.lookAt.y  , camera.lookAt.z  ,
			  camera.up.x      , camera.up.y      , camera.up.z       );

	// axis drawing
	if (axis) showAxis();

	// lights
	world.applyLights();

	// drawing instructions
	int nIndexes = 0;
	if (viewFrustumCulling) {
		vector<FrustumPlane> planes = world.computeFrustumPlanes();
		nIndexes = world.drawModels(planes);
	}
	else {
		nIndexes = world.drawModels();
	}

	// FPS and triangles
	showFPS(nIndexes / 3);
	if (debug){
		renderText();
	}

	//  End of frame
	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y){
	switch(key){
		case 27: // ESCAPE
			glutDestroyWindow(window);
			exit(0);
			break;
		default:
			world.camera.processNormalKeys(key);
			break;
	}

	glutPostRedisplay();
}


void processSpecialKeys(int key, int x, int y){	
	switch(key){
		default:
			world.camera.processSpecialKeys(key);
			break;
	}

	glutPostRedisplay();
}


void processMouseButtons(int button, int state, int x, int y){
	world.camera.processMouseButtons(button);
}


void processMouseMotion(int x, int y){
	world.camera.processMouseMotion(x, y);
}


void explorerChoice(int choice) {
	Point p;
	if(choice == 0){
		int index = world.getClosestGroupIndex();
		if (index != -1){
			world.camera.groupIndex = index;
			world.camera.mode = EXPLORER;
			world.camera.beta = 0;
		}
	}
	else{
		world.camera.groupIndex = choice-1;
		world.camera.mode = EXPLORER;
		world.camera.beta = 0;
	}
}


void menuCamChoice(int choice){
    switch (choice) {
        case 0:
            world.camera.mode = STATIC;
            break;
        case 1:
            world.camera.mode = FPS;
			world.camera.beta = 0;
			world.camera.firstTime = true;
            break;
        default:
            break;
    }
}


void modeChoice(int choice){
	switch (choice) {
		case 0:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 1:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case 2:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		default:
			break;
	}
}


void menuChoice(int choice) {
	switch (choice) {
		case 0:
			axis ^= 1;
			break;
		case 1:
			debug ^= 1;
			break;
		case 2:
			viewFrustumCulling ^= 1;
			break;
	}
}


void visualizationMenu(){
	int explorerMenu = glutCreateMenu(explorerChoice);
	glutAddMenuEntry("Closest group", 0);
	// Meter menus
	vector<char *> labels = world.getLabels();
	for (int i=0; i < labels.size(); i++) {
		if(labels[i]){
			char *label = labels[i];
			glutAddMenuEntry(label, i+1);
		}
	}

	int cameraMenu = glutCreateMenu(menuCamChoice);
	glutAddMenuEntry("Static Camera", 0);
	glutAddSubMenu("Explorer Camera", explorerMenu);
	glutAddMenuEntry("FPS Camera", 1);

	int modeMenu = glutCreateMenu(modeChoice);
	glutAddMenuEntry("Lines", 0);
	glutAddMenuEntry("Fill", 1);
	glutAddMenuEntry("Points", 2);

	glutCreateMenu(menuChoice);
	glutAddMenuEntry("Toggle Axis", 0);
	glutAddMenuEntry("Toggle Debug", 1);
	glutAddMenuEntry("Toggle View Frustum Culling", 2);

	glutAddSubMenu("Camera", cameraMenu);
	glutAddSubMenu("Mode", modeMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void init() {
	ilInit();
	ilEnable(IL_ORIGIN_SET); 
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_RESCALE_NORMAL);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}


int main(int argc, char **argv) {
	if (argc == 1 || (argc == 2 && strcmp(argv[1], "--help") == 0)){
        cout << "-------------------------------------------------HELP-----------------------------------------------" << endl;
        cout << "USAGE: ./engine {FILEPATH}.xml" << endl;
		cout << "note: the filepath must be relative to 'build' folder" << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "OPEN MENU: mouse right button" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "FPS CAMERA MODE      | MOVE: W, A, S, D      | POINT: MOUSE             | INCREASE SPEED: hold SHIFT" << endl;
		cout << "EXPLORER CAMERA MODE | MOVE: ARROWS or MOUSE | ZOOM: +/- or MOUSE WHEEL" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;

		return 0;
    }

	// init GLUT and the window
	world = World(argv[1]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(world.window.width, world.window.height);
	window = glutCreateWindow("CG@DI-UM");
		
	// Required callback registry 
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
	// registration of the keyboard callbacks
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseButtons);
	glutPassiveMotionFunc(processMouseMotion);

	// init GLEW
	#ifndef __APPLE__
		glewInit();
	#endif

	//  OpenGL settings
	init();

	world.setupLights();
	world.loadModels();

	timebase = glutGet(GLUT_ELAPSED_TIME);

	visualizationMenu();

	// GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
