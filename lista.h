#include <stdio.h>
#include <stdlib.h>

/*definindo lista encadeada*/
struct lista{
	int info;
	struct lista *prox;
};

typedef struct lista Lista;

/*Funcoes de lista encadeada*/

Lista* lst_cria();

Lista* lst_insere(Lista *l, int i);

void lst_imprime(Lista *l);

int lst_vazia(Lista *l);

Lista* lst_busca(Lista *l, int v);

Lista *lst_retira(Lista *l, int v);

void lst_libera(Lista *l);

Lista *lst_insere_ordenado(Lista *l, int v);

int lst_igual(Lista *l1, Lista *l2);

