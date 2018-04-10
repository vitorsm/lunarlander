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
#include "FloorController.h"
#include "SpacecraftController.h"
#include "../models/Params.h"
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
	static SpacecraftController *spacecraftController;
	static FloorController *floorController;
	static bool powerMotor;
	static long lastTimePowerMotor;
	static long lastTimePowerDirection;
//	static int updateTime;
};

#endif /* CONTROLLERS_CONTROLLER_H_ */
