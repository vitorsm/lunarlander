/*
 * Hole.h
 *
 *  Created on: 2 de abr de 2018
 *      Author: vitor
 */

#ifndef MODELS_HOLE_H_
#define MODELS_HOLE_H_

class Hole {
public:
	Hole();
	virtual ~Hole();

private:
	int width;
	int height;
	int alpha;
	bool placeToLand;
};


#endif /* MODELS_HOLE_H_ */
