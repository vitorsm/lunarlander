/*
 * PauseController.h
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_PAUSECONTROLLER_H_
#define CONTROLLERS_PAUSECONTROLLER_H_

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "../models/Params.h"
#include "../Utils.h"

using namespace std;

class PauseController {
public:
	PauseController();
	virtual ~PauseController();
	void drawPause();
	void setUpMenu();
	void setDownMenu();
	int getSelectedMenu();

	static int RESUME_GAME_MENU_ITEM;
	static int RESTART_GAME_MENU_ITEM;
	static int MENU_MENU_ITEM;

private:
	void drawMenuItem();
	void drawText(void *font, char *s);
	int coutMenu;
};

#endif /* CONTROLLERS_PAUSECONTROLLER_H_ */
