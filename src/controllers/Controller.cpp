/*
 * Controller.cpp
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#include "Controller.h"

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

FloorController *Controller::floorController = new FloorController();

void Controller::drawScene() {
	// Limpa a tela (com a cor definida por glClearColor(r,g,b)) para que
	// possamos desenhar
	glClear(GL_COLOR_BUFFER_BIT);

	floorController->drawFloor();

	// Diz ao OpenGL para colocar o que desenhamos na tela
	glFlush();
}
