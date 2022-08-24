#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listas.h"
#define SUCESSO 0
#define MAX_RAND 2
#define MIN 3
#define MAX 10
#define AGORA 0
#define SIM 1

void imprimeGrafo(Lista **grafoBusca, int numVertices){//Função pra imprimir grafo, não precisa usar se não quiser

    Lista *copia;
    int comparador, comparador2;

    for (comparador = 0; comparador < numVertices; comparador++){

        printf("     %.02d ", comparador + 1);


        for (copia = grafoBusca[comparador]; copia != NULL; copia = copia->prox){

            printf(" %d ", copia->info + 1);

        }

        printf("\n");
    }

}

Lista **criaGrafo(Lista **grafoBusca, int numVertices){//Função já pra criar o grafo aleatório

    srand(time(AGORA));//Gera uma seed pro número aleatório baseada no tempo de agora

    int comparador, comparador2, valorBinario;

    grafoBusca = (Lista**)malloc(numVertices * sizeof(Lista*));

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

/* Só pra teste meu esse main
int main(int argc, char** argv){

    Lista **grafoBusca;
    int numVertices;

    scanf("%d", &numVertices);

    grafoBusca = criaGrafo(grafoBusca, numVertices);
    imprimeGrafo(grafoBusca, numVertices);    

    liberaGrafo(grafoBusca, numVertices);
    return SUCESSO;
}
*/
