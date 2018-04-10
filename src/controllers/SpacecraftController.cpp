/*
 * SpacecraftController.cpp
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#include "SpacecraftController.h"

SpacecraftController::SpacecraftController() {
	// TODO Auto-generated constructor stub
//	this->position = new Coordinate(0, Params::SCREEN_HEIGHT);
	this->position = new Coordinate(Params::SCREEN_WIDTH / 2, Params::SCREEN_HEIGHT);
//	this->acceleration = Params::INITIAL_ACCELERATION;
	this->acceleration[0] = 0;
	this->acceleration[1] = Params::INITIAL_ACCELERATION;
	this->speed[0] = 0;
	this->speed[1] = 0;
	this->timeLastUpdateMotor = 0;
	this->timeLastUpdateDirection = 0;
	this->floorController = NULL;

	this->lastTime = time(0);
}

SpacecraftController::~SpacecraftController() {
	// TODO Auto-generated destructor stub
}

void SpacecraftController::setPowerMotor(bool power) {
	this->acceleration[1] = power ? Params::POWER_ACCELERATION : Params::INITIAL_ACCELERATION;
}

void SpacecraftController::setLeftPower() {
	float lastAcceleration = this->acceleration[0];

	if (this->acceleration[0] > 0)
		this->acceleration[0] += -(10 * this->acceleration[0]) * Params::POWER_DIRECTION_ACCELERATION;
	else
		this->acceleration[0] += -Params::POWER_DIRECTION_ACCELERATION;

	if (this->acceleration[0] > 2 * Params::MAX_SPEED || this->acceleration[0] < -2 * Params::MAX_SPEED) {
		this->acceleration[0] = lastAcceleration;
	}

	this->timeLastUpdateDirection = time(0);
}

void SpacecraftController::setRightPower() {
	float lastAcceleration = this->acceleration[0];

	if (this->acceleration[0] < 0)
		this->acceleration[0] += (10 * -this->acceleration[0]) * Params::POWER_DIRECTION_ACCELERATION;
	else
		this->acceleration[0] += Params::POWER_DIRECTION_ACCELERATION;

	if (this->acceleration[0] > 2 * Params::MAX_SPEED || this->acceleration[0] < -2 * Params::MAX_SPEED) {
		this->acceleration[0] = lastAcceleration;
	}

	this->timeLastUpdateMotor = time(0);
}

void SpacecraftController::updatePosition(FloorController *floorController) {
	this->floorController = floorController;

	long currentTime = time(0);
	float time = (currentTime - this->lastTime);

	float newSpeed = acceleration[0] * Params::UNITY_PER_METER;
	if (newSpeed <= 2 * Params::MAX_SPEED && newSpeed >= -2 * Params::MAX_SPEED)
		speed[0] = newSpeed;

	if (this->acceleration[1] < 0 && this->speed[1] > 0) {
		speed[1] = 0;
	}

	newSpeed = speed[1] + acceleration[1] * Params::UNITY_PER_METER;
	if (newSpeed <= 2 * Params::MAX_SPEED && newSpeed >= -2 * Params::MAX_SPEED)
		speed[1] = newSpeed;

	this->position->updateBySpeed(speed, time);

	this->lastTime = currentTime;

	this->floorController->isOnTheFloor(this->position);

	if (this->floorController->isOnTheRunway(this->position)) {
		cout << "Esta no local" << endl;
	}
}

void SpacecraftController::setRotate() {
//	glTranslatef(this->position->getX(), this->position->getY(), 0);
	float x = this->position->getX() - Params::SPACECRAFT_WIDTH / 2;
	float y = this->position->getY();

	glTranslatef(x, y, 0);
	glRotatef(-30 * this->acceleration[0], 0, 0, 1);
}

void SpacecraftController::drawSpacecraft() {

	glPushMatrix();

	this->setRotate();
	float x = this->position->getX() - Params::SPACECRAFT_WIDTH / 2;
	float y = this->position->getY() - Params::SPACECRAFT_HEIGHT / 2;

	glColor3f(0, 0, 0);

//	glBegin(GL_POLYGON);
//		glVertex3f(x, y, 0);
//		glVertex3f(x + Params::SPACECRAFT_WIDTH, y, 0);
//		glVertex3f(x + Params::SPACECRAFT_WIDTH, y + Params::SPACECRAFT_HEIGHT, 0);
//		glVertex3f(x, y + Params::SPACECRAFT_HEIGHT, 0);
//	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(Params::SPACECRAFT_WIDTH, 0, 0);
		glVertex3f(Params::SPACECRAFT_WIDTH, Params::SPACECRAFT_HEIGHT, 0);
		glVertex3f(0, Params::SPACECRAFT_HEIGHT, 0);
	glEnd();
	glPopMatrix();
}
