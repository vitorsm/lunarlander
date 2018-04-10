/*
 * Controller.cpp
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#include "Controller.h"

const int LEFT_BUTTON = 100;
const int RIGHT_BUTTON = 102;
const int MOTOR_BUTTON = 32;
const int ESC_BUTTON = 27;

bool Controller::powerMotor = false;
long Controller::lastTimePowerMotor = 0;
long Controller::lastTimePowerDirection = 0;

Controller::Controller() {
	// TODO Auto-generated constructor stub
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

SpacecraftController *Controller::spacecraftController = new SpacecraftController();
FloorController *Controller::floorController = new FloorController();
//int Controller::updateTime = Params::UPDATE_TIME;

void Controller::keyboardNotAsciiCallback(int key, int x, int y) {

	switch(key) {
	case LEFT_BUTTON:
//		cout << "foi para a esquerda" << endl;
		spacecraftController->setLeftPower();
		lastTimePowerDirection = time(0);
		break;
	case RIGHT_BUTTON:
//		cout << "foi para a direita" << endl;
		spacecraftController->setRightPower();
		lastTimePowerDirection = time(0);
		break;
	default:
		break;
	}

}

void Controller::keyboardCallback(unsigned char key, int x, int y) {

	switch(key) {
	case ESC_BUTTON:
		cout << "apertou esc" << endl;
		break;
	case MOTOR_BUTTON:
		powerMotor = true;
		lastTimePowerMotor = time(0);
		break;
	default:
		break;
	}
}

void Controller::drawScene() {
	// Limpa a tela (com a cor definida por glClearColor(r,g,b)) para que
	// possamos desenhar
	glClear(GL_COLOR_BUFFER_BIT);

	spacecraftController->drawSpacecraft();
	floorController->drawFloor();

	// Diz ao OpenGL para colocar o que desenhamos na tela
//	glFlush();
	glutSwapBuffers();
}

void Controller::update(int idx) {

	if (time(0) != lastTimePowerMotor) {
		powerMotor = false;
	}

	spacecraftController->setPowerMotor(powerMotor);
	spacecraftController->updatePosition(floorController);

	glutPostRedisplay();

	glutTimerFunc(Params::UPDATE_TIME, update, 0);
}
