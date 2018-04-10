/*
 * Floor.h
 *
 *  Created on: 2 de abr de 2018
 *      Author: vitor
 */

#ifndef MODELS_FLOOR_H_
#define MODELS_FLOOR_H_

using namespace std;
#include "Coordinate.h"
#include "Params.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


const int coefficientVariation = 3;

class Floor {
public:
	Floor();
	virtual ~Floor();
	void generateFloor(int level);
	void printAllCoordinates();
	vector<Coordinate*> *getCoordinates();
	int getCoordinatesAmount();
	Coordinate *getRunwayCoordinate();
	vector<Coordinate*> *getFloorCoordinateByPosition(Coordinate *leftCoordinate, Coordinate *rightCoordinate);
private:
	int coordinatesAmount;
	vector<Coordinate*> *coordinates;
	Coordinate *runwayCoordinate;
	void closePolygon();
};

#endif /* MODELS_FLOOR_H_ */
