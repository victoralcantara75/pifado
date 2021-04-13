#include <stdio.h>
#include <stdlib.h>
#include "structs.c"

typedef struct sCell{
    carta info;
    struct sCell *prox;
}celula;

typedef struct sPilha{
    celula *ptrtopo;
    int tamanho;
}pilha;

void* criarCelula(){
    return (celula*)malloc(sizeof(celula));
}

void inicializar(pilha *p){
    p->ptrtopo = NULL;
    p->tamanho = 0;
}

int pilha_vazia(pilha *p){
    if(p->ptrtopo == NULL)
        return 1;
    return 0;
}

int push(pilha *p, carta elem){
    
    celula *no = criarCelula();
    no->info = elem;

    no->prox = p->ptrtopo;
    p->ptrtopo = no;
    p->tamanho++;

    return 1;
}

int pop(pilha *p){
    if(pilha_vazia(p))
    {
        printf("n�o h� elementos para desempilhar\n");
        return 0;
    }
    
    celula *aux = p->ptrtopo;
    p->ptrtopo = p->ptrtopo->prox;
    free(aux);
    return 1;
}

void imprimir_pilha(pilha *p){
    while(!pilha_vazia(p)){
        printf("%c%c ", p->ptrtopo->info.display, p->ptrtopo->info.naipe);
        pop(p);
    }
    printf("\n");
}