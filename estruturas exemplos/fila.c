#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.c"
#include "structs.c"
#define MAXTAM 52

typedef struct sFila{
	carta vet[MAXTAM];
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
	if((fila->fim+1) % MAXTAM ==  fila->inicio)
		return 1;
	return 0;
}
 
int enfileirar(fila *fila, carta n){
	
	if(fila_cheia(fila))
		return 0;
	
	fila->fim = (fila->fim+1) % MAXTAM;
	fila->vet[fila->fim] = n;
	return 1;
}
 
 int desenfileirar(fila *fila){
	
	 if (fila_vazia(fila)){
		 printf("fila vazia");
		 	return 0;
	 }
	 
	 fila->inicio = (fila->inicio+1) % MAXTAM;
	 return 1;
 }
 
 int imprimir_fila(fila *fila){

	 if(fila_vazia(fila))
	 	return 0;
	 
	 while(!fila_vazia(fila)){
		 printf("%c%c ", fila->vet[(fila->inicio+1) % MAXTAM].display,
		 	 	 	 	 fila->vet[(fila->inicio+1) % MAXTAM].naipe);
		 desenfileirar(fila);
	 }
	 return 1;
 }
 
 void imprimirFilaNaoClassica(fila *fila){
	 int i= (fila->inicio+1) % MAXTAM;
	 while (i!= (fila->fim+1)%MAXTAM){
		 printf("%c%c ", fila->vet[i].display, fila->vet[i].naipe);
		 i = (i+1)%MAXTAM;
	 }
 }
 

