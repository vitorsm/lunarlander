/*
 * Controller.cpp
 *
 *  Created on: 3 de abr de 2018
 *      Author: vitor
 */

#include "Controller.h"

const int LEFT_BUTTON = 100;
const int RIGHT_BUTTON = 102;
const int MOTOR_BUTTON = 32;
const int ESC_BUTTON = 27;
const int PAUSE_BUTTON = 'p';
const int ENTER_BUTTON = 13;
const int EXIT_BUTTON = 27;
const int RESTART_BUTTON = 'r';

bool Controller::powerMotor = false;
long Controller::lastTimePowerMotor = 0;
long Controller::lastTimePowerDirection = 0;

Controller::Controller() {
}

Controller::~Controller() {
}

//Controlador de background, apenas exibe a imagem de fundo
BackgroundController	*Controller::backgroundController = new BackgroundController();
// Controlador do menu principal, apenas exibe as opcoes de iniciar jogo, instrucoes e sair do jogo
MenuController 			*Controller::menuController = new MenuController();
// Controlador do chao, e responsavel por verificacoes referentes ao chao e pela geracao aleatorio do chao
FloorController 		*Controller::floorController = new FloorController();
// Controlador da nave, responsavel por tudo referente a nava, como velocidade, posicao, explosao, etc.
SpacecraftController 	*Controller::spacecraftController = new SpacecraftController(floorController);
// Controlador de HUD, apenas exibe os dados pre definidos
HUDController 			*Controller::hudController = new HUDController();
// Controlador de pause, exibe as opcoes do menu pause
PauseController			*Controller::pauseController = new PauseController();
// Controlador de fase, exibe o status de quando uma fase termina, informando se o jogador passou ou nao de fase
LevelController			*Controller::levelController = new LevelController();
//Controlador de instrucoes, apenas exibe as instrucoes e teclas do jogo
InstructionsController	*Controller::instructionsController = new InstructionsController();
// Controlador de confirmacacao, utilizado para confirmar acoes de fechar o jogo e reiniciar o jogo
ConfirmController		*Controller::confirmController = new ConfirmController();

//Fase que o jogador esta
int Controller::level = 1;
// Quantidade de vidas que o jogador tem
int Controller::lifes = Params::INITIAL_LIFES;
// Pontuacao total do jogador
int Controller::scores = 0;
// Variavael que informa se o jogo esta pausado
bool Controller::pause = false;
// Variavel que informa se o jogo esta no menu
bool Controller::menu = true;
// Variavel que informa se a tela de status do fim do jogo esta sendo exibida
bool Controller::startLevel = false;
// Variavel que informa se a explosao da nave foi iniciada.
// E necessaria pq a explosao possui varios frames, e so depois que ela termina o jogo para
bool Controller::exploded = false;
// Variavel que informa se o jogador esta na tela de instrucoes
bool Controller::instructions = false;
// Variavel que informa se o jogador esta na tela de confirmacao pq quer reinicar o jogo
bool Controller::restart = false;
// Variavel que informa se o jogador esta na tela de confirmacao pq quer fechar o jogo
bool Controller::exitGame = false;

void Controller::keyboardNotAsciiCallback(int key, int x, int y) {

	switch(key) {
	case GLUT_KEY_LEFT:
		spacecraftController->setLeftPower();
		lastTimePowerDirection = time(0);
		break;
	case GLUT_KEY_RIGHT:
		spacecraftController->setRightPower();
		lastTimePowerDirection = time(0);
		break;
	case GLUT_KEY_UP:
		powerMotor = true;
		lastTimePowerMotor = time(0);
		if (restart || exitGame) confirmController->setUpMenu();
		if (menu) menuController->setUpMenu();
		if (startLevel) levelController->setUpMenu();
		if (pause) pauseController->setUpMenu();
		break;
	case GLUT_KEY_DOWN:
		if (restart || exitGame) confirmController->setDownMenu();
		if (menu) menuController->setDownMenu();
		if (startLevel)levelController->setDownMenu();
		if (pause) pauseController->setDownMenu();
		break;
	default:
		break;
	}

}

