/*
 * Params.h
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#ifndef MODELS_PARAMS_H_
#define MODELS_PARAMS_H_

class Params {
public:
	Params();
	virtual ~Params();
	static int LEVEL_MAX;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static int RUNWAY_WIDTH;
	static int SPACECRAFT_WIDTH;
	static int SPACECRAFT_HEIGHT;
	static int ALPHA_HEIGHT;
	static float INITIAL_ACCELERATION;
	static float POWER_ACCELERATION;
	static float POWER_DIRECTION_ACCELERATION;
	static float UNITY_PER_METER;
	static float MAX_SPEED;

	static float LIFES_SIZE;

	static int INITIAL_FUEL;
	static int MINIMUM_FUEL;

	static int INITIAL_LIFES;
	static float FIRE_SIZE;

	static float TEXT_POSITION;
	static float TEXT_INCREMENT_POSITION;

	static float MENU_POSITION_X;
	static float MENU_POSITION_Y;
	static float MENU_INCREMENT_POSITION;

	static int UPDATE_TIME;

	static int MOTOR_BUTTON;
	static int RIGHT_BUTTON;
	static int LEFT_BUTTON;
	static int PAUSE_BUTTON;
};

#endif /* MODELS_PARAMS_H_ */
