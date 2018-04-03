/*
 * Coordinate.cpp
 *
 *  Created on: 2 de abr de 2018
 *      Author: vitor
 */

#include "Coordinate.h"

Coordinate::Coordinate(int x, int y) {
	// TODO Auto-generated constructor stub
	this->x = x;
	this->y = y;
}

Coordinate::~Coordinate() {
	// TODO Auto-generated destructor stub
}

int Coordinate::getX() {
	return this->x;
}

int Coordinate::getY() {
	return this->y;
}

void Coordinate::print() {
	cout << "(" << this->x << ", " << this->y << ")";
}
