/*
 * Params.cpp
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#include "Params.h"

Params::Params() {
	// TODO Auto-generated constructor stub
}

Params::~Params() {
	// TODO Auto-generated destructor stub
}

// Tamanho do mundo
int Params::SCREEN_WIDTH = 100;
int Params::SCREEN_HEIGHT = 100;

// Tamanho da pista de pouso
int Params::RUNWAY_WIDTH = 13;

// Tamanho da nave
int Params::SPACECRAFT_WIDTH = 8;
int Params::SPACECRAFT_HEIGHT = 12;

// Variavel para correcao da altura da nave em relacao a textura.
int Params::ALPHA_HEIGHT = 5;

// Valores das aceleracoes
float Params::INITIAL_ACCELERATION = -0.00580665;
float Params::POWER_ACCELERATION = 0.00580665;
float Params::POWER_DIRECTION_ACCELERATION = 0.13;


float Params::UNITY_PER_METER = 1;

// Valores maximos permitidos no jogo
float Params::MAX_SPEED_LANDER = -0.4;
float Params::MAX_ROTATION_LANDER = 0.1;
float Params::MAX_SPEED = 0.5;

// Tamanho da estrelinha que representa uma vida na HUD
float Params::LIFES_SIZE = 1.5;


// Valor inicial de quantidade de combustivel
int Params::INITIAL_FUEL = 400;
// Valor minimo para iniciar o combustivel
int Params::MINIMUM_FUEL = 80;

// Quantidade inicial de vidas
int Params::INITIAL_LIFES = 3;

// Tamanho do poligono que representa o foguinho da nave
float Params::FIRE_SIZE = 12;

// Posicao do texto na tela de pausa, de fase, e de confirmacao
float Params::TEXT_POSITION = 95;
float Params::TEXT_INCREMENT_POSITION = 2;

// Posicao texto da tela de menu
float Params::MENU_POSITION_X = 35;
float Params::MENU_POSITION_Y = 50;
float Params::MENU_INCREMENT_POSITION = 8;

// Tempo que a tela sera atualizar novamente
int Params::UPDATE_TIME = 20;
