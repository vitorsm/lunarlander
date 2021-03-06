/*
 * FloorController.cpp
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#include "FloorController.h"

FloorController::FloorController() {
	this->floor = new Floor();
	this->generateFloor(1);
	this->lastLevel = 1;
}

FloorController::~FloorController() {
	// TODO Auto-generated destructor stub
}

void FloorController::generateFloor(int level) {
	// Verifica se a fase e diferente,
	// Se nao for, o chao sera o mesmo
	// Pq se o jogador morrer em uma fase ele tem que passar ela.
	if (level != this->lastLevel) {
		this->floor->generateFloor(level);
		this->lastLevel = level;
	}
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

	glColor3f(0.62745098, 0.62745098, 0.62745098);

	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(lastCoordinate->getX(), lastCoordinate->getY(), 0);
	glVertex3f(coordinate->getX(), coordinate->getY(), 0);
	glVertex3f(coordinate->getX(), 0, 0);

	glVertex3f(lastCoordinate->getX(), 0, 0);
	glVertex3f(coordinate->getX(), 0, 0);
	glVertex3f(lastCoordinate->getX(), lastCoordinate->getY(), 0);

	glEnd();
}

/***
 * Desenha a pista de pouso
 */
void FloorController::drawRunway() {
	Coordinate *coordinate = this->floor->getRunwayCoordinate();

	glLineWidth(50.0f);
	glBegin(GL_LINES);

	glColor3f(0, 1, 0);

	glVertex3f(coordinate->getX(), coordinate->getY(), 0);
	glVertex3f(coordinate->getX() + Params::RUNWAY_WIDTH, coordinate->getY(), 0);

	glEnd();
}

/***
 * Verifica se a nave esta encostando no chao
 */
bool FloorController::isOnTheFloor(Coordinate *spacecraftPosition) {
	Coordinate *leftCoordinate = new Coordinate(spacecraftPosition->getX() - Params::SPACECRAFT_WIDTH / 2,
			spacecraftPosition->getY() - Params::SPACECRAFT_HEIGHT / 2);

	Coordinate *rightCoordinate = new Coordinate(spacecraftPosition->getX() + Params::SPACECRAFT_WIDTH / 2,
			spacecraftPosition->getY() - Params::SPACECRAFT_HEIGHT / 2);

	vector<Coordinate*> *coordinates = this->floor->getFloorCoordinateByPosition(leftCoordinate, rightCoordinate);

	for (int i = 0; i < coordinates->size() - 1; i++) {

		Coordinate *coordinate = coordinates->at(i);
		Coordinate *nextCoordinate = coordinates->at(i + 1);

		if (leftCoordinate->getY() <= coordinate->getY() ||
				leftCoordinate->getY() <= nextCoordinate->getY() ||
				rightCoordinate->getY() <= coordinate->getY() ||
				rightCoordinate->getY() <= nextCoordinate->getY()) {

			vector <Coordinate*> *coordinatesByLine = this->getBorderCoordinate(coordinate, nextCoordinate, leftCoordinate, rightCoordinate);

			float leftY = this->calculateY(coordinate, nextCoordinate, coordinatesByLine->at(0)->getX());

			if (leftY >= leftCoordinate->getY() + Params::ALPHA_HEIGHT)
				return true;

			float rightY = this->calculateY(coordinate, nextCoordinate, coordinatesByLine->at(1)->getX());

			if (rightY >= rightCoordinate->getY() + Params::ALPHA_HEIGHT)
				return true;
		}

	}

	return false;
}

/***
 * Verifica se a nave esta na pista de pouso
 */
bool FloorController::isOnTheRunway(Coordinate *spacecraftPosition) {
	Coordinate *coordinate = this->floor->getRunwayCoordinate();

	float leftPosition = spacecraftPosition->getX() - Params::SPACECRAFT_WIDTH / 2;
	float rightPosition = spacecraftPosition->getX() + Params::SPACECRAFT_WIDTH / 2;

	return coordinate->getX() <= leftPosition && coordinate->getX() + Params::RUNWAY_WIDTH >= rightPosition;
}

/***
 * Calcula um y, ou seja, a altura, com base na posicao x
 */
float FloorController::calculateY(Coordinate *c1, Coordinate *c2, float x) {
	// y = ax + b
	float a = (c1->getY() - c2->getY()) / (c1->getX() - c2->getX());
	float b = c2->getY() - a * c2->getX();

	return a * x + b;
}

vector<Coordinate*> *FloorController::getBorderCoordinate(Coordinate *c1, Coordinate *c2,
		Coordinate *spacecraftLeftCoordinate, Coordinate *spacecraftRightCoordinate) {

	Coordinate *leftCoordinate = NULL;
	Coordinate *rightCoordinate= NULL;

	if (spacecraftLeftCoordinate->getX() < c1->getX())
		leftCoordinate = c1;
	else
		leftCoordinate = spacecraftLeftCoordinate;

	if (spacecraftRightCoordinate->getX() > c2->getX())
		rightCoordinate = c2;
	else
		rightCoordinate = spacecraftRightCoordinate;

	vector<Coordinate*> *coordinatesRet = new vector<Coordinate*>;
	coordinatesRet->push_back(leftCoordinate);
	coordinatesRet->push_back(rightCoordinate);

	return coordinatesRet;
}
