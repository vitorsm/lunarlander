/*
 * InstructionsController.cpp
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#include "InstructionsController.h"

InstructionsController::InstructionsController() {
	// TODO Auto-generated constructor stub

}

InstructionsController::~InstructionsController() {
	// TODO Auto-generated destructor stub
}

const int amountLines = 13;
const int amountKeyLines = 9;

char instructionsStr[amountLines][100] = {
		"O jogo Lunar Lander foi criado pela Atari em 1979 e foi um terrível sucesso,",
		"sendo jogado em fliperamas de todo o mundo.",
		"Ele foi baseado no Moonlander (1973), que foi o primeiro jogo gráfico do genero,",
		" e utilizou um monitor vetorial dentro do gabinete de madeira do arcade.",
		"O jogo mostra uma nave que está tentando aterrisar com sucesso na superfície lunar.",
		"Assim que uma partida começa, a nave está a uma certa altura do chão,",
		"e logo começa a cair sendo atraída pela gravidade. Ao pressionar as setas, ",
		"a nave gira em torno do próprio eixo e, ao pressionar a seta para cima, ",
		"ela ativa seu motor principal e acelera na direção para onde está apontando",
		"Existe um local pré-determinado e visualmente marcado no chão onde a nave deve",
		"aterrisar.",
		"",
		""
//		" ........:::::::: Pressione enter para voltar ao menu inicial ::::::::........"
};

char keys[amountKeyLines][100] = {
		"Seta para cima: liga o motor da nave",
		"Seta para esquerda: movimenta a nave para esquerda",
		"Seta para direita: movimenta a nave para direita",
		"P: pausa o jogo",
		"ESC: encerra o jogo",
		"R: reinicia o jogo",
		"",
		"",
		" ........:::::::: Pressione enter para voltar ao menu inicial ::::::::........"
};

void InstructionsController::drawText(void *font, char *s) {
	while(*s)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*s++);
}

void InstructionsController::drawInstructions() {

	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(Params::SCREEN_WIDTH, 0, 0);
		glVertex3f(Params::SCREEN_WIDTH, Params::SCREEN_HEIGHT, 0);
		glVertex3f(0, Params::SCREEN_HEIGHT, 0);
	glEnd();

	float y = Params::MENU_POSITION_Y + 15;

	glColor3f(1, 1, 1);
	glRasterPos2i(15, y);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "INSTRUCOES DO JOGO");

	for (int i = 0; i < amountLines; i++) {
		char *str = instructionsStr[i];

		y -= Params::TEXT_INCREMENT_POSITION;
		glRasterPos2i(8, y);
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, str);
	}

	y -= Params::MENU_INCREMENT_POSITION;
	glRasterPos2i(15, y);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "TECLAS:");

	for (int i = 0; i < amountKeyLines; i++) {
		char *str = keys[i];

		y -= Params::TEXT_INCREMENT_POSITION;
		glRasterPos2i(8, y);
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, str);
	}
}
