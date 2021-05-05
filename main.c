#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_functions.c"

int main(){

	carta cartas[52];
	pegar_cartas(cartas);
	int seeds[2];
	pegar_sementes(seeds);

	jogador player1, player2;

	player1.numero = 1;
	printf("Digite o nome do primeiro jogador: ");
	fflush(stdin);
	gets(player1.nome);
	player1.turno = 1;
	player1.pontuacao = 0;

	player2.numero = 2;
	printf("Digite o nome do segundo jogador: ");
	fflush(stdin);
	gets(player2.nome);
	player2.turno = 0;
	player2.pontuacao = 0;
	
	inicializar_fila(&player1.baralho);
	inicializar_fila(&player2.baralho);

	int i;
	for(i = 0; i < 4; i++){
		inicializar_deque(&player1.jogo[i]);
		inicializar_deque(&player2.jogo[i]);
	}

	inicializar_pilha(&player1.cartasInteresse);
	inicializar_pilha(&player2.cartasInteresse);

	embaralhar(&player1.baralho, cartas, seeds[0]);
	embaralhar(&player2.baralho, cartas, seeds[1]);

	jogador *ganhador = jogar(&player1, &player2);

	printf("Parabens %s, você ganhou!! ", ganhador->nome);

	return 0;
}