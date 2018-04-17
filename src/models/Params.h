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
	// Tamanho do mundo
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;

	// Tamanho da pista de pouso
	static int RUNWAY_WIDTH;

	// Tamanho da nave
	static int SPACECRAFT_WIDTH;
	static int SPACECRAFT_HEIGHT;

	// Variavel para correcao da altura da nave em relacao a textura.
	static int ALPHA_HEIGHT;

	// Valores das aceleracoes
	static float INITIAL_ACCELERATION;
	static float POWER_ACCELERATION;
	static float POWER_DIRECTION_ACCELERATION;

	static float UNITY_PER_METER;

	// Valores maximos permitidos no jogo
	static float MAX_SPEED;
	static float MAX_SPEED_LANDER;
	static float MAX_ROTATION_LANDER;

	// Tamanho da estrelinha que representa uma vida na HUD
	static float LIFES_SIZE;

	// Valor inicial de quantidade de combustivel
	static int INITIAL_FUEL;
	// Valor minimo para iniciar o combustivel
	static int MINIMUM_FUEL;

	// Quantidade inicial de vidas
	static int INITIAL_LIFES;

	// Tamanho do poligono que representa o foguinho da nave
	static float FIRE_SIZE;

	// Posicao do texto na tela de pausa, de fase, e de confirmacao
	static float TEXT_POSITION;
	static float TEXT_INCREMENT_POSITION;

	// Posicao texto da tela de menu
	static float MENU_POSITION_X;
	static float MENU_POSITION_Y;
	static float MENU_INCREMENT_POSITION;

	// Tempo que a tela sera atualizar novamente
	static int UPDATE_TIME;
};

#endif /* MODELS_PARAMS_H_ */
