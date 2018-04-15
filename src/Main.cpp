//============================================================================
// Name        : lunarlander.cpp
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
//	glOrtho(0.0, (double) Params::SCREEN_WIDTH, 0.0, (double) Params::SCREEN_HEIGHT, -1, 1);
	glOrtho(0.0, (double) 100, 0.0, (double) 100, -1, 1);
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

void desenhaCena(void)
{
	// Limpa a tela (com a cor definida por glClearColor(r,g,b)) para que
	// possamos desenhar
	glClear(GL_COLOR_BUFFER_BIT);

	// Começa a usar a cor verde
	glColor3f(0, 1, 0);

	// Começa a desenhar um polígono com os vértices especificados
	glBegin(GL_POLYGON);
		glVertex3f(20, 20, 0);
		glVertex3f(80, 20, 0);
		glVertex3f(80, 80, 0);
		glVertex3f(20, 80, 0);
	glEnd();

	// Diz ao OpenGL para colocar o que desenhamos na tela
	glutSwapBuffers();
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
//	glutDisplayFunc(desenhaCena);
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
