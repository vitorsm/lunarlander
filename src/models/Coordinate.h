/*
 * Coordinate.h
 *
 *  Created on: 2 de abr de 2018
 *      Author: vitor
 */

#ifndef MODELS_COORDINATE_H_
#define MODELS_COORDINATE_H_

#include <iostream>
#include "Params.h"

using namespace std;


class Coordinate {
public:
	Coordinate(float x, float y);
	virtual ~Coordinate();
	float getX();
	float getY();
	void print();
	void updateBySpeed(float *speed, long time);
private:
	float x;
	float y;
};

#endif /* MODELS_COORDINATE_H_ */
