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
const int EXIT_BUTTON = 27;
const int RESTART_BUTTON = 'r';

bool Controller::powerMotor = false;
long Controller::lastTimePowerMotor = 0;
long Controller::lastTimePowerDirection = 0;

Controller::Controller() {
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

BackgroundController	*Controller::backgroundController = new BackgroundController();
MenuController 			*Controller::menuController = new MenuController();
FloorController 		*Controller::floorController = new FloorController();
SpacecraftController 	*Controller::spacecraftController = new SpacecraftController(floorController);
HUDController 			*Controller::hudController = new HUDController();
PauseController			*Controller::pauseController = new PauseController();
LevelController			*Controller::levelController = new LevelController();
InstructionsController	*Controller::instructionsController = new InstructionsController();
ConfirmController		*Controller::confirmController = new ConfirmController();

int Controller::level = 1;

int Controller::lifes = Params::INITIAL_LIFES;
int Controller::scores = 0;

bool Controller::pause = false;
bool Controller::menu = true;
bool Controller::startLevel = false;
bool Controller::gameOver = false;
bool Controller::instructions = false;
bool Controller::restart = false;
bool Controller::exitGame = false;

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
		powerMotor = true;
		lastTimePowerMotor = time(0);
		if (restart || exitGame) confirmController->setUpMenu();
		if (menu) menuController->setUpMenu();
		if (startLevel) levelController->setUpMenu();
		if (pause) pauseController->setUpMenu();
		break;
	case GLUT_KEY_DOWN:
		if (restart || exitGame) confirmController->setDownMenu();
		if (menu) menuController->setDownMenu();
		if (startLevel)levelController->setDownMenu();
		if (pause) pauseController->setDownMenu();
		break;
	default:
		break;
	}

}

void Controller::keyboardCallback(unsigned char key, int x, int y) {
	int value = key;

	switch(key) {
	case MOTOR_BUTTON:
		powerMotor = true;
		lastTimePowerMotor = time(0);
//		spacecraftController->setPowerMotor();
		break;
	case PAUSE_BUTTON:
		pause = !pause;
		break;
	case ENTER_BUTTON:
		clickMenu();
		break;
	case RESTART_BUTTON:
		restart = true;
		confirmController->setMessage("Deseja reiniciar o jogo");
		break;
	case EXIT_BUTTON:
		exitGame = true;
		confirmController->setMessage("Deseja sair do jogo");
		break;
	default:
		break;
	}
}

void Controller::drawScene() {

	glClear(GL_COLOR_BUFFER_BIT);

	if (menu) {
		menuController->drawMenu();
	} else if (instructions) {
		instructionsController->drawInstructions();
	} else {

		backgroundController->drawBackground();
		spacecraftController->drawSpacecraft();
		floorController->drawFloor();
		hudController->drawHUD();

		if (restart || exitGame) {
			confirmController->drawConfirm();
		} else if (startLevel) {
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
		if (!pause && !startLevel && !restart && !exitGame) {
//			cout << "power motor: " << powerMotor << endl;
			if (time(0) != lastTimePowerMotor) {
				powerMotor = false;
			}


			spacecraftController->setPowerMotor(powerMotor);
			spacecraftController->updatePosition();

			float *speed = spacecraftController->getSpeed();
			hudController->updateData(speed[1], spacecraftController->getSpacecraftPosition()->getY(),
					speed[0], lifes, level, spacecraftController->getFuel());

			levelController->setMaxSpeed(speed[1] < Params::MAX_SPEED_LANDER,
										speed[0] < -Params::MAX_ROTATION_LANDER || speed[0] > Params::MAX_ROTATION_LANDER);

			Coordinate *spacecraftPosition = spacecraftController->getSpacecraftPosition();
			if (floorController->isOnTheFloor(spacecraftPosition)) {
				if (floorController->isOnTheRunway(spacecraftPosition) &&
						(speed[0] > -Params::MAX_ROTATION_LANDER && speed[0] < Params::MAX_ROTATION_LANDER &&
								speed[1] > Params::MAX_SPEED_LANDER)) {
					level++;
					calculateScore();
					floorController->generateFloor(level);
					levelController->setLevel(level);
					startLevel = true;
				} else {
					if (!gameOver) {
						// chama a funcao q perde
						lifes--;
						spacecraftController->setExplosion(true);
						levelController->setLastLevel(lifes);
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
			level = 1;
			lifes = Params::INITIAL_LIFES;
			initLevel();
			menu = false;
			cout << "clicou no start game" << endl;
		} else if (selected == MenuController::INSTRUCTION_MENU_ITEM) {
			instructions = true;
			menu = false;
		} else if (selected == MenuController::EXIT_MENU_ITEM) {
			cout << "vai fechar o jogo" << endl;
			exit(0);
		}
	} else if (restart) {
		restart = false;
		if (confirmController->getSelectedMenu() == ConfirmController::YES_MENU_ITEM)
			initLevel();
	} else if (exitGame) {
		exitGame = false;
		if (confirmController->getSelectedMenu() == ConfirmController::YES_MENU_ITEM)
			cout << "vai fechar o jogo" << endl;
			exit(0);
	} else if (startLevel) {
		selected = levelController->getSelectedMenu();

		if (selected == LevelController::CONTINUE_MENU_ITEM) {
//			lifes = Params::INITIAL_LIFES;
//			level = 1;
			startLevel = false;
			initLevel();
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
	} else if (instructions) {
		menu = true;
		instructions = false;
	}

}

void Controller::initLevel() {
	floorController->generateFloor(level);
	spacecraftController->setInitialPosition();
	spacecraftController->setInitialFuel(level);
}

void Controller::calculateScore() {
	float score = level * 3;
	if (spacecraftController->getSpentFuel() > 0) {
		score += Params::INITIAL_FUEL / spacecraftController->getSpentFuel();
	}
	float rotation = spacecraftController->getSpeed()[0];
	if (rotation < 0) rotation = -rotation;

	score -= 3 * rotation;

	scores += score;
	levelController->setScores(score, scores);
}
