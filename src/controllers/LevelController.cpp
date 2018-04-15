/*
 * LevelController.cpp
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#include "LevelController.h"

LevelController::LevelController() {
	// TODO Auto-generated constructor stub
	this->level = 1;
	this->lastLevel = 1;
	this->countMenu = CONTINUE_MENU_ITEM;
}

LevelController::~LevelController() {
	// TODO Auto-generated destructor stub
}

int LevelController::CONTINUE_MENU_ITEM = 1;
int LevelController::MENU_MENU_ITEM = 2;

void LevelController::setLevel(int level) {
	this->level = level;
}

void LevelController::setLastLevel() {
	this->lastLevel = this->level;
}

void LevelController::setUpMenu() {
	if (this->countMenu > LevelController::CONTINUE_MENU_ITEM)
		this->countMenu--;
}

void LevelController::setDownMenu() {
	if (this->countMenu < LevelController::MENU_MENU_ITEM)
		this->countMenu++;
}

int LevelController::getSelectedMenu() {
	return this->countMenu;
}

void LevelController::drawLevel() {

	glColor4f(0, 0, 0, 0.5);
	glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(Params::SCREEN_WIDTH, 0, 0);
		glVertex3f(Params::SCREEN_WIDTH, Params::SCREEN_HEIGHT, 0);
		glVertex3f(0, Params::SCREEN_HEIGHT, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y + 15);
	if (this->level == this->lastLevel) {
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, "Voce perdeu.");
	} else {
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, "Voce ganhou!!");
	}


	float increment = 0;

	if (this->countMenu == CONTINUE_MENU_ITEM)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);

	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y - increment);

	if (this->level == this->lastLevel) {
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, Utils::concatValue("Reiniciar a fase ", this->level));
	} else {
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, Utils::concatValue("Iniciar a fase ", this->level));
	}

	increment += Params::MENU_INCREMENT_POSITION;

	if (this->countMenu == MENU_MENU_ITEM)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y - increment);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "Menu principal.");
}

void LevelController::drawText(void *font, char *s) {
	while(*s)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*s++);
}
