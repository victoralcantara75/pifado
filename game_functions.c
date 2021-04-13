#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.c"
#define TAM_CARTAS 52
#define TAM_ESPACO 4

void pegar_cartas(carta *baralho){

	printf("Pegando cartas...\n");
	baralho[0].display = 'A';
	int i;
	for (i = 0; i<52; i++){
		if(i == 0 || i == 13 || i == 26 || i == 39) {
		    baralho[i].display = 'A';
		    baralho[i].valor = 1;
		}
		if(i == 1 || i == 14 || i == 27 || i == 40) {
		    baralho[i].display = '2';
		    baralho[i].valor = 2;
		}
		if(i == 2 || i == 15 || i == 28 || i == 41) {
		    baralho[i].display = '3';
		    baralho[i].valor = 3;
		}
		if(i == 3 || i == 16 || i == 29 || i == 42) {
		    baralho[i].display = '4';
		    baralho[i].valor = 4;
		}
		if(i == 4 || i == 17 || i == 30 || i == 43) {
		    baralho[i].display = '5';
		    baralho[i].valor = 5;
		}
		if(i == 5 || i == 18 || i == 31 || i == 44) {
		    baralho[i].display = '6';
		    baralho[i].valor = 6;
		}
		if(i == 6 || i == 19 || i == 32 || i == 45) {
		    baralho[i].display = '7';
		    baralho[i].valor = 7;
		}
		if(i == 7 || i == 20 || i == 33 || i == 46) {
		    baralho[i].display = '8';
		    baralho[i].valor = 8;
		}
		if(i == 8 || i == 21 || i == 34 || i == 47) {
		    baralho[i].display = '9';
		    baralho[i].valor = 9;
		}
		if(i == 9 || i == 22 || i == 35 || i == 48) {
		    baralho[i].display = '0';
		    baralho[i].valor = 10;
		}
		if(i == 10 || i == 23 || i == 36 || i == 49) {
		    baralho[i].display = 'J';
		    baralho[i].valor = 11;
		}
		if(i == 11 || i == 24 || i == 37 || i == 50) {
		    baralho[i].display = 'Q';
		    baralho[i].valor = 12;
		}
		if(i == 12 || i == 25 || i == 38 || i == 51) {
		    baralho[i].display = 'K';
		    baralho[i].valor = 13;
		}
		
		if (i < 13)
			baralho[i].naipe = 3;
		else if (i < 26)
			baralho[i].naipe = 4;
		else if (i < 39)
			baralho[i].naipe = 5;
		else
			baralho[i].naipe = 6;
	}
	
}

void pegar_sementes(int *seeds){
	int i;
	srand(time(NULL));
	// srand(42);
	for (i = 0; i < 2; i++)
		seeds[i] = rand() % 100;
 }
 
void embaralhar(fila *baralho, carta *cartas, int seed){
	
	printf("Embaralhando...\n");
	int index, jaExiste, i;
	
	lista elementosJaSorteados;
	inicializar_lista(&elementosJaSorteados);
	srand(seed);
	
	for (i = 0; i < 52; i++){
		do{
			index = (rand() % 51)+1;
			jaExiste = existeElemento(&elementosJaSorteados, index);
		}while(jaExiste);
	
		adicionar(&elementosJaSorteados, index);
		enfileirar(baralho, cartas[index]);
	}
}

jogador *pegar_turno(jogador *player1, jogador *player2){
	
	if(player1->turno == 1)
		return player1;
	return player2;
}

void imprimirJogos(jogador player){
	int i;
	system("cls || clear");
	printf("Pontuacao: %d\n", player.pontuacao);
	printf("Meus jogos: \n");
	for (i = 0; i < 4 ; i++){
			printf("%d - [", i);
			imprimirDeque(&player.jogo[i]);
			printf("]\n");
		}
	if(!pilha_vazia(&player.cartasInteresse))
		printf("Carta de interesse: %c%c \n", player.cartasInteresse.ptrtopo->info.display,
									   		  player.cartasInteresse.ptrtopo->info.naipe);
}

int cartaIgual(deque d, carta carta){
	int i;
	for (i = 0; i < 4; i++){
		if(d.info[i].valor == carta.valor)
			return 1;
	}
	return 0;
}

int cartaMaior(deque d, carta carta){

	int var = d.fim -1;
	if(d.fim == 0)
		var = TAM_ESPACO -1;

	if(d.info[var].valor+1 == carta.valor || (d.info[var].valor == 13 && carta.valor == 1))
		return 1;
	return 0;
}

