//============================================================================
// Name        : Main.cpp
// Author      : Vitor Moreira
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "controllers/Controller.h"
#include "models/Params.h"

using namespace std;


void setGlOrtho() {
	glOrtho(0.0, (double) Params::SCREEN_WIDTH, 0.0, (double) Params::SCREEN_HEIGHT, -1, 1);
}

void setup() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	setGlOrtho();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setGlOrtho();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void glutInitScreen(int *argc, char **argv) {
	glutInit(argc, argv);

	glutInitContextVersion(1, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 640);
	glutInitWindowPosition(100, 40);

	glutCreateWindow("Lunar Lander");

	glutDisplayFunc(Controller::drawScene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Controller::keyboardCallback);
	glutSpecialFunc(Controller::keyboardNotAsciiCallback);


	glutTimerFunc(Params::UPDATE_TIME, Controller::update, 0);

	setup();

	glutMainLoop();
}

int main(int argc, char **argv) {

	glutInitScreen(&argc, argv);

	return 0;
}
