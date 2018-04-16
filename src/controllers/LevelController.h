/*
 * LevelController.h
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_LEVELCONTROLLER_H_
#define CONTROLLERS_LEVELCONTROLLER_H_

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "../models/Params.h"
#include "../Utils.h"

using namespace std;

class LevelController {
public:
	LevelController();
	virtual ~LevelController();
	void setLevel(int level);
	void setLastLevel(int lifes);
	void requestStartLevel();
	void drawLevel();

	void setScores(int score, int completeScore);
	void setUpMenu();
	void setDownMenu();
	int getSelectedMenu();

	void setMaxSpeed(bool maxSpeed, bool maxRotation);

	static int CONTINUE_MENU_ITEM;
	static int MENU_MENU_ITEM;
private:
	int lifes;
	int level;
	int lastLevel;
	void drawText(void *font, char *s);

	bool maxSpeed;
	bool maxRotation;

	int score;
	int completeScore;
	int countMenu;
};

#endif /* CONTROLLERS_LEVELCONTROLLER_H_ */
