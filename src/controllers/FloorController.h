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
	void generateFloor(int level);
	bool isOnTheFloor(Coordinate *spacecraftPosition);
	bool isOnTheRunway(Coordinate *spacecraftPosition);
private:
	int lastLevel;
	Floor *floor;
	void drawTriangle(Coordinate *lastCoordinate, Coordinate *coordinate);
	void drawRunway();
	float calculateY(Coordinate *c1, Coordinate *c2, float x);
	vector<Coordinate*> *getBorderCoordinate(Coordinate *c1, Coordinate *c2, Coordinate *spacecraftLeftCoordinate, Coordinate *spacecraftRightCoordinate);
};

#endif /* CONTROLLERS_FLOORCONTROLLER_H_ */