int cartaMenor(deque d, carta carta){
	if(d.info[d.inicio].valor-1 == carta.valor || (d.info[d.inicio].valor == 1 && carta.valor == 13))
		return 1;
	return 0;
}

int verificarJogo(deque d){

	int iguais = 0, sequencia = 0;
	int primeiro = d.inicio;
	int segundo = (primeiro+1)%TAM_ESPACO;
	int terceiro = (segundo+1)%TAM_ESPACO;

	if (d.info[primeiro].valor == d.info[segundo].valor && d.info[segundo].valor == d.info[terceiro].valor)
		iguais = 1;
	else if ((d.info[primeiro].valor + 1 == d.info[segundo].valor || d.info[primeiro].valor == 13 && d.info[segundo].valor == 1)
				&&
			 (d.info[segundo].valor + 1 == d.info[terceiro].valor || d.info[segundo].valor == 13 &&  d.info[terceiro].valor == 1))
		sequencia = 1;

	if (sequencia || iguais)
		return 1;
	return 0;
}

int realizarAcao(jogador *player, carta carta, int escolha){
	if(escolha == 1){
		int jogo, completo = 0, inserido = 0, voltar = 0;
		imprimirJogos(*player);

		do{
			do{
				printf("(Digite -1 para voltar)\n");
				printf("A qual jogo quer adicionar a carta %c%c: ", carta.display, carta.naipe);
				scanf("%d", &jogo);
			}while(jogo < -1 || jogo > 3);
			
			if (jogo == -1)
				return 0;

			deque *d = &player->jogo[jogo];

			if (deque_vazio(d) || cartaIgual(*d, carta) || cartaMenor(*d, carta)){
				if (inserirInicio(d, carta))
					inserido = 1;
			}
			else if (cartaMaior(*d, carta)){
				if(inserirFinal(d, carta))
					inserido = 1;
			}
			else
				inserido = 0;

			imprimirJogos(*player);

			if (deque_cheio(d)){
				printf("verificar? %d\n", verificarJogo(*d));
				completo = verificarJogo(*d);
			}
				
			if (completo){
				printf("Jogo feito!");
				player->pontuacao++;
				inicializar_deque(d);
			}
		}while(!inserido);
	}
	if(escolha == 2){
		printf("Empilhando a carta %c%c nas cartas de interesse\n", carta.display, carta.naipe);
		push(&player->cartasInteresse, carta);
	}
	if(escolha == 3){
		printf("Enfileirando a carta %c%c no baralho.. \n", carta.display, carta.naipe);
		enfileirar(&player->baralho, carta);
	}
	if(escolha == 4){
		imprimirJogos(*player);
		return 0;
	}
	system("pause");
	return 1;
}

jogador *jogar(jogador *player1, jogador *player2){
	
	int escolha, inserido, retirada;
	jogador *player;
	carta carta;

	do
	{
		player = pegar_turno(player1, player2);

		do{
			retirada = 1;
			system("cls || clear");
			printf("Vez de %s \n", player->nome);
			printf("Pontuacao: %d\n", player->pontuacao);
			if (!pilha_vazia(&player->cartasInteresse)){
				printf("Carta de interesse: %c%c\n", player->cartasInteresse.ptrtopo->info.display,
												 player->cartasInteresse.ptrtopo->info.naipe);
				printf("Escolha: \n");
				printf("1 - Comprar do monte \n");
				printf("2 - Retirar das cartas de interesse \n");
				scanf("%d", &retirada);
			}
			
		}while(retirada != 1 && retirada != 2);
		
		if (retirada == 1)
			carta = desenfileirar(&player->baralho);
		else if (retirada == 2)
			carta = pop(&player->cartasInteresse);

		do{
			system("cls || clear");
			printf("Vez de %s \n", player->nome);
			printf("Pontuacao: %d\n", player->pontuacao);
			printf("Carta retirada: %c%c \n", carta.display, carta.naipe);
			printf("1 - Adicionar a um jogo \n");
			printf("2 - Adicionar como carta de interesse \n");
			printf("3 - Descartar \n");
			printf("4 - Ver jogo \n");
			scanf("%d", &escolha);

			inserido = realizarAcao(player, carta, escolha);
		} while(!inserido);
		
				
		player1->turno = !player1->turno;
		player2->turno = !player2->turno;

	} while(player->pontuacao < 5);

	return player;
}

