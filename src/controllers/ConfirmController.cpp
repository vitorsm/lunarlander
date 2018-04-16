/*
 * ConfirmController.cpp
 *
 *  Created on: 16 de abr de 2018
 *      Author: vitor
 */

#include "ConfirmController.h"

ConfirmController::ConfirmController() {
	this->text = NULL;
	this->countMenu = 1;
}

ConfirmController::~ConfirmController() {
	// TODO Auto-generated destructor stub
}

int ConfirmController::YES_MENU_ITEM = 1;
int ConfirmController::NO_MENU_ITEM = 2;


int ConfirmController::getSelectedMenu() {
	return this->countMenu;
}

void ConfirmController::setMessage(char *text) {
	this->text = text;
}

void ConfirmController::drawText(void *font, char *s) {
	while(*s)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*s++);
}

void ConfirmController::setUpMenu() {
	if (this->countMenu > ConfirmController::YES_MENU_ITEM)
		this->countMenu--;
}

void ConfirmController::setDownMenu() {
	if (this->countMenu < ConfirmController::NO_MENU_ITEM)
		this->countMenu++;
}

void ConfirmController::drawConfirm() {
	glColor4f(0, 0, 0, 0.5);

	glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(Params::SCREEN_WIDTH, 0, 0);
		glVertex3f(Params::SCREEN_WIDTH, Params::SCREEN_HEIGHT, 0);
		glVertex3f(0, Params::SCREEN_HEIGHT, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y + 5);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, this->text);

	this->drawMenuItem();
}

void ConfirmController::drawMenuItem() {

	if (this->countMenu == YES_MENU_ITEM)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);

	float increment = 0;
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y - increment);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "SIM");

	if (this->countMenu == NO_MENU_ITEM)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);

	increment += Params::MENU_INCREMENT_POSITION;
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y - increment);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "NAO");

	glColor3f(1, 1, 1);
}
