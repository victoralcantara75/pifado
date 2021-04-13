#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.c"
#define TAM 52

typedef struct sDeque{
    carta info[TAM];
    int inicio, fim;
}deque;

int inicializar_deque(deque *deque){
    deque->inicio = 0;
    deque->fim = 0;
    return 1;
}

int deque_vazio(deque *deque){
    if (deque->inicio == deque->fim)
        return 1;
    return 0;
}

int deque_cheio(deque *deque){
    if ((deque->fim+1)%TAM == deque->inicio)
        return 1;
    return 0;
}

int inserirInicio(deque *deque, carta elemento){
    if (deque_cheio(deque))
        return 0;
    
    if(deque->inicio == 0)
        deque->inicio = TAM-1;
    else
        deque->inicio--;

    deque->info[deque->inicio] = elemento;
    
    return 1;
}

int removerInicio(deque *deque){
    if(deque_vazio(deque))
        return 0;

    deque->inicio = (deque->inicio+1)%TAM;
    
    return 1;
}

int inserirFinal(deque *deque, carta elemento){
    if (deque_cheio(deque))
        return 0;
    
    deque->info[deque->fim] = elemento;
    deque->fim = (deque->fim+1)%TAM;
    return 1;
}

int removerFinal(deque *deque){
    if(deque_vazio(deque))
        return 0;

    if(deque->fim == 0)
        deque->fim = TAM-1;
    else
        deque->fim--;
	
	return 1;   
}

void imprimirDeque(deque *deque){
	printf("Imprimindo...\n");
	if(deque_vazio(deque))
        return;
    
    int aux = deque->inicio;

    while (aux != deque->fim)
    {
        printf("%c%c ", deque->info[aux].valor, deque->info[aux].naipe);
        aux = (aux+1)%TAM;
    }
    printf("\n");
}

