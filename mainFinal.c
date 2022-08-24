/**
 * @file   main.c
 * @brief  
 * @author Bernardo de Oliveira Silva, Inaue Ferreira da Silva, Nicolle Taila de Oliveira, Vitoria Ellen Honorio
 * @date   08-23-2022
 */

/*  CABECALHOS  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listas.h"


/*  CODIGOS DE ERRO */
#define EXECUTADO_COM_EXITO     0

/*	CONSTANTES	*/
#define VERDADEIRO	(1 == 1)
#define FALSO		!VERDADEIRO
#define DIST_PADRAO	-1
#define MAX_RAND 	2
#define SIM 		1
#define ERRO 		-42

/*	ESTRUTURAS	*/
struct Info_dfs {
    int explorando;
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

void    grafo_ini_busca     (Info_dfs* resultado, int total_vertices, int v_destino)
{
    int v;

    for (v = 0; v < total_vertices; v++)
    {
        resultado[v].explorando         = FALSO;
        resultado[v].chega_no_destino       = FALSO;
    }
    
    resultado[v_destino].distancia      = 0;
    resultado[v_destino].chega_no_destino   = VERDADEIRO;
}

void    grafo_maior_caminho (Lista** grafo, int v_visitar, int limite_passos, Info_dfs* resultado)
{
    int maior_distancia = DIST_PADRAO;
    Lista* v_adj;

    if ((resultado[v_visitar].chega_no_destino) && (resultado[v_visitar].distancia == 0))
        return;

    resultado[v_visitar].explorando = VERDADEIRO;

    for (v_adj = grafo[v_visitar]; v_adj != NULL; v_adj = v_adj->prox)
    {
        if (!resultado[v_adj->info].explorando)
            grafo_maior_caminho(grafo, v_adj->info, limite_passos - 1, resultado);

        if (    !resultado[v_adj->info].explorando && //Se nao esta sendo explorado
            (resultado[v_adj->info].chega_no_destino) && //Se existe um caminho pro destino
            (resultado[v_adj->info].distancia > maior_distancia) && //Se a distancia for maior q a armazenada atualmente
            ((resultado[v_adj->info].distancia + 1) < limite_passos)    ) //Se estiver dentro do limite
        {
            resultado[v_visitar].chega_no_destino   = VERDADEIRO;
            maior_distancia             = resultado[v_adj->info].distancia;
            resultado[v_visitar].prox       = v_adj->info;
        }
    }

    resultado[v_visitar].explorando = FALSO;

    if (resultado[v_visitar].chega_no_destino)
        resultado[v_visitar].distancia  = maior_distancia + 1;
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

Lista **criaGrafo(Lista **grafoBusca, int numVertices){//Função já pra criar o grafo aleatório

    int comparador, comparador2, valorBinario;

    for (comparador = 0; comparador < numVertices; comparador++){

        grafoBusca[comparador] = lst_cria();

    }

    for (comparador = 0; comparador < numVertices; comparador++){

        for (comparador2 = 0; comparador2 < numVertices; comparador2++){
            
            valorBinario = rand() % MAX_RAND;

            if (valorBinario == SIM){

                grafoBusca[comparador]= lst_insere(grafoBusca[comparador], comparador2);

            }

        }

    }    

    return grafoBusca;
}

void liberaGrafo(Lista **grafoBusca, int numVertices){//Função pra liberar o grafo criado

    int comparador;

    for (comparador = 0; comparador < numVertices; comparador++){

        lst_libera(grafoBusca[comparador]);

    }

    free(grafoBusca);
}

int problemaResolve()
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
	limite++;
	srand(seed);
	grafo = (Lista**)malloc(vertices * sizeof(Lista*));
	resultado_busca_dfs = (Info_dfs*)malloc(vertices * sizeof(Info_dfs));

	criaGrafo(grafo, vertices);

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
        if(resultado_busca_dfs[v].prox == resultado_busca_dfs[v+1].prox){
            printf(" -- Não existe caminho disponivel -- ");
            v = destino;
        }else{
		v = resultado_busca_dfs[v].prox;
		printf("%i -> ", v);
        }
	} while (v != destino);

	printf("/\n");

	liberaGrafo(grafo, vertices);
	free(resultado_busca_dfs);

	return EXECUTADO_COM_EXITO;
}

/**
 * @brief FUNCAO PRINCIPAL
 *
 * @param argc NUMERO DE ARGUMENTOS
 * @param argv ARGUMENTOS
 * @return int CODIGO DE ERRO
 */

 int main(int argc, char** argv){

	int escolha, repetir, inicia;

    do {
        
        printf("Fuga da Terra\n");
        printf("\n");
        printf("\t1- Iniciar\n");
        printf("\t2- Informações\n");
        printf("\t3- Creditos\n");
        printf("\t4- Sair\n");
        printf("\n> ");

        scanf("%d", &escolha);

        switch(escolha){
        case 1:
            inicia = problemaResolve();
            break;
        case 2:
            printf("\nA Terra esta prestes a ser destruida por uma raça alienigena burocrata, os Vogons.\nPorem, devido a burocracia, eles devem demorar a destruir o planeta, dando tempo de voce pegar a nave mais proxima para fugir. \nComo voce eh uma pessoa legal, vai tentar salvar o maximo de pessoas que conseguir.\nSeu objetivo eh passar no maior numero de casas possivel para tentar levar o maximo de pessoas ate o local da fuga, antes que os Vogons cheguem.\n");
            break;
        case 3:
            printf("\nTrabalho de Algoritimos e Estruturas de Dados\n");
            printf("Tema 42: \"Ate Logo e Obrigado Pelos Peixes\"\n");
            printf("Feito por:\n\n");
            printf("- Bernardo de Oliveira Silva;\n- Inaue Ferreira da Silva;\n- Nicolle Taila de Oliveira;\n- Vitoria Ellen Honorio;\n\n");
            break;
        case 4:
            printf("\nSaindo...\n");
            return EXECUTADO_COM_EXITO;
            break;
        default:
            fputs("Houve um erro.\n", stderr);
            return ERRO;
            break;
        }

        printf("\nDeseja repetir o processo?\n1- Sim\n2- Nao\n> ");
        scanf("%d", &repetir);

    } while (repetir == SIM);

    printf("\nSaindo...\n");

	return EXECUTADO_COM_EXITO;
 }
