/**
 * @file   main.c
 * @brief  
 * @author Inaue Ferreira da Silva, 
 * @date   07-10-2022
 */

/*  CABECALHOS  */
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
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
	int visitado; //Avisa se o vertice foi visitado ou nao
	int chega_no_fim; //Vertice tem caminho ou nao ate o destino
	int distancia; //A maior distancia possivel ate o vert destino
	int prox; //Proximo vertice a ser visitado para chegar no destino com a maior distância
};
typedef struct Info_dfs Info_dfs;

/* 	FUNCOES     */
/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

int	main			(int argc, char** argv);
void	grafo_maior_caminho	(Lista** grafo, int v_inicial, int v_final, Info_dfs* resultado);
void	lst_print		(Lista* lst_imprimir);

/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

void	grafo_maior_caminho	(Lista** grafo, int v_inicial, int v_final, Info_dfs* resultado)
{
	int maior_distancia = DIST_PADRAO; //Maior distancia encontrada, inicializada com valor padrao (-1)
	Lista* v_adj; //Lista de adjacência auxiliar

	resultado[v_inicial].visitado = VERDADEIRO; //Vertice atual foi visitado

	if (v_inicial == v_final) //Se o vértice final for igual ao inicial...
	{
		resultado[v_inicial].chega_no_fim	= VERDADEIRO; //Chegamos! Finalizamos o caminho
		resultado[v_inicial].distancia		= 0;          //A distância é 0
		return;                                         //Retorna a recursão
	}
	
	for (v_adj = grafo[v_inicial]; v_adj != NULL; v_adj = v_adj->prox) //Percorremos a lista de adjacência do vert analisado
	{
		if (!resultado[v_adj->info].visitado)                           //Se o vértice não foi visitado...
			grafo_maior_caminho(grafo, v_adj->info, v_final, resultado);  //...chamamos a função novamente

		if ((resultado[v_adj->info].chega_no_fim) && (resultado[v_adj->info].distancia > maior_distancia))
      // Se existe um caminho até v_final e a distância até ele for maior que a registrada atualmente...
      {
			resultado[v_inicial].chega_no_fim = VERDADEIRO;     //Existe um caminho até o fim
			maior_distancia = resultado[v_adj->info].distancia; //Nova maior distância
			resultado[v_inicial].prox = v_adj->info;            //O vertice analisado faz parte do caminho mais longo
		}
	}

	resultado[v_inicial].distancia = maior_distancia + 1; //
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
	int vertices, v, v1, v2, origem, destino, i, seed;

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
	srand(seed);
	grafo = (Lista**)malloc(vertices * sizeof(Lista*));
	resultado_busca_dfs = (Info_dfs*)malloc(vertices * sizeof(Info_dfs));

	for (v = 0; v < vertices; v++)
	{
		grafo[v] = lst_cria();
		resultado_busca_dfs[v].visitado			= FALSO;
		resultado_busca_dfs[v].chega_no_fim		= FALSO;
		resultado_busca_dfs[v].distancia		= DIST_PADRAO;
		resultado_busca_dfs[v].prox			= NAO_PREENCHIDO;
	}
	
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

	grafo_maior_caminho(grafo, origem, destino, resultado_busca_dfs);
	printf("____________________________________________________________\n");
	printf("CAMINHO MAIS LONGO DE %i A %i:\n", origem, destino);
	
	for (v = origem; v != NAO_PREENCHIDO; v = resultado_busca_dfs[v].prox)
		printf("%i -> ", v);

	printf("/\n");

	free(grafo);
	free(resultado_busca_dfs);

	return EXECUTADO_COM_EXITO;
}
