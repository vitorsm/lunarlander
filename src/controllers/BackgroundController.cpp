/*
 * BackgroundController.cpp
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#include "BackgroundController.h"

BackgroundController::BackgroundController() {

}

BackgroundController::~BackgroundController() {
	// TODO Auto-generated destructor stub
}

void BackgroundController::initTexture() {
	this->backgroundTexture = SOIL_load_OGL_texture(
		"src/resources/background_game.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
}

void BackgroundController::drawBackground() {

	if (this->backgroundTexture == NULL) {
		this->initTexture();
	}

	glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, this->backgroundTexture);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0); 	glVertex3f(0, 0, 0);
		glTexCoord2f(1, 0);	glVertex3f(Params::SCREEN_WIDTH, 0, 0);
		glTexCoord2f(1, 1);	glVertex3f(Params::SCREEN_WIDTH, Params::SCREEN_HEIGHT, 0);
		glTexCoord2f(0, 1);	glVertex3f(0, Params::SCREEN_HEIGHT, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

}
