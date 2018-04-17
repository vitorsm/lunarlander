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
O Controller é a classe de controle principal do jogo, ele importa todas as outras classes de controle, ou seja, as demais classes de controle estão no mesmo nível:
* ```BackgroundController```: Responsavel por desenhar o background do jogo, apenas coloca uma imagem no fundo.
* ```ConfirmController```: Responsavel por desenhar uma tela de confirmação com um texto variavel, o texto é setado. Existem apenas duas opções: Sim ou Não.
* ```FloorController```: Controle responsavel por tudo que é referente ao chão, como por exemplo: gerar o chão aleatoriamente com base na fase que o jogador está, informar se a nave tocou o chão, ou se a nave está na pista de pouso.
* ```HUDController```: Controle de HUD, coloca os dados de status do para a visualizacao do jogador na tela, como por exemplo: quantidade de vidas, quantiadade de combustível, velocidade e etc.
* ```InstructionsController```: Apenas exibe as instruções do jogo.
* ```LevelController```: Exibe a tela que mostra o status do fim da fase, informando se o jogador passou de fase ou se não passou, e no caso de não ter passado, informa o motivo do fracasso.
* ```MenuController```: Controle do menu principal.
* ```PauseController```: Responsavel pelo pause do jogo, implementa opções de voltar ao jogo, reiniciar o jogo ou voltar ao menu principal.
* ```SpacecraftController```: Controle da nave espacial, atualiza os dados de velocidade e posicao, com base na aceleração. É reponsavel por exibir o "foguinho" da nave e no caso de explosão, desenhá-la na tela.

O código do jogo possui comentários para explicação de partes onde existe alguma logica complexa.

## Estrutura de diretorios
```
lunarlander
│   README.md
|   makefile
│___images
│
└───src
    │   Main.cpp
    │   Utils.cpp
    │   Utils.h
    │
    └───models
    |
    └───controllers
    |
    └───resources

```

## makefile
Para executar o jogo basta estar no diretorio raiz e executar o comando make, após o jogo ser compilado basta usar o comando make run

## Resultado
Tela inicial do jogo contendo as 3 opções do Menu principal. 
![Tela inicial do jogo](/images/1_menu-principal.png)

Jogo sendo executado
![Jogo rodando](/images/2_jogo-rodando.png)

Tela exibida no fim de uma fase ( ```LevelController``` )
![Fim de jogo](/images/3_tela-fim-de-jogo.png)

Tela de pause contendo as 3 opções de menu pause
![Pause](/images/4_tela-pause.png)

Tela exibida quando o jogador deseja reinicar ou fechar o jogo, variando apenas o texto de confirmçaõ
![Tela de confirmação](/images/5_tela-confirmacao.png)

Tela exibida quando o jogador morre
![Jogador morreu](/images/6_tela-fim-de-jogo-perdeu.png)

Tela exibida quando game over
![Game over](/images/7_tela-game-over.png)

## Funcionalidades extras implementadas

* Superficie nao plana
* Geracao aleatória da superficie
* Fases infinitas
* Texturas animadas - Nave espatifando
* Fundo lindão
* Vidas
* Pontuação
* Fogo/explosão
* Telas do jogo

