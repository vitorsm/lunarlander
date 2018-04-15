/*
 * MenuController.cpp
 *
 *  Created on: 14 de abr de 2018
 *      Author: vitor
 */

#include "MenuController.h"

MenuController::MenuController() {
	// TODO Auto-generated constructor stub
	this->coutMenu = MenuController::START_GAME_MENU_ITEM;
}

MenuController::~MenuController() {
	// TODO Auto-generated destructor stub
}

int MenuController::START_GAME_MENU_ITEM = 1;
int MenuController::INSTRUCTION_MENU_ITEM = 2;
int MenuController::EXIT_MENU_ITEM = 3;


void MenuController::initBackground() {
	this->backgroundTexture = SOIL_load_OGL_texture(
			"src/resources/background_menu.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
	);

	if (this->backgroundTexture == 0) {
		cout << "Algo de errado não está certo com a textura: " << endl << SOIL_last_result() << endl;
	}
}

int MenuController::getSelectedMenu() {
	return this->coutMenu;
}

void MenuController::drawMenu() {

	if (this->backgroundTexture == NULL) {
		this->initBackground();
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->backgroundTexture);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0); 	glVertex3f(0, 0, 0);
		glTexCoord2f(1, 0);	glVertex3f(Params::SCREEN_WIDTH, 0, 0);
		glTexCoord2f(1, 1);	glVertex3f(Params::SCREEN_WIDTH, Params::SCREEN_HEIGHT, 0);
		glTexCoord2f(0, 1);	glVertex3f(0, Params::SCREEN_HEIGHT, 0);
	glEnd();

	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);

	this->drawMenuItem();
}

void MenuController::drawMenuItem() {

//	glScalef(0.2, 0.2, 0.2);

	if (this->coutMenu == START_GAME_MENU_ITEM)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);

	float increment = 0;
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y - increment);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "INICIAR JOGO");

	if (this->coutMenu == INSTRUCTION_MENU_ITEM)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);

	increment += Params::MENU_INCREMENT_POSITION;
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y - increment);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "INSTRUCOES");

	if (this->coutMenu == EXIT_MENU_ITEM)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);

	increment += Params::MENU_INCREMENT_POSITION;
	glRasterPos2i(Params::MENU_POSITION_X, Params::MENU_POSITION_Y - increment);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "SAIR DO JOGO");

	glColor3f(1, 1, 1);
}

void MenuController::drawText(void *font, char *s) {
	while(*s)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*s++);
}

void MenuController::setUpMenu() {
	if (this->coutMenu > MenuController::START_GAME_MENU_ITEM)
		this->coutMenu--;
}

void MenuController::setDownMenu() {
	if (this->coutMenu < MenuController::EXIT_MENU_ITEM)
		this->coutMenu++;
}
