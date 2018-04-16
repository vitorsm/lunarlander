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
//	GLfloat color[3] = { 1, 1, 1 };
//	glColor3fv(color);
	glColor3f(1, 1, 1);

	float increment = 0;

	glRasterPos2i(5, Params::TEXT_POSITION - increment);
	drawText(GLUT_BITMAP_9_BY_15, Utils::concatValue("Fase: ", this->level));

	increment += Params::TEXT_INCREMENT_POSITION;
	glRasterPos2i(5, Params::TEXT_POSITION - increment);
	drawText(GLUT_BITMAP_9_BY_15, Utils::concatValue("Velocidade: ", this->speed));

	increment += Params::TEXT_INCREMENT_POSITION;
	glRasterPos2i(5, Params::TEXT_POSITION - increment);
	drawText(GLUT_BITMAP_9_BY_15, Utils::concatValue("Altitude: ", this->height));

	increment += Params::TEXT_INCREMENT_POSITION;
	glRasterPos2i(5, Params::TEXT_POSITION - increment);
	drawText(GLUT_BITMAP_9_BY_15, Utils::concatValue("Rotacao: ", this->rotation));

	increment += Params::TEXT_INCREMENT_POSITION;
	glRasterPos2i(5, Params::TEXT_POSITION - increment);
	drawText(GLUT_BITMAP_9_BY_15, Utils::concatValue("Combustivel: ", this->fuel));

	increment += Params::TEXT_INCREMENT_POSITION;
	glRasterPos2i(5, Params::TEXT_POSITION - increment);
//	drawText(GLUT_BITMAP_9_BY_15, Utils::concatValue("Vidas: ", this->lifes));
	drawText(GLUT_BITMAP_9_BY_15, "Vidas  ");

	this->drawLifes(14, Params::TEXT_POSITION - increment + Params::LIFES_SIZE);
}

void HUDController::drawLifes(float x, float y) {

	glColor3f(1, 1, 1);

	for (int i = 0; i < this->lifes; i++) {
		glBegin(GL_TRIANGLES);
			glVertex3f(x, y, 0);
			glVertex3f(x - Params::LIFES_SIZE, y - Params::LIFES_SIZE, 0);
			glVertex3f(x + Params::LIFES_SIZE, y - Params::LIFES_SIZE, 0);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3f(x - Params::LIFES_SIZE, y - 0.5, 0);
			glVertex3f(x + Params::LIFES_SIZE, y - 0.5, 0);
			glVertex3f(x, y - Params::LIFES_SIZE - 0.5, 0);
		glEnd();

		x += 3;
	}

}
// Codigo retirado da internet por motivos de otimização de tempo
// *Fonte: www.univasf.edu.br/~jorge.cavalcanti/opengl/ExemploGLUT-texto.cpp
void HUDController::drawText(void *font, char *s) {
	while(*s)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*s++);
}

void HUDController::updateData(float speed, float height, float rotation, int lifes, int level, int fuel) {
	this->speed = speed * 10;
	this->height = height;
	this->rotation = rotation *10;
	this->lifes = lifes;
	this->level = level;
	this->fuel = fuel;
}
