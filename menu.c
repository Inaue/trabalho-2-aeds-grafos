#include <stdio.h>
#include <stdlib.h>
#define SUCESSO 0
#define ERRO -42
#define SIM 1

int main(int argc, char** argv){

    int escolha, repetir;

    do {
        
        printf("Fuga da Terra\n");
        printf("\n");
        printf("\t1- Iniciar\n");
        printf("\t2- Informações\n");
        printf("\t3- Créditos\n");
        printf("\t4- Sair\n");
        printf("\n> ");

        scanf("%d", &escolha);

        switch(escolha){
        case 1:
            printf("1");//É aqui que será colocada a função feita por vcs
            break;
        case 2:
            printf("\nA Terra está prestes a ser destruída por uma raça alienígena burocrata, os Vogons.\nPorém, devido à burocracia, eles devem demorar a destruir o planeta, dando tempo de você pegar a nave mais próxima para fugir. \nComo você é uma pessoa legal, vai tentar salvar o máximo de pessoas que conseguir.\nSeu objetivo é passar no maior número de casas possível para tentar levar o máximo de pessoas até o local da fuga, antes que os Vogons cheguem.\n");
            break;
        case 3:
            printf("\nTrabalho de Algoritimos e Estruturas de Dados\n");
            printf("Tema 42: \"Até Logo e Obrigado Pelos Peixes\"\n");
            printf("Feito por:\n\n");
            printf("- Bernardo de Oliveira Silva;\n- Inauê Ferreira Silva;\n- Nicolle Taila de Oliveira;\n- Vitória Ellen Honório;\n\n");
            break;
        case 4:
            printf("\nSaindo...\n");
            return SUCESSO;
            break;
        default:
            fputs("Houve um erro.\n", stderr);
            return ERRO;
            break;
        }

        printf("\nDeseja repetir o processo?\n1- Sim\n2- Não\n> ");
        scanf("%d", &repetir);

    } while (repetir == SIM);

    printf("\nSaindo...\n");

    return SUCESSO;
}

