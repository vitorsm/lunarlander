/*
 * BackgroundController.h
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_BACKGROUNDCONTROLLER_H_
#define CONTROLLERS_BACKGROUNDCONTROLLER_H_


#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>

#include "../models/Params.h"
#include "FloorController.h"

class BackgroundController {
public:
	BackgroundController();
	virtual ~BackgroundController();
	/***
	 * Apenas desenha a imagem de background
	 */
	void drawBackground();
private:
	GLuint backgroundTexture;
	void initTexture();
};

#endif /* CONTROLLERS_BACKGROUNDCONTROLLER_H_ */
