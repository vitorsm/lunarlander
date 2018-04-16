/*
 * MenuController.h
 *
 *  Created on: 14 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_MENUCONTROLLER_H_
#define CONTROLLERS_MENUCONTROLLER_H_

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "../models/Params.h"
#include "../Utils.h"

using namespace std;

class MenuController {
public:
	MenuController();
	virtual ~MenuController();
	void drawMenu();
	void setUpMenu();
	void setDownMenu();
	int getSelectedMenu();

	static int START_GAME_MENU_ITEM;
	static int INSTRUCTION_MENU_ITEM;
	static int EXIT_MENU_ITEM;

private:
	void drawMenuItem();
	void drawText(void *font, char *s);
	int coutMenu;
	GLuint backgroundTexture;
	void initBackground();
};

#endif /* CONTROLLERS_MENUCONTROLLER_H_ */
