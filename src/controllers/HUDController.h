/*
 * HUDController.h
 *
 *  Created on: 14 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_HUDCONTROLLER_H_
#define CONTROLLERS_HUDCONTROLLER_H_
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include "../models/Params.h"
#include "../Utils.h"

using namespace std;


class HUDController {
public:
	HUDController();
	virtual ~HUDController();
	void drawHUD();

	void updateData(float speed, float height, float rotation, int lifes, int level, int fuel);
private:
	GLuint fontOffset;
	float speed;
	float height;
	float rotation;
	int lifes;
	int level;
	int fuel;

	void drawLifes(float x, float y);
//	char *concatValue(char *str, float value);

	void drawText(void *font, char *text);
};

#endif /* CONTROLLERS_HUDCONTROLLER_H_ */
