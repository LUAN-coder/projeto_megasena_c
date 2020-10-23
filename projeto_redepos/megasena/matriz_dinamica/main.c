#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,m;
    int i,j;
    int **matriz;
    printf("bem vindo ao gerador de tabela\n");
    printf("esse programa gera tabelas preenchidas com inteiros\n");
    printf("\n");
    printf("\n");
    printf("digite o numero de linhas da matriz\n");
    scanf("%i",n);
    printf("digite o numero de colunas da matriz\n");
    scanf("%i",m);

    //primeiro alocar memoria

    // aloca um vetor de LIN ponteiros para linhas
    matriz = malloc(n*sizeof(int*)) ;

    // aloca cada uma das linhas (vetores de COL inteiros)
    for (i=0; i < n; i++){
    matriz[i] = malloc(m*sizeof(int));
    }

    // percorre a matriz
    for (i=0; i < n; i++){
        for (j=0; j < m; j++){
            matriz[i][j] = j ;
            }  // acesso com sintaxe mais simples
    }

        // imprime a matriz
    for (i=0; i < n; i++){
        for (j=0; j < m; j++){
            printf(" %2d ",matriz[i][j]);
        }
        printf("\n");
    }



return 0;
}
