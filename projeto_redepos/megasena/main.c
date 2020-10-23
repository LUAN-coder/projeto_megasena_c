#include <stdio.h>
#include <stdlib.h>

int main()
{

    int N;/* variável que irá conter o numero de jogos */
    int M;/* variável que irá conter o número de bolas */
    //int dados[50063860][15]; /* matriz para os resultados*/


    srand(time(NULL)); /*fáz com que os números não se repitam*/
    printf("\n");
    printf("     Projeto gerador de numeros aleatórios para megasena:\n");
    printf("\n");
    printf("\n");
    do{
        printf("1) digite o número 'N' de jogos da megasena que deseja fazer:");
        scanf("%i",& N);

    }while(N < 0 );

    printf("\n");
    printf("\n");

    do{
        printf("2) digite agora o número de bolas(entre 6 e 15) que os %i jogos devem ter:", N);
        scanf("%i",& M);
    }while(M<6 || M>15);

    //possibilidade_de_jogo(N,M);



    return 0;
}

void possibilidade_de_jogo(int jogos, int bolas){
    int bolas_max = 6;
    int combinatoria;
    combinatoria = fatorial(60)*fatorial(bolas-bolas_max)/(fatorial(54)*fatorial(bolas));
    printf("É possivel gerar no máximo %i resultados",combinatoria);
    if(jogos>combinatoria){
            printf("É possivel gerar no máximo %i resultados",combinatoria);
    }

}

//Função fatorial recursiva
int fatorial(int numero)
{
   if(numero > 1)
      return numero*fatorial(numero - 1);
   else
      return 1;
}
