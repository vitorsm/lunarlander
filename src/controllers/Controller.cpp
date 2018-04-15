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
const int PAUSE_BUTTON = 'p';
const int ENTER_BUTTON = 13;

bool Controller::powerMotor = false;
long Controller::lastTimePowerMotor = 0;
long Controller::lastTimePowerDirection = 0;

Controller::Controller() {
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

MenuController 			*Controller::menuController = new MenuController();
FloorController 		*Controller::floorController = new FloorController();
SpacecraftController 	*Controller::spacecraftController = new SpacecraftController(floorController);
HUDController 			*Controller::hudController = new HUDController();
PauseController			*Controller::pauseController = new PauseController();
LevelController			*Controller::levelController = new LevelController();

int Controller::level = 1;

bool Controller::pause = false;
bool Controller::menu = true;
bool Controller::startLevel = false;
bool Controller::gameOver = false;

void Controller::keyboardNotAsciiCallback(int key, int x, int y) {

	switch(key) {
	case GLUT_KEY_LEFT:
//		cout << "foi para a esquerda" << endl;
		spacecraftController->setLeftPower();
		lastTimePowerDirection = time(0);
		break;
	case GLUT_KEY_RIGHT:
//		cout << "foi para a direita" << endl;
		spacecraftController->setRightPower();
		lastTimePowerDirection = time(0);
		break;
	case GLUT_KEY_UP:
		menuController->setUpMenu();
		levelController->setUpMenu();
		pauseController->setUpMenu();
		break;
	case GLUT_KEY_DOWN:
		menuController->setDownMenu();
		levelController->setDownMenu();
		pauseController->setDownMenu();
		break;
	default:
		break;
	}

}

void Controller::keyboardCallback(unsigned char key, int x, int y) {
	int value = key;

	switch(key) {
	case ESC_BUTTON:
		cout << "apertou esc" << endl;
		break;
	case MOTOR_BUTTON:
//		powerMotor = true;
//		lastTimePowerMotor = time(0);
		spacecraftController->setPowerMotor();
		break;
	case PAUSE_BUTTON:
		pause = !pause;
		break;
	case ENTER_BUTTON:
		clickMenu();
		break;
	default:
		break;
	}
}

void Controller::drawScene() {

	if (menu) {
		menuController->drawMenu();
	} else {
		glClear(GL_COLOR_BUFFER_BIT);

		spacecraftController->drawSpacecraft();
		floorController->drawFloor();
		hudController->drawHUD();

		if (startLevel) {
			levelController->drawLevel();
		} else if (pause) {
			pauseController->drawPause();
		}
	}


	glutSwapBuffers();
}

void Controller::update(int idx) {

	if (menu) {

	} else {
		if (!pause && !startLevel) {
			if (time(0) != lastTimePowerMotor) {
				powerMotor = false;
			}

			spacecraftController->setPowerMotor(powerMotor);
			spacecraftController->updatePosition();

			float *speed = spacecraftController->getSpeed();
			hudController->updateData(speed[1], spacecraftController->getSpacecraftPosition()->getY(), speed[0]);

			Coordinate *spacecraftPosition = spacecraftController->getSpacecraftPosition();
			if (floorController->isOnTheFloor(spacecraftPosition)) {
				if (floorController->isOnTheRunway(spacecraftPosition)) {
					// chama a funcao q ganha a fase
					level++;
					floorController->generateFloor(level);
					levelController->setLevel(level);
					startLevel = true;
				} else {
					if (!gameOver) {
						// chama a funcao q perde
						spacecraftController->setExplosion(true);
						levelController->setLastLevel();
						gameOver = true;
					} else {
//						cout << spacecraftController->getCountExplosionImage() << " >= " << spacecraftController->getAmountExplosionImage();
						if (spacecraftController->getCountExplosionImage() >= spacecraftController->getAmountExplosionImage()) {
							// coloca a parada de iniciar a fase
							gameOver = false;
							startLevel = true;
						}

					}

				}
			}
		}
	}


	glutPostRedisplay();
	glutTimerFunc(Params::UPDATE_TIME, update, 0);

}

void Controller::clickMenu() {
	int selected = 0;

	if (menu) {
		selected = menuController->getSelectedMenu();

		if (selected == MenuController::START_GAME_MENU_ITEM) {
			initLevel();
			menu = false;
			cout << "clicou no start game" << endl;
		} else if (selected == MenuController::INSTRUCTION_MENU_ITEM) {

		} else if (selected == MenuController::EXIT_MENU_ITEM) {
			exit(0);
		}
	} else if (startLevel) {
		selected = levelController->getSelectedMenu();
		cout << "startLevel = " << selected << endl;

		if (selected == LevelController::CONTINUE_MENU_ITEM) {
			initLevel();
			startLevel = false;
		} else if (selected == LevelController::MENU_MENU_ITEM) {
			startLevel = false;
			menu = true;
		}
	} else if (pause) {
		selected = pauseController->getSelectedMenu();

		if (selected == PauseController::RESUME_GAME_MENU_ITEM) {
			pause = false;
		} else if (selected == PauseController::RESTART_GAME_MENU_ITEM) {
			initLevel();
			pause = false;
		} else if (selected == PauseController::MENU_MENU_ITEM) {
			menu = true;
			pause = false;
		}
	}

}

void Controller::initLevel() {
	cout << "dentro da funcao" << endl;
	floorController->generateFloor(level);
	spacecraftController->setInitialPosition();
}
