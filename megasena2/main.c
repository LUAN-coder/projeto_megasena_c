#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

    float numero_max_jogos;
    int numero_de_jogos;
    int numero_de_bolas;
    char *bolas_sorteadas;

int main()
{


/******* Cria ou abre o arquivo se já existir onde ficará alocado os resultados ******/

        // criando a variável ponteiro para o arquivo
        FILE *jogos;

        //abrindo o arquivo
        jogos = fopen("resultados.txt", "a+");

        //testando se o arquivo foi realmente criado
        if(jogos == NULL)
            {
                printf("Erro na abertura do arquivo!");
            return 1;
            }


/******** Pede as informações de quantidade de jogos e número de bolas ao usuário ********/

        printf("*************************************************\n");
        printf("*************************************************\n");
        printf("*****   Gerador de jogos para Mega-sena  ********\n");
        printf("*************************************************\n");
        printf("*************************************************\n");
        printf("\n");
        printf("\n");
        printf("1) Digite quantos jogos quer fazer:");
        scanf("%d",&numero_de_jogos);                   //inserção do número de jogos
        printf("2) Digite o número de bolas que os jogos devem ter:");
        scanf("%d",&numero_de_bolas);                   //inserção do número de bolas
        printf("\n");
        printf("      Espere um pouco......    ");
        printf("\n");

        bolas_sorteadas = calloc(3*numero_de_bolas,sizeof(char)); // cria um vetor dinâmico para guardar os números aleatórios no formato char


/***************************  Gera os números aleatórios   ********************************/

        /* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
        com o valor da função time(NULL). Este por sua vez, é calculado
        como sendo o total de segundos passados desde 1 de janeiro de 1970
        até a data atual.
        Desta forma, a cada execução o valor da "semente" será diferente.
        */

        srand(time(NULL));
        do{

        gerador_aleatorio();

                                                    //usando fprintf para armazenar a string no arquivo
                                                    //fprintf (jogos, "%s", bolas_sorteadas);


        //usando fwrite para armazenar a string no arquivo
        //fwrite(bolas_sorteadas,sizeof(char),strlen(bolas_sorteadas),jogos);
        fputs(bolas_sorteadas,jogos);
        printf("%s", bolas_sorteadas);
        numero_de_jogos--;
        }while(numero_de_jogos!=0);

/**************************  Apresentação dos resultados    ********************************/
        printf("\n");
        printf("*************************************************\n");
        printf("*****       O resultados possíveis       ********\n");
        printf("*************************************************\n");
        printf("\n");


  while (!feof(jogos))
    {
       //fscanf(jogos,"%s",&bolas_sorteadas);
       fread(bolas_sorteadas,sizeof(char),strlen(bolas_sorteadas),jogos);
       printf("%s",bolas_sorteadas);
    }

  //usando fclose para fechar o arquivo
  fclose(jogos);
  free(bolas_sorteadas);// libera o espaço que foi alocado dinamicamente

  printf("\n");
  printf("Dados gravados com sucesso!");

  printf("\n");

        printf("*************************************************\n");
        printf("************   Fim do código    *****************\n");
        printf("*************************************************\n");

    return 0;



}




/*O objetivo dessa função é fazer um calculo fatorial com o numero de entrada n.*/
float fatorial(int n){
    double vfat;

  if ( n <= 1 ){
    //Caso base: fatorial de n <= 1 retorna 1
    return (1);}
  else
  {
    //Chamada recursiva
    vfat = n * fatorial(n - 1);
    return (vfat);
  }
}

/*O objetivo dessa função é fazer um calculo combinatório e obter o máximo de jogos possíveis que se pode fazer o numero de bolas="nd" dentre o numero total de bolas="nbt".*/
float combinatoria(int nbt,int nb){
    double vcomb;
    if(nbt>1 || nb>1){
            //Chamada recursiva
    vcomb = (fatorial(nbt)/(fatorial(nb)*fatorial(nbt-nb)))*combinatoria(nbt-1,nb-1);
    return (vcomb);
    }

}

void gerador_aleatorio(void){

    unsigned int  i;
    unsigned int  n;

    for(i = 0; i<(numero_de_bolas); i++){      // percorre o vetor auxiliar
        n = rand()%59+1;                         // gera um número aleatório entre 1 e 60
        if(n/10==0){                             // verifica se n é um numero menor que 10 se for passa pela condição
        bolas_sorteadas[i*3] =48;                // recebe o "0"
        bolas_sorteadas[i*3+1] = n+48;           // recebe um numero que pode ser 1 até 9
        }
        else{                                    // caso contrário significa que o numero gerado aleatoriamente foi maior que 10
        bolas_sorteadas[i*3] = n/10+48;          // recebe o primeiro algarismo
        bolas_sorteadas[i*3+1] = n%10+48;         // recebe o segundo algarismo
        }
        bolas_sorteadas[i*3+2] = 32;             // coloca um caractere espaço
    }
    bolas_sorteadas[3*numero_de_bolas-1] = '\n';  // substitui o ultimo espaço de caractere pelo caractere \n que representa uma quebra de linha
}




