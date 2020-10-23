#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>

int main(void)
{

    int numero_de_jogos;/* variável que irá conter o numero de jogos */
    int numero_de_bolas;/* variável que irá conter o número de bolas */
    int **jogos_possiveis;

    printf("\n");
    printf("     Projeto gerador de números aleatórios para Mega-sena:\n");
    printf("\n");
    printf("\n");
    do{
        printf("1) digite o número 'N' de jogos da Mega-sena que deseja fazer:\n");
        scanf("%i",& numero_de_jogos);

    }while(numero_de_jogos < 0 );

    printf("\n");
    printf("\n");

    do{
        printf("2) digite agora o número de bolas(entre 6 e 15) que os %i jogos devem ter: \n", numero_de_jogos);
        scanf("%i",& numero_de_bolas);
    }while(numero_de_bolas<6 || numero_de_bolas>15);

    //N = possibilidade_de_jogo(N,M); /*faz com que os números não se repitam*/
    srand( time( NULL ) ); /* inicia o gerador de números aleatórios. */
    printf("\n");
    printf("\n");

    jogos_possiveis = AlocaMatriz(numero_de_jogos,numero_de_bolas);
    jogos_possiveis = GeradorAleatorio(jogos_possiveis,numero_de_jogos,numero_de_bolas);
    ImprimeMatriz(jogos_possiveis,numero_de_jogos,numero_de_bolas);
    LiberaMatriz(jogos_possiveis,numero_de_jogos);

}


int AlocaMatriz(int m, int n){
 int **M;
    int i;
    M = malloc(m*sizeof(int*));
    if(M == NULL){
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    for(i = 0; i < m; i++){

    M[i]=malloc(n*sizeof(int));
    if(M[i] == NULL){
        printf("Memoria insuficiente.\n");
        exit(1);
        }
    }
    return M;
}

void LiberaMatriz(int **M, int m){
  int i;
  for(i = 0; i < m; i++)
    free(M[i]);
  free(M);
  printf("Espaço de memória liberada.\n");
}

void ImprimeMatriz(int **M, int m, int n){
  int i,j;
  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){
      printf(" %2d ",M[i][j]);
    }
    printf("\n");
  }
}

int GeradorAleatorio(int **M,int m, int n){
  int i,j;

  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){

                    do{
                        M[i][j] = rand()%59+1;
                    }while(VerificadorDeIguais(M[i][j],M,m,n)==1);


    }
  }
  return M;
}

int VerificadorDeIguais(int num, int **M, int m, int n){
    int i,j;
    int aux;

      for(i = 0; i < m; i++){
            for(j = 0; j < n; j++){
            if(M[i][j] == num){
                aux=1;
            }else{
                aux=0;
            }

        }
      }
return aux;
}






