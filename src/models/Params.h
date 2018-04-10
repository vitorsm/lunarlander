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
	static float INITIAL_ACCELERATION;
	static float POWER_ACCELERATION;
	static float POWER_DIRECTION_ACCELERATION;
	static float UNITY_PER_METER;
	static float MAX_SPEED;

	static int MOTOR_BUTTON;
	static int RIGHT_BUTTON;
	static int LEFT_BUTTON;
	static int UPDATE_TIME;
};

#endif /* MODELS_PARAMS_H_ */
