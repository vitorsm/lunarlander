/*
 * PauseController.cpp
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#include "PauseController.h"

PauseController::PauseController() {
	// TODO Auto-generated constructor stub
	this->coutMenu = RESUME_GAME_MENU_ITEM;
}

PauseController::~PauseController() {
	// TODO Auto-generated destructor stub
}

int PauseController::RESUME_GAME_MENU_ITEM = 1;
int PauseController::RESTART_GAME_MENU_ITEM = 2;
int PauseController::MENU_MENU_ITEM = 3;

int PauseController::getSelectedMenu() {
	return this->coutMenu;
}

void PauseController::drawPause() {

	glColor4f(0, 0, 0, 0.5);

	glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(Params::SCREEN_WIDTH, 0, 0);
		glVertex3f(Params::SCREEN_WIDTH, Params::SCREEN_HEIGHT, 0);
		glVertex3f(0, Params::SCREEN_HEIGHT, 0);
	glEnd();

	this->drawMenuItem();
}

void PauseController::drawMenuItem() {

	glColor3f(1, 1, 1);
	glRasterPos2i(Params::MENU_POSITION_X - 10, Params::MENU_POSITION_Y + 15);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "Jogo pausado - Pressione p para voltar ao jogo");

	if (this->coutMenu == RESUME_GAME_MENU_ITEM)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);

	float increment = 0;
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y - increment);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "VOLTAR AO JOGO");

	if (this->coutMenu == RESTART_GAME_MENU_ITEM)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);

	increment += Params::MENU_INCREMENT_POSITION;
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y - increment);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "REINICIAR JOGO");

	if (this->coutMenu == MENU_MENU_ITEM)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);

	increment += Params::MENU_INCREMENT_POSITION;
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y - increment);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "IR PARA O MENU PRINCIPAL");

	glColor3f(1, 1, 1);
}

void PauseController::drawText(void *font, char *s) {
	while(*s)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*s++);
}

void PauseController::setUpMenu() {
	if (this->coutMenu > PauseController::RESUME_GAME_MENU_ITEM)
		this->coutMenu--;
}

void PauseController::setDownMenu() {
	if (this->coutMenu < PauseController::MENU_MENU_ITEM)
		this->coutMenu++;
}
