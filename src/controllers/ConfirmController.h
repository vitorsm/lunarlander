/*
 * ConfirmController.h
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_CONFIRMCONTROLLER_H_
#define CONTROLLERS_CONFIRMCONTROLLER_H_

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "../models/Params.h"
#include "../Utils.h"

using namespace std;

class ConfirmController {
public:
	ConfirmController();
	virtual ~ConfirmController();
	void drawConfirm();

	void setMessage(char *text);
	void setUpMenu();
	void setDownMenu();
	int getSelectedMenu();


	static int YES_MENU_ITEM;
	static int NO_MENU_ITEM;
private:
	void drawMenuItem();
	void drawText(void *font, char *s);
	int countMenu;
	char *text;
};

#endif /* CONTROLLERS_CONFIRMCONTROLLER_H_ */
