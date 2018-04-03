/*
 * FloorController.h
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_FLOORCONTROLLER_H_
#define CONTROLLERS_FLOORCONTROLLER_H_

#include "../models/Floor.h"
#include <vector>
#include "../models/Coordinate.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

class FloorController {
public:
	FloorController();
	virtual ~FloorController();
	void drawFloor();
	void generateFloor();

private:
	Floor *floor;

};

#endif /* CONTROLLERS_FLOORCONTROLLER_H_ */