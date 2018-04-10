/*
 * Floor.cpp
 *
 *  Created on: 2 de abr de 2018
 *      Author: vitor
 */

#include "Floor.h"

Floor::Floor() {
	srand(time(NULL));
	this->coordinatesAmount = 0;
}

Floor::~Floor() {
	// TODO Auto-generated destructor stub
}

void Floor::printAllCoordinates() {
	cout << this->coordinatesAmount << " pontos" << endl;

	for (int i = 0; i < this->coordinatesAmount; i++) {
		this->coordinates->at(i)->print();
		cout << endl;
	}
}

void Floor::generateFloor(int level) {
	// somando + 1 para colocar a ultima coordenada, para fechar a parada
	int coordinatesAmount = level * coefficientVariation + 1;
	int variationHeight = level * coefficientVariation * 2;

//	this->coordinatesAmount = coordinatesAmount;
	this->coordinates = new vector<Coordinate*>;

//	int countRunway = rand() % (coordinatesAmount/2);
	int coordinateXRunway = rand() % (Params::SCREEN_WIDTH - Params::RUNWAY_WIDTH);

	cout << "coordinates amount: " << coordinatesAmount << " | countRunway: " << coordinateXRunway << endl;
	float lastX = 0;
	float lastY = 0;
	bool isRunway = false;
	bool runwaySelected = false;

	for (int i = 0; i < coordinatesAmount; i++) {
		int x = 0;

		// Somente se nao for o primeiro ponto a coordenada pode nao ser o zero.
		if (i > 0 && i != coordinatesAmount) {
			x = rand() % (Params::SCREEN_WIDTH - (int) lastX + 1) + lastX;
		} else if (i == coordinatesAmount) {
			x = Params::SCREEN_WIDTH;
		}

		int y = 0;

		// Verifica se o ultimo foi a pista de pouso, se sim mante a variacao do y = 0
		// Ou seja, vai manter essa parte do piso reta
		if (isRunway)
			isRunway = false;
		else
			y = rand() % variationHeight - (variationHeight / 2.0);

		y += lastY;
		if (y < 0) y = 0;

		if (x >= coordinateXRunway && !runwaySelected) {
			if (x + Params::RUNWAY_WIDTH > Params::SCREEN_WIDTH) {
				x -= (x + Params::RUNWAY_WIDTH) - Params::SCREEN_WIDTH;
			}
			cout << "x = " << x << " e gerou runway" << endl;
			this->runwayCoordinate = new Coordinate(x, y);
			lastX = x + Params::RUNWAY_WIDTH;
			isRunway = true;
			runwaySelected = true;
		} else {
			lastX = x;
		}
		lastY = y;

		Coordinate *coordinate = new Coordinate(x, y);
		this->coordinates->push_back(coordinate);

		this->coordinatesAmount++;

		if (x >= Params::SCREEN_WIDTH)
			break;
	}

	cout << "coordinates amount: " << this->coordinatesAmount << endl;

	this->closePolygon();

}

void Floor::closePolygon() {
	Coordinate *coordinate = new Coordinate(Params::SCREEN_WIDTH, 0);
	this->coordinates->push_back(coordinate);
	this->coordinatesAmount++;

	coordinate = new Coordinate(0, 0);
	this->coordinates->push_back(coordinate);
	this->coordinatesAmount++;
}

vector<Coordinate*> *Floor::getCoordinates() {
	return this->coordinates;
}

int Floor::getCoordinatesAmount() {
	return this->coordinatesAmount;
}

Coordinate *Floor::getRunwayCoordinate() {
	return this->runwayCoordinate;
}

vector<Coordinate*> *Floor::getFloorCoordinateByPosition(Coordinate *leftCoordinate, Coordinate *rightCoordinate) {

//	cout << "leftCoordinate: " << leftCoordinate->getX() << ", rightCoordinate: " << rightCoordinate->getX() << endl;

//	printAllCoordinates();

	Coordinate *firstCoordinate = NULL;
	Coordinate *lastCoordinate = NULL;

	vector<Coordinate*> *coordinatesRet = new vector<Coordinate*>;

	for (int i = 0; i < this->coordinatesAmount; i++) {
		Coordinate *coordinate = this->coordinates->at(i);

		if (firstCoordinate == NULL) {
			firstCoordinate = coordinate;
		} else if (coordinate->getX() <= leftCoordinate->getX() &&
				(coordinate->getX() > firstCoordinate->getX())) {
			firstCoordinate = coordinate;
		}

		if (lastCoordinate == NULL) {
			lastCoordinate = coordinate;
		} else if (coordinate->getX() >= rightCoordinate->getX() &&
				(lastCoordinate->getX() < rightCoordinate->getX() || coordinate->getX() < lastCoordinate->getX())) {
			lastCoordinate = coordinate;
		}
	}

//	cout << "first: " << firstCoordinate->getX() << ", last: " << lastCoordinate->getX() << endl;

	for (int i = 0; i < this->coordinatesAmount - 1; i++) {
		Coordinate *coordinate = this->coordinates->at(i);

		if (coordinate->getX() >= firstCoordinate->getX() && coordinate->getX() <= lastCoordinate->getX()) {
			coordinatesRet->push_back(coordinate);
		}
	}

	return coordinatesRet;
}
