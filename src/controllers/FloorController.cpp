/*
 * FloorController.cpp
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#include "FloorController.h"

FloorController::FloorController() {
	this->floor = new Floor();
	this->generateFloor();
}

FloorController::~FloorController() {
	// TODO Auto-generated destructor stub
}

void FloorController::generateFloor() {
	this->floor->generateFloor(5);
	this->floor->printAllCoordinates();
}

void FloorController::drawFloor() {

	vector<Coordinate*> *coordinates = this->floor->getCoordinates();

	glColor3f(0, 1, 0);

//	glBegin(GL_LINE_STRIP);
	glBegin(GL_POLYGON);
	if (coordinates != NULL) {

		for (int i = 0; i < this->floor->getCoordinatesAmount(); i++) {
			Coordinate *coordinate = coordinates->at(i);
			cout << "Vai desenhar o vertice (" << coordinate->getX() << ", " << coordinate->getY() << ")" << endl;
			glVertex3f(coordinate->getX(), coordinate->getY(), 0);
		}

	}
	glEnd();
}
