/*
 * Controller.h
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_CONTROLLER_H_
#define CONTROLLERS_CONTROLLER_H_

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "../models/Params.h"
#include "FloorController.h"
#include "SpacecraftController.h"
#include "HUDController.h"
#include "MenuController.h"
#include "PauseController.h"
#include "LevelController.h"
#include "BackgroundController.h"
#include "InstructionsController.h"
#include "ConfirmController.h"

#include <time.h>

class Controller {
public:
	Controller();
	virtual ~Controller();
	static void drawScene();
	static void update(int idx);
	static void keyboardCallback(unsigned char key, int x, int y);
	static void keyboardNotAsciiCallback(int key, int x, int y);

private:
	static int level;
	static int lifes;
	static int scores;

	static void calculateScore();

	static ConfirmController *confirmController;
	static BackgroundController *backgroundController;
	static SpacecraftController *spacecraftController;
	static FloorController *floorController;
	static HUDController *hudController;
	static MenuController *menuController;
	static PauseController *pauseController;
	static LevelController *levelController;
	static InstructionsController *instructionsController;

	static void initLevel();

	static bool menu;
	static bool instructions;
	static bool powerMotor;
	static long lastTimePowerMotor;
	static long lastTimePowerDirection;
	static bool pause;
	static bool startLevel;
	static bool gameOver;
	static bool restart;
	static bool exitGame;

	static void clickMenu();
//	static int updateTime;
};

#endif /* CONTROLLERS_CONTROLLER_H_ */
