#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

FilaL *fila_cria_l(){
	FilaL *f = (FilaL *) malloc(sizeof(FilaL));
	f->ini = f->fim = NULL;
	return f;
}

void fila_insere_l(FilaL *f,int v){
	ListaF *n = (ListaF *) malloc(sizeof(ListaF));
	n->info=v;
	n->prox = NULL;
	if(f->fim != NULL) f->fim->prox = n;
	else f->ini = n;
	f->fim = n;
}

int fila_retira_l(FilaL *f){
	ListaF *t;
	int v;
	if(fila_vazia_l(f)){
		printf("Fila vazia!");
		exit(1);
	}
	t = f->ini;
	v = t->info;
	f->ini = t->prox;
	if(f->ini==NULL) f->fim = NULL;
	free(t);
	return v;
}

int fila_vazia_l(FilaL *f){
	return (f->ini == NULL);
}

void fila_libera_l(FilaL *f){
	ListaF *q = f->ini;
	while(q!=NULL){
		ListaF *t = q->prox;
		free(q);
		q = t;
	}
	free(f);
}

ListaF* fila_busca_l(FilaL *fila, int informacao){
	ListaF *q;
	for(q=fila->ini; q!=NULL; q=q->prox){
		if(q->info==informacao){
			return q;
		}
	}
	return NULL;
}
