#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estruturas.h" //mudar nome do .h e das funções para as equivalentes do .h que for usar
#define SUCESSO 0
#define MAX_RAND 2
#define MIN 3
#define MAX 10
#define AGORA 0
#define SIM 1

void grafoAleatorio(lista **grafoBusca, int numVertices){

    srand(time(AGORA));//Gera uma seed pro número aleatório baseada no tempo de agora

    int comparador, comparador2, valorBinario;

    grafoBusca = (lista**)malloc(numVertices * sizeof(lista*));

    for (comparador = 0; comparador < numVertices; comparador++){

        grafoBusca[comparador] = criaLista();

    }

    for (comparador = 0; comparador < numVertices; comparador++){

        for (comparador2 = 0; comparador2 < numVertices; comparador2++){
            
            valorBinario = rand() % MAX_RAND;

            if (valorBinario == SIM){

                grafoBusca[comparador] = insereLista(grafoBusca[comparador], comparador2);

            }

        }

    }

}
