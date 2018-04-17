/*
 * SpacecraftController.cpp
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#include "SpacecraftController.h"

SpacecraftController::SpacecraftController(FloorController *floorController) {
	// TODO Auto-generated constructor stub
//	this->position = new Coordinate(0, Params::SCREEN_HEIGHT);
	this->position = new Coordinate(Params::SCREEN_WIDTH / 2, Params::SCREEN_HEIGHT);
	this->acceleration[0] = 0;
	this->acceleration[1] = Params::INITIAL_ACCELERATION;
	this->speed[0] = 0;
	this->speed[1] = 0;
	this->timeLastUpdateMotor = 0;
	this->timeLastUpdateDirection = 0;
	this->floorController = floorController;

	this->fuel = 0;
	srand(time(NULL));

	this->lastTime = time(0);

	// pq eu já sei que tem 40 imagens de fogo
	this->amountFireImage = 40;
	this->countFireImage = 0;
	this->motorPower = false;

	// pq eu já sei que tem 20 imagens de explosao
	this->amountExplosionImage = 20;
	this->countExplosionImage = 0;
	this->explosion = false;

}

SpacecraftController::~SpacecraftController() {
	// TODO Auto-generated destructor stub
}

void SpacecraftController::setInitialFuel(int level) {
	this->fuel = Params::INITIAL_FUEL - (level * level + 3 * level);
	this->spentFuel = 0;
	if (this->fuel < Params::MINIMUM_FUEL) {
		this->fuel = Params::MINIMUM_FUEL;
	}
}

int SpacecraftController::getSpentFuel() {
	return this->spentFuel;
}

int SpacecraftController::getFuel() {
	return this->fuel;
}
int SpacecraftController::getAmountExplosionImage() {
	return this->amountExplosionImage;
}
int SpacecraftController::getCountExplosionImage() {
	return this->countExplosionImage;
}
/***
 * Cria aleatoriomente uma posicao inicial para nave
 */
void SpacecraftController::setInitialPosition() {
	this->countExplosionImage = 0;
	this->explosion = false;

	float initX = rand() % (Params::SCREEN_WIDTH);

	this->position = new Coordinate(initX, Params::SCREEN_HEIGHT);
	this->acceleration[0] = 0;
	this->acceleration[1] = Params::INITIAL_ACCELERATION;
	this->speed[0] = 0;
	this->speed[1] = 0;
}

void SpacecraftController::initTexture() {

	// Pegando a textura da nave
	this->spacecraftTexture = SOIL_load_OGL_texture(
			"src/resources/spacecraft.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
	);

	if (this->spacecraftTexture == 0) {
		cout << "Algo de errado não está certo com a textura: " << endl << SOIL_last_result() << endl;
	}

	// Pegando a textura do fogo
	// Existem 40 imagens do fogo, o nome delas e
	// src/resources/fire/fire_1f_40_i.png, sendo que i vai de 1 a 40.
	for (int i = 0; i < this->amountFireImage; i++) {
		char *str = Utils::concatValue("src/resources/fire/fire_1f_40_", (i + 1));
		str = Utils::concatChar(str, ".png");

		this->fireTexture[i] = SOIL_load_OGL_texture(
				str,
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y
		);

		if (this->fireTexture[i] == 0) {
			cout << "Algo de errado não está certo com a textura: " << endl << SOIL_last_result() << endl;
		}
	}

	// Pegando a textura da explosao
	// Existem 20 imagens da explosao, o nome delas e
	// src/resources/explosion/bubble_exploi.png, sendo que i vai de 1 a 40.
	for (int i = 0; i < this->amountExplosionImage; i++) {
		char *str = Utils::concatValue("src/resources/explosion/bubble_explo", (i + 1));
		str = Utils::concatChar(str, ".png");

		this->explosionTexture[i] = SOIL_load_OGL_texture(
				str,
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y
		);

		if (this->explosionTexture[i] == 0) {
			cout << "Algo de errado não está certo com a textura: " << endl << SOIL_last_result() << endl;
		}
	}
}

/***
 * Informa se o motor esta ligado ou desligado
 */
void SpacecraftController::setPowerMotor(bool power) {
	this->motorPower = power;
	this->acceleration[1] = power && this->fuel > 0 ? Params::POWER_ACCELERATION : Params::INITIAL_ACCELERATION;
}

/***
 * Informa que o motor para esquerda esta ligado
 */
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

