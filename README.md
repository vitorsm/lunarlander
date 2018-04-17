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

	if (menu) {
		menuController->drawMenu();
	} else if (instructions) {
		instructionsController->drawInstructions();
	} else {
		backgroundController->drawBackground();
		spacecraftController->drawSpacecraft();
		floorController->drawFloor();
		hudController->drawHUD();
	}

	glutSwapBuffers();
}
```

### Controles
O Controller é a classe de controle principal do jogo, ele importa todas as classes de controle do jogo, ou seja, todas as outras classes de controle estão no mesmo nível:
* ```BackgroundController```: Responsavel por desenhar o background do jogo, apenas coloca uma imagem no fundo.
* ```ConfirmController```: Responsavel por desenhar uma tela de confirmação com um texto variavel, o texto é setado. Existem apenas duas opções: Sim ou Não
*```FloorController```: Controle responsavel por tudo que é referente ao chão, como por exemplo: gerar o chão aleatoriamente com base na fase que o jogador está, informar se a nave tocou o chão, ou se a nave está na pista de pouso.
*```HUDController```: Controle de HUD, coloca os dados de status do para a visualizacao do jogador na tela, como por exemplo: quantidade de vidas, quantiadade de combustível, velocidade e etc.
*```InstructionsController```: Apenas exibe as instruções do jogo.
*```LevelController```: Exibe a tela que mostra o status do fim da fase, informando se o jogador passou de fase ou se não passou, e no caso de não ter passado, informa o motivo do fracasso.
*```MenuController```: Controle do menu principal.
*```PauseController```: Responsavel pelo pause do jogo, implementa opções de voltar ao jogo, reiniciar o jogo ou voltar ao menu principal.
*```SpacecraftController```: Controle da nave espacial, atualiza os dados de velocidade e posicao, com base na aceleração. É reponsavel por exibir o "foguinho" da nave e no caso de explosão, desenhá-la na tela.

O código do jogo possui comentários para explicação de partes onde existe alguma logica complexa.

## Resultado
![Tela inicial do jogo](/images/1_menu-principal.png)
Format: ![Imagem mostrando a tela inicial do jogo]
## Funcionalidades extras implementadas

* Superficie nao plana
* Geracao aleatória da superficie
* Fases infinitas
* Texturas animadas - Nave espatifando
* Fundo lindão
* Vidas
* Pontuação
* Fogo/explosão