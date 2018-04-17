# lunarlander
> TP 01 computação gráfica

## Descrição
Implementação do jogo Lunar Lander em C++ usando OpenGL, FreeGlut e Soil.
A implementacao possui 2 camadas:
1. models: possui os modelos utilizados para o desenvolvimento das regras do jogo
1. controllers: possui os controladores de visulizacao, é responsavel pelas regras de negocio

A classe Main informa as funções de callback da GLUT. Todas as funções de callback estão na classe Controller, que é o controle principal do jogo, todos os outros controles se comunicam com ela. Ela chama todos os controles que precisam desenhar na tela.


Funcionalidades extras implementadas:
Superficie nao plana
Geracao aleatória da superficie
Fases infinitas
Texturas animadas - Nave espatifando
Fundo lindão
Vidas
Pontuação
Fogo/explosão