/***
 * Informa que o motor para direita esta ligado
 */
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

/***
 * Atualiza respectivamente a velocidade e a posicao da nave com base na aceleracao
 */
void SpacecraftController::updatePosition() {

	// Caso a nave tenha explodido nao e necessario desenha-la
	if (!this->explosion) {

		long currentTime = time(0);
		float time = (currentTime - this->lastTime);

		if (acceleration[1] > 0) {
			this->fuel--;
			this->spentFuel++;
		}

		float newSpeed = acceleration[0] * Params::UNITY_PER_METER;
		if (newSpeed <= 3 * Params::MAX_SPEED && newSpeed >= -3 * Params::MAX_SPEED)
			speed[0] = newSpeed;

		newSpeed = speed[1] + acceleration[1] * Params::UNITY_PER_METER;
		if (newSpeed <= 2 * Params::MAX_SPEED && newSpeed >= -2 * Params::MAX_SPEED)
			speed[1] = newSpeed;

		this->position->updateBySpeed(speed, time, acceleration[1] > 0);

		this->lastTime = currentTime;
	}


	if (this->motorPower) {
		this->countFireImage++;
		if (this->countFireImage >= this->amountFireImage) {
			this->countFireImage = 0;
		}
	} else {
		this->countFireImage = 0;
	}

	if (this->explosion) {

		if (this->countExplosionImage + 1 <= this->amountExplosionImage) {
			this->countExplosionImage++;
		}
	}
}

void SpacecraftController::setRotate() {
	float x = this->position->getX() - Params::SPACECRAFT_WIDTH / 2;
	float y = this->position->getY();

	glTranslatef(x, y, 0);
	glRotatef(-30 * this->acceleration[0], 0, 0, 1);
}

void SpacecraftController::drawSpacecraft() {
	if (this->spacecraftTexture == NULL) {
		this->initTexture();
	}

	glPushMatrix();

	this->setRotate();

	// Desenhando a nave
	if (!this->explosion || this->countExplosionImage < 6) {
		float x = this->position->getX() - Params::SPACECRAFT_WIDTH / 2;
		float y = this->position->getY() - Params::SPACECRAFT_HEIGHT / 2;

		glEnable(GL_TEXTURE_2D);
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, this->spacecraftTexture);
		glBegin(GL_POLYGON);
			glTexCoord2f(0,0); 	glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0);	glVertex3f(Params::SPACECRAFT_WIDTH, 0, 0);
			glTexCoord2f(1, 1);	glVertex3f(Params::SPACECRAFT_WIDTH, Params::SPACECRAFT_HEIGHT, 0);
			glTexCoord2f(0, 1);	glVertex3f(0, Params::SPACECRAFT_HEIGHT, 0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}

	//Desenhando a explosao
	if (this->explosion) {
		glEnable(GL_TEXTURE_2D);
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, this->explosionTexture[this->countExplosionImage]);
		glBegin(GL_POLYGON);
			glTexCoord2f(0,0); 	glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0);	glVertex3f(Params::SPACECRAFT_WIDTH, 0, 0);
			glTexCoord2f(1, 1);	glVertex3f(Params::SPACECRAFT_WIDTH, Params::SPACECRAFT_HEIGHT, 0);
			glTexCoord2f(0, 1);	glVertex3f(0, Params::SPACECRAFT_HEIGHT, 0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}

	//Desenhando o foguinho da nave
	if (this->motorPower && !this->explosion && this->fuel > 0) {
		// Desenhar fogo
		glEnable(GL_TEXTURE_2D);
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, this->fireTexture[this->countFireImage]);
		glBegin(GL_POLYGON);
			glTexCoord2f(0,0); 	glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0);	glVertex3f(Params::SPACECRAFT_WIDTH, 0, 0);
			glTexCoord2f(1, 1);	glVertex3f(Params::SPACECRAFT_WIDTH, -Params::FIRE_SIZE, 0);
			glTexCoord2f(0, 1);	glVertex3f(0, -Params::FIRE_SIZE, 0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}

float *SpacecraftController::getAcceleration() {
	return this->acceleration;
}

float *SpacecraftController::getSpeed() {
	return this->speed;
}

Coordinate *SpacecraftController::getSpacecraftPosition() {
	return this->position;
}

void SpacecraftController::setExplosion(bool explosion) {
	this->explosion = explosion;
	this->countExplosionImage = 0;
}
