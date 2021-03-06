/*
 * SpacecraftController.h
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#ifndef CONTROLLERS_SPACECRAFTCONTROLLER_H_
#define CONTROLLERS_SPACECRAFTCONTROLLER_H_

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../models/Coordinate.h"
#include "../models/Params.h"
#include "FloorController.h"
#include "../Utils.h"


class SpacecraftController {
public:
	SpacecraftController(FloorController *floorController);
	virtual ~SpacecraftController();
	void drawSpacecraft();
	void updatePosition();
	void setPowerMotor(bool power);
	void setLeftPower();
	void setRightPower();
	float *getAcceleration();
	float *getSpeed();
	Coordinate *getSpacecraftPosition();
	// Informa que a nave explodiu
	void setExplosion(bool explosion);
	// Pega em qual frame da explosao esta sendo executada
	int getCountExplosionImage();
	// Pega a quantidade de frames da explosao
	int getAmountExplosionImage();
	void setInitialPosition();
	void setInitialFuel(int level);
	int getSpentFuel();
	int getFuel();
private:
	void setRotate();
	long lastTime;
	float acceleration[2]; // vetor contendo: { 0: componeneteX, 1: componentY }
	float speed[2]; // vetor contendo: { 0: componeneteX, 1: componentY }
	Coordinate *position;
	long timeLastUpdateMotor;
	long timeLastUpdateDirection;
	FloorController *floorController;
	int fuel;
	int spentFuel;

	GLuint spacecraftTexture;
	GLuint fireTexture[40]; // 40 posicoes no vetor pq eu já sei que existem 40 imagens de fogo
	GLuint explosionTexture[20]; // 20 posicoes no vetor pq eu já sei que existem 20 imagens de fogo
	void initTexture();

	// Variaveis para controle da animacao de explosao
	int amountExplosionImage;
	int countExplosionImage;
	bool explosion;

	// Variaveis para controle da animacao do foguinho da nave
	int amountFireImage;
	int countFireImage;
	bool motorPower;
};

#endif /* CONTROLLERS_SPACECRAFTCONTROLLER_H_ */
