/**
 * @file   main.c
 * @brief  
 * @author Inaue Ferreira da Silva, 
 * @date   07-10-2022
 */

/*  CABECALHOS  */
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/*  CODIGOS DE ERRO */
#define EXECUTADO_COM_EXITO     0

/*	CONSTANTES	*/
#define VERDADEIRO	(1 == 1)
#define FALSO		!VERDADEIRO
#define COMECO_BUSCA	0
#define FIM_BUSCA	1
#define NAO_PREENCHIDO	-1
#define DIST_PADRAO	-1

/*	ESTRUTURAS	*/
struct Info_dfs {
	int visitado;
	int chega_no_destino;
	int distancia;
	int prox;
};
typedef struct Info_dfs Info_dfs;

/* 	FUNCOES     */
/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

int	main			(int argc, char** argv);
void	grafo_maior_caminho	(Lista** grafo, int v_visitar, int limite_passos, Info_dfs* resultado);
void	grafo_ini_busca		(Info_dfs* resultado, int total_vertices, int v_destino);
void	lst_print		(Lista* lst_imprimir);

/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

void	grafo_ini_busca		(Info_dfs* resultado, int total_vertices, int v_destino)
{
	int v;

	for (v = 0; v < total_vertices; v++)
	{
		resultado[v].visitado			= FALSO;
		resultado[v].chega_no_destino		= FALSO;
	}
	
	resultado[v_destino].distancia		= 0;
	resultado[v_destino].chega_no_destino	= VERDADEIRO;
}

void	grafo_maior_caminho	(Lista** grafo, int v_visitar, int limite_passos, Info_dfs* resultado)
{
	int maior_distancia = DIST_PADRAO;
	Lista* v_adj;

	if (	resultado[v_visitar].chega_no_destino &&
		(resultado[v_visitar].distancia == 0)	)
		return;

	resultado[v_visitar].visitado = VERDADEIRO;

	for (v_adj = grafo[v_visitar]; v_adj != NULL; v_adj = v_adj->prox)
	{
		if (!resultado[v_adj->info].visitado)
			grafo_maior_caminho(grafo, v_adj->info, limite_passos - 1, resultado);

		if (	(resultado[v_adj->info].chega_no_destino) &&
			(resultado[v_adj->info].distancia > maior_distancia) &&
			((resultado[v_adj->info].distancia + 1) < limite_passos)	)
		{
			resultado[v_visitar].chega_no_destino	= VERDADEIRO;
			maior_distancia				= resultado[v_adj->info].distancia;
			resultado[v_visitar].prox		= v_adj->info;
		}
	}

	if (resultado[v_visitar].chega_no_destino)
		resultado[v_visitar].distancia	= maior_distancia + 1;
	else
		resultado[v_visitar].visitado	= FALSO;
}

void	lst_print	(Lista* lst_imprimir)
{
	Lista* item = lst_imprimir;

	while(item != NULL)
	{
		printf("%i -> ", item->info);
		item = item->prox;
	}

	printf("/\n");

}

/**
 * @brief FUNCAO PRINCIPAL
 *
 * @param argc NUMERO DE ARGUMENTOS
 * @param argv ARGUMENTOS
 * @return int CODIGO DE ERRO
 */
int main(int argc, char** argv)
{
	Lista** grafo;
	Info_dfs* resultado_busca_dfs;
	int vertices, v, v1, v2, origem, destino, limite, i, seed;

	printf("GRAFO ORIENTADO\n");
	printf("____________________________________________________________\n");
	printf("Digite quantos vertices deseja no grafo:\n");
	scanf("%i", &vertices);
	printf("Digite um numero inteiro qualquer:\n");
	scanf("%i", &seed);
	printf("Digite a origem da busca:\n");
	scanf("%i", &origem);
	printf("Digite o destino da busca:\n");
	scanf("%i", &destino);
	printf("Digite o limite de passos:\n");
	scanf("%i", &limite);
	srand(seed);
	grafo = (Lista**)malloc(vertices * sizeof(Lista*));
	resultado_busca_dfs = (Info_dfs*)malloc(vertices * sizeof(Info_dfs));

	for (v = 0; v < vertices; v++)
		grafo[v] = lst_cria();
	
	for (v1 = 0; v1 < vertices; v1++)
	{
		for (v2 = 0; v2 < vertices; v2++)
		{
			if ((rand() % 2) == 1)
				grafo[v1] = lst_insere(grafo[v1], v2);
		}
	}

	printf("____________________________________________________________\n");
	printf("GRAFO RESULTANTE:\n");

	for (v = 0; v < vertices; v++)
	{
		printf("vertices 'destino' a partir do vertice %i: ", v);
		lst_print(grafo[v]);
	}

	grafo_ini_busca(resultado_busca_dfs, vertices, destino);
	grafo_maior_caminho(grafo, origem, limite, resultado_busca_dfs);
	printf("____________________________________________________________\n");
	printf("CAMINHO MAIS LONGO DE %i A %i:\n", origem, destino);
	v = origem;
	printf("%i -> ", v);
	
	do {
		v = resultado_busca_dfs[v].prox;
		printf("%i -> ", v);
	} while (v != destino);

	printf("/\n");

	free(grafo);
	free(resultado_busca_dfs);

	return EXECUTADO_COM_EXITO;
}
