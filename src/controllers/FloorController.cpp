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

	glPushMatrix();
	glTranslatef(0, 0, 0);
	vector<Coordinate*> *coordinates = this->floor->getCoordinates();

	if (coordinates != NULL) {

		for (int i = 1; i < this->floor->getCoordinatesAmount(); i++) {
			Coordinate *lastCoordinate = coordinates->at(i -1);
			Coordinate *coordinate = coordinates->at(i);
			drawTriangle(lastCoordinate, coordinate);
		}

	}

	this->drawRunway();
	glPopMatrix();
}

void FloorController::drawTriangle(Coordinate *lastCoordinate, Coordinate *coordinate) {
	if (lastCoordinate == NULL) {
		lastCoordinate = new Coordinate(0, 0);
	}

	glColor3f(0, 0, 1);

	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(lastCoordinate->getX(), lastCoordinate->getY(), 0);
	glVertex3f(coordinate->getX(), coordinate->getY(), 0);
	glVertex3f(coordinate->getX(), 0, 0);

	glVertex3f(lastCoordinate->getX(), 0, 0);
	glVertex3f(coordinate->getX(), 0, 0);
	glVertex3f(lastCoordinate->getX(), lastCoordinate->getY(), 0);

	glEnd();
}

void FloorController::drawRunway() {
	Coordinate *coordinate = this->floor->getRunwayCoordinate();

	glLineWidth(50.0f);
	glBegin(GL_LINES);

	glColor3f(0, 1, 0);

	glVertex3f(coordinate->getX(), coordinate->getY(), 0);
	glVertex3f(coordinate->getX() + Params::RUNWAY_WIDTH, coordinate->getY(), 0);

	glEnd();
}

bool FloorController::isOnTheFloor(Coordinate *spacecraftPosition) {
	Coordinate *leftCoordinate = new Coordinate(spacecraftPosition->getX() - Params::SPACECRAFT_WIDTH / 2,
			spacecraftPosition->getY() - Params::SPACECRAFT_HEIGHT / 2);

	Coordinate *rightCoordinate = new Coordinate(spacecraftPosition->getX() + Params::SPACECRAFT_WIDTH / 2,
			spacecraftPosition->getY() - Params::SPACECRAFT_HEIGHT / 2);

	vector<Coordinate*> *coordinates = this->floor->getFloorCoordinateByPosition(leftCoordinate, rightCoordinate);

//	cout << "Qtd: " << coordinates->size() << endl;

	for (int i = 0; i < coordinates->size(); i++) {

		Coordinate *coordinate = coordinates->at(i);
//		cout << "Pegou: " << coordinate->getX() << ", " << coordinate->getY() << endl;

	}

	cout << endl;

	return false;
}

bool FloorController::isOnTheRunway(Coordinate *spacecraftPosition) {
	Coordinate *coordinate = this->floor->getRunwayCoordinate();

	float leftPosition = spacecraftPosition->getX() - Params::SPACECRAFT_WIDTH / 2;
	float rightPosition = spacecraftPosition->getX() + Params::SPACECRAFT_WIDTH / 2;

	cout << "leftPosition: " << leftPosition << ", rightPosition: " << rightPosition << endl;
	cout << "runwayLeft: " << coordinate->getX() << ", runwayRight: " << (coordinate->getX() + Params::RUNWAY_WIDTH) << endl;

	return coordinate->getX() <= leftPosition && coordinate->getX() + Params::RUNWAY_WIDTH >= rightPosition;
}
