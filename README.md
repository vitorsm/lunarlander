# lunarlander
> TP 01 computação gráfica

## Descrição
Implementação do jogo Lunar Lander em C++ usando OpenGL, FreeGlut e Soil.
A implementacao possui 2 camadas:
1. models: possui os modelos utilizados para o desenvolvimento das regras do jogo
1. controllers: possui os controladores de visulizacao, é responsavel pelas regras de negocio

A classe Main informa as funções de callback da GLUT. Todas as funções de callback estão na classe Controller, que é o controle principal do jogo, todos os outros controles se comunicam com ela. Ela chama todos os controles que precisam desenhar na tela:

```c
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
```
### Controles
Os controles implementados são:
* ```c BackgroundController```: Responsavel por desenhar o background do jogo, é apenas uma imagem de fundo.

Funcionalidades extras implementadas:
Superficie nao plana
Geracao aleatória da superficie
Fases infinitas
Texturas animadas - Nave espatifando
Fundo lindão
Vidas
Pontuação
Fogo/explosão