void Controller::keyboardCallback(unsigned char key, int x, int y) {
	int value = key;

	switch(key) {
	case MOTOR_BUTTON:
		powerMotor = true;
		lastTimePowerMotor = time(0);
		break;
	case PAUSE_BUTTON:
		pause = !pause;
		break;
	case ENTER_BUTTON:
		clickMenu();
		break;
	case RESTART_BUTTON:
		restart = true;
		confirmController->setMessage("Deseja reiniciar o jogo");
		break;
	case EXIT_BUTTON:
		exitGame = true;
		confirmController->setMessage("Deseja sair do jogo");
		break;
	default:
		break;
	}
}

void Controller::drawScene() {

	glClear(GL_COLOR_BUFFER_BIT);

	// Verifica se o menu está selecionado
	// Caso ele esteja selecinado só é necessário desenhar ele
	// Idem para instruções
	if (menu) {
		menuController->drawMenu();
	} else if (instructions) {
		instructionsController->drawInstructions();
	} else {
		// Inicia o desenho do jogo

		// Primeiro é desenhado o fundo
		backgroundController->drawBackground();
		//Desenho da nave
		spacecraftController->drawSpacecraft();
		//Desenho do chão
		floorController->drawFloor();
		//Desenho da HUD
		hudController->drawHUD();

		// Caso o restart ou exitGame estejam selecionados, exibe-se a tela de confirmação
		// As 3 telas (confirmacao, level e pause) possuem um fundo com alpha 0.5, ou seja,
		// O jogo continua aparecendo no background.
		if (restart || exitGame) {
			// Desenho da tela de confirmacao, com opcoes de sim ou nao
			confirmController->drawConfirm();
		} else if (startLevel) {
			// Desenho da tela que exibe o status do fim do jogo em uma fase,
			// informa se o jogador passou ou não de fase, além de mostrar a pontuacao do jogador
			levelController->drawLevel();
		} else if (pause) {
			//Desenho da tela de pause com opcoes de voltar ao jogo, reiniciar o jogo e ir ao menu principal
			pauseController->drawPause();
		}

	}

	glutSwapBuffers();
}

