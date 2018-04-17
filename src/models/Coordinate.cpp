/*
 * Coordinate.cpp
 *
 *  Created on: 2 de abr de 2018
 *      Author: vitor
 */

#include "Coordinate.h"

Coordinate::Coordinate(float x, float y) {
	// TODO Auto-generated constructor stub
	this->x = x;
	this->y = y;
}

Coordinate::~Coordinate() {
	// TODO Auto-generated destructor stub
}

float Coordinate::getX() {
	return this->x;
}

float Coordinate::getY() {
	return this->y;
}

void Coordinate::print() {
	cout << "(" << this->x << ", " << this->y << ")";
}

void Coordinate::updateBySpeed(float *speed, long time, bool powerMotor) {

	if ((this->x + speed[0] >= 0 && this->x + speed[0] <= Params::SCREEN_WIDTH))
		this->x += speed[0];

	if (this->y + speed[1] >= 0 && this->y + speed[1] <= Params::SCREEN_HEIGHT)
		this->y += speed[1];

}

void Coordinate::setMaxWidthX() {
	this->x = Params::SCREEN_WIDTH - 1;
}
