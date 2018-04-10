/*
 * SpacecraftController.h
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_SPACECRAFTCONTROLLER_H_
#define CONTROLLERS_SPACECRAFTCONTROLLER_H_

#include "../models/Coordinate.h"
#include "../models/Params.h"
#include "FloorController.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>

class SpacecraftController {
public:
	SpacecraftController();
	virtual ~SpacecraftController();
	void drawSpacecraft();
	void updatePosition(FloorController *floorController);
	void setPowerMotor(bool power);
	void setLeftPower();
	void setRightPower();
private:
//	bool lastDirectionY;
	void setRotate();
	long lastTime;
	float acceleration[2]; // vetor contendo: { 0: componeneteX, 1: componentY }
	float speed[2];
	Coordinate *position;
	long timeLastUpdateMotor;
	long timeLastUpdateDirection;
};

#endif /* CONTROLLERS_SPACECRAFTCONTROLLER_H_ */
