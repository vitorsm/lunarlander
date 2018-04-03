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

class Controller {
public:
	Controller();
	virtual ~Controller();
	static void drawScene();
private:
	static FloorController *floorController;
};

#endif /* CONTROLLERS_CONTROLLER_H_ */
