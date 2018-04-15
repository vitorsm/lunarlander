/*
 * HUDController.cpp
 *
 *  Created on: 14 de abr de 2018
 *      Author: vitor
 */

#include "HUDController.h"

HUDController::HUDController() {
	// TODO Auto-generated constructor stub
	this->speed = 12.02;
	this->height = 0;
	this->rotation = 0;
}

HUDController::~HUDController() {
	// TODO Auto-generated destructor stub
}

void HUDController::drawHUD() {
	GLfloat color[3] = { 0, 0, 0 };
	glColor3fv(color);

	float increment = 0;
	glRasterPos2i(5, Params::TEXT_POSITION - increment);
	drawText(GLUT_BITMAP_9_BY_15, Utils::concatValue("Velocidade: ", this->speed));

	increment += Params::TEXT_INCREMENT_POSITION;
	glRasterPos2i(5, Params::TEXT_POSITION - increment);
	drawText(GLUT_BITMAP_9_BY_15, Utils::concatValue("Altitude: ", this->height));

	increment += Params::TEXT_INCREMENT_POSITION;
	glRasterPos2i(5, Params::TEXT_POSITION - increment);
	drawText(GLUT_BITMAP_9_BY_15, Utils::concatValue("Rotacao: ", this->rotation));

}

// Codigo retirado da internet por motivos de otimização de tempo
// *Fonte: www.univasf.edu.br/~jorge.cavalcanti/opengl/ExemploGLUT-texto.cpp
void HUDController::drawText(void *font, char *s) {
	while(*s)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*s++);
}

void HUDController::updateData(float speed, float height, float rotation) {
	this->speed = speed * 10;
	this->height = height;
	this->rotation = rotation *10;
}
