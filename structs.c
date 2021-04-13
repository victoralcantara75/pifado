#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_CARTAS 52
#define TAM_ESPACO 4

typedef struct sCard{
	char display;
	int naipe;
	int valor;
}carta;


// ================================== FILA (Baralho) ====================================
typedef struct sFila{
	carta vet[TAM_CARTAS];
	int inicio, fim;
}fila;
 
void inicializar_fila(fila *fila){
	fila->inicio = 0;
	fila->fim = 0;
}
 
int fila_vazia(fila *fila){
	if(fila->inicio == fila->fim)
		return 1;
	return 0;
}

int fila_cheia(fila *fila){
	if((fila->fim+1) % TAM_CARTAS ==  fila->inicio)
		return 1;
	return 0;
}
 
int enfileirar(fila *fila, carta n){
	
	if(fila_cheia(fila))
		return 0;
	
	fila->fim = (fila->fim+1) % TAM_CARTAS;
	fila->vet[fila->fim] = n;
	return 1;
}
 
 carta desenfileirar(fila *fila){
	
	 if (fila_vazia(fila)){
		 printf("fila vazia");
		 exit(1);
	 }
	 int prox = (fila->inicio+1) % TAM_CARTAS;
     carta aux = fila->vet[prox];
	 fila->inicio = prox;
	 return aux;
 }
 
 int imprimir_fila(fila *fila){

	 if(fila_vazia(fila))
	 	return 0;
	 
	 while(!fila_vazia(fila)){
		 printf("%c%c ", fila->vet[(fila->inicio+1) % TAM_CARTAS].display,
		 	 	 	 	 fila->vet[(fila->inicio+1) % TAM_CARTAS].naipe);
		 desenfileirar(fila);
	 }
	 return 1;
 }
 
 void imprimirFilaNaoClassica(fila *fila){
	 int i= (fila->inicio+1) % TAM_CARTAS;
	 while (i!= (fila->fim+1) % TAM_CARTAS){
		 printf("%c%c ", fila->vet[i].display, fila->vet[i].naipe);
		 i = (i+1)%TAM_CARTAS;
	 }
 }

 // ================================== DEQUE (Espacos) ====================================
 typedef struct sDeque{
    carta info[TAM_ESPACO];
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
    if ((deque->fim+1)%TAM_ESPACO == deque->inicio)
        return 1;
    return 0;
}

int inserirInicio(deque *deque, carta elemento){
    if (deque_cheio(deque))
        return 0;
    
    if(deque->inicio == 0)
        deque->inicio = TAM_ESPACO-1;
    else
        deque->inicio--;

    deque->info[deque->inicio] = elemento;
    
    return 1;
}

int removerInicio(deque *deque){
    if(deque_vazio(deque))
        return 0;

    deque->inicio = (deque->inicio+1)%TAM_ESPACO;
    
    return 1;
}

int inserirFinal(deque *deque, carta elemento){
    if (deque_cheio(deque)){
        printf("Espaço cheio!");
        return 0;
    }
       
    deque->info[deque->fim] = elemento;
    deque->fim = (deque->fim+1)%TAM_ESPACO;
    return 1;
}

int removerFinal(deque *deque){
    if(deque_vazio(deque))
        return 0;

    if(deque->fim == 0)
        deque->fim = TAM_ESPACO-1;
    else
        deque->fim--;
	
	return 1;   
}

void imprimirDeque(deque *deque){

	if(deque_vazio(deque)){
        printf("Jogo vazio...");
        return;
    }

    int aux = deque->inicio;

    while (aux != deque->fim)
    {
        printf("%c%c ", deque->info[aux].display, deque->info[aux].naipe);
        aux = (aux+1)%TAM_ESPACO;
    }
}
// ================================== PILHA (Cartas de Interesse) ====================================
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

void inicializar_pilha(pilha *p){
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

carta pop(pilha *p){
    if(pilha_vazia(p))
    {
        printf("nao ha elementos para desempilhar\n");
        exit(1);
    }
    
    celula *aux = p->ptrtopo;
    carta rem;

    p->ptrtopo = p->ptrtopo->prox;
    rem = aux->info;
    free(aux);
    return rem;
}

void imprimir_pilha(pilha *p){
    while(!pilha_vazia(p)){
        printf("%c%c ", p->ptrtopo->info.display, p->ptrtopo->info.naipe);
        pop(p);
    }
    printf("\n");
}

void imprimir_pilha_nao_classica(pilha *p){

    celula *aux = p->ptrtopo;
    while(aux != NULL){
        printf("%c%c ", aux->info.display, aux->info.naipe);
        aux = aux->prox;
    }
    printf("\n");
}
// =================== LISTA (Utilizado para verificar cartas no embaralhamento) ====================================
typedef struct sList{
	int info[52];
	int ultimo;
}lista;

void inicializar_lista(lista *lista){
	int i;
	for(i =0; i<52; i++){
		lista->info[i] = -1;
	}
	lista->ultimo = -1;
}

int lista_vazia(lista *lista){
	if (lista->ultimo == -1)
		return 1;
	return 0;
}

void adicionar(lista *lista, int elemento){
	lista->info[lista->ultimo] = elemento;
	lista->ultimo++;
}

int existeElemento(lista *lista, int elemento){
	int i;
	for(i =0; i<52; i++){
		if(lista->info[i] == elemento)
			return 1;
	}
	return 0;
}

// ==================================================================
typedef struct sJog{
	int numero;
	char nome[20];
	int turno;
    int pontuacao;
    fila baralho;
	deque jogo[TAM_ESPACO];
	pilha cartasInteresse;
}jogador;