/*
 * InstructionsController.h
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_INSTRUCTIONSCONTROLLER_H_
#define CONTROLLERS_INSTRUCTIONSCONTROLLER_H_

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "../models/Params.h"
#include "../Utils.h"

class InstructionsController {
public:
	InstructionsController();
	virtual ~InstructionsController();
	void drawInstructions();
private:
	void drawText(void *font, char *s);
};

#endif /* CONTROLLERS_INSTRUCTIONSCONTROLLER_H_ */
