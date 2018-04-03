/*
 * Coordinate.h
 *
 *  Created on: 2 de abr de 2018
 *      Author: vitor
 */

#ifndef MODELS_COORDINATE_H_
#define MODELS_COORDINATE_H_

#include <iostream>
using namespace std;

class Coordinate {
public:
	Coordinate(int x, int y);
	virtual ~Coordinate();
	int getX();
	int getY();
	void print();
private:
	int x;
	int y;
};

#endif /* MODELS_COORDINATE_H_ */