void Controller::update(int idx) {

	// Se não estiver no menu, jogo pausado, informando o status do fim do jogo,
	// ou em tela de confirmacao (restart e exitGame)
	// As variaveis do jogo devem ser atualizadas
	if (!menu && !pause && !startLevel && !restart && !exitGame) {
		// Logica para verificar se a tecla de motor parou de ser pressionada
		// Se o tempo agora for diferente do tempo quando apertou-se a tecla do motor
		// considera-se que ele esta desligado.
		if (time(0) != lastTimePowerMotor) {
			powerMotor = false;
		}

		// Seta no controle da nave o status do motor
		// se powerMotor == true -> motor ligado
		// se powerMotor == false -> motor desligado
		spacecraftController->setPowerMotor(powerMotor);
		// Atualiza a posicao da nave com base nas novas atualizacoes
		spacecraftController->updatePosition();

		float *speed = spacecraftController->getSpeed();
		// Atualiza os dados da HUD
		// (velocidade da nave, altura da nave, rotacao, vidas, fase, qtd de combustivel)
		hudController->updateData(speed[1], spacecraftController->getSpacecraftPosition()->getY(),
				speed[0], lifes, level, spacecraftController->getFuel());

		// Seta no controlador de fase se a nave estava acima da velocidade maxima permitida para pouso
		// e se a nave estava com uma rotacao acima da rotacao permitida para pouso
		// Dessa forma, e possivel informar ao jogador o motivo de nao ter conseguido pousar a nave.
		levelController->setMaxSpeed(speed[1] < Params::MAX_SPEED_LANDER,
									speed[0] < -Params::MAX_ROTATION_LANDER || speed[0] > Params::MAX_ROTATION_LANDER);

		Coordinate *spacecraftPosition = spacecraftController->getSpacecraftPosition();

		// Verifica se a nave esta encostando no chao
		if (floorController->isOnTheFloor(spacecraftPosition)) {
			// Se a nave estiver encostando no chao, e necessario saber se ela esta na area de pouso
			// E tambem e verificado se a nave esta com a velocidade e rotacao permitida para o pouso
			if (floorController->isOnTheRunway(spacecraftPosition) &&
					(speed[0] > -Params::MAX_ROTATION_LANDER && speed[0] < Params::MAX_ROTATION_LANDER &&
							speed[1] > Params::MAX_SPEED_LANDER)) {
				// Se isso for verdade, e necessario atualizar a vitoria
				// Incrementa a variavel level, para subir um nivel
				level++;
				// Atualiza os pontos do jogador
				calculateScore();
				// Gera-se um novo chao, aleatorio, para a proxima fase
				floorController->generateFloor(level);
				levelController->setLevel(level);
				// Seta o startLevel = true para ser exibido a tela de informacao de status do fim da fase,
				// informando que o jogador passou de fase e sua pontuacao
				startLevel = true;
			} else {
				// Nesse caso a nave se espatifou
				if (!exploded) {
					// Se ainda nao explodiu, e necessario atualizar a derrota
					lifes--;
					// Informa ao controlador da nave que ela explodiu
					spacecraftController->setExplosion(true);
					// Seta o ultimo level no controlador de level, dessa forma, sera exibida uma mensagem
					// para o jogador tentar novamente, e nao como se fosse a primeira vez que tentasse a fase
					levelController->setLastLevel(lifes);
					// Seta a variavel para informar que iniciou a explosao
					exploded = true;
				} else {
					// Verifica se todos os frames da explosao ja foram executados, se sim a variavel
					// startLevel e setada com true, para ser exibida a tela de status de fim do jogo
					if (spacecraftController->getCountExplosionImage() >= spacecraftController->getAmountExplosionImage()) {
						exploded = false;
						startLevel = true;
					}

				}
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(Params::UPDATE_TIME, update, 0);

}

/***
 * Funcao que e chamada quando o jogador clica no enter
 */
void Controller::clickMenu() {
	int selected = 0;

	//Verifica se o jogador esta no menu
	if (menu) {
		selected = menuController->getSelectedMenu();

		if (selected == MenuController::START_GAME_MENU_ITEM) {
			level = 1;
			lifes = Params::INITIAL_LIFES;
			initLevel();
			menu = false;
		} else if (selected == MenuController::INSTRUCTION_MENU_ITEM) {
			instructions = true;
			menu = false;
		} else if (selected == MenuController::EXIT_MENU_ITEM) {
			exit(0);
		}
	} else if (restart) {
		// Verifica se o jogador esta na tela de confirmacao pq quer reinicar o jogo
		restart = false;
		if (confirmController->getSelectedMenu() == ConfirmController::YES_MENU_ITEM)
			initLevel();
	} else if (exitGame) {
		// Verifica se o jogador esta na tela de confirmacao pq quer fechar o jogo
		exitGame = false;
		if (confirmController->getSelectedMenu() == ConfirmController::YES_MENU_ITEM)
			cout << "vai fechar o jogo" << endl;
			exit(0);
	} else if (startLevel) {
		// Verifica se o jogador esta na tela de status de fim de jogo
		selected = levelController->getSelectedMenu();

		if (selected == LevelController::CONTINUE_MENU_ITEM) {
			startLevel = false;
			initLevel();
		} else if (selected == LevelController::MENU_MENU_ITEM) {
			startLevel = false;
			menu = true;
		}
	} else if (pause) {
		// Verifica se o jogador esta na tela de pause
		selected = pauseController->getSelectedMenu();

		if (selected == PauseController::RESUME_GAME_MENU_ITEM) {
			pause = false;
		} else if (selected == PauseController::RESTART_GAME_MENU_ITEM) {
			initLevel();
			pause = false;
		} else if (selected == PauseController::MENU_MENU_ITEM) {
			menu = true;
			pause = false;
		}
	} else if (instructions) {
		menu = true;
		instructions = false;
	}

}

/***
 * Funcao chamada quando e necessario iniciar o level
 */
void Controller::initLevel() {
	floorController->generateFloor(level);
	spacecraftController->setInitialPosition();
	spacecraftController->setInitialFuel(level);
}

/***
 * Funcao de calculo de pontuacao
 */
void Controller::calculateScore() {
	float score = level * 3; //A pontuacao e proporcial ao numero da fase

	if (spacecraftController->getSpentFuel() > 0) {
		score += Params::INITIAL_FUEL / spacecraftController->getSpentFuel();
		// a pontuacao e inversamente proporcional a quantidade de combustivel gasto
	}
	float rotation = spacecraftController->getSpeed()[0];
	if (rotation < 0) rotation = -rotation;

	// A pontuacao e inversamente proporcional a rotacao da nave, ou seja,
	// quanto mais reta esta estiver maior a pontuacao
	score -= 3 * rotation;

	scores += score;
	// Seta no controlador de fase as pontuacoes para serem exibidas ao usuario
	levelController->setScores(score, scores);
}
