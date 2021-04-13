#include <stdio.h>

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