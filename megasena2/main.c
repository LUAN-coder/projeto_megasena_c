#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


    char *bolas_sorteadas;
    int numero_de_bolas;

int main()
{
    float numero_max_jogos;
    int numero_de_jogos;

    int aux,i;


/******* Cria ou abre o arquivo se já existir onde ficará alocado os resultados ******/

        // criando a variável ponteiro para o arquivo
        FILE *jogos;

        //abrindo o arquivo
        jogos = fopen("resultados.txt", "w+");

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
        do{
        printf("1) Digite quantos jogos quer fazer:");
        scanf("%d",&numero_de_jogos);                   //inserção do número de jogos
        }while(numero_de_jogos<1);
        do{
        printf("2) Digite o número de bolas que os jogos devem ter:");
        scanf("%d",&numero_de_bolas);                   //inserção do número de bolas
        }while(numero_de_bolas<6||numero_de_bolas>15);
/*
        if(combinatoria(60,numero_de_bolas)<numero_de_jogos){
        printf("\n");
        printf("o numero de jogos que foi pedido não é possível de realizar, o número máximo para essa quantidade de bolas é %f",combinatoria(60,numero_de_bolas));
        numero_de_jogos = combinatoria(60,numero_de_bolas);
        }*/

        printf("\n");
        printf("      Espere um pouco......    ");
        printf("\n");
        printf("\n");



        bolas_sorteadas = calloc(3*numero_de_bolas,sizeof(char)); // cria um vetor dinâmico para guardar os números aleatórios no formato char
        //aux = calloc(3*numero_de_bolas,sizeof(char)); // cria um vetor dinâmico para guardar os números aleatórios no formato char

/***************************  Gera os números aleatórios   ********************************/


        srand(time(NULL)); //inicializar o gerador de números aleatórios
        aux = numero_de_jogos;
        do{

        gerador_aleatorio();

        //usando fwrite para armazenar a string no arquivo
        fwrite(bolas_sorteadas,sizeof(char),strlen(bolas_sorteadas),jogos);
        //fputs(bolas_sorteadas,jogos);
        //printf("%s", bolas_sorteadas);

        aux--;
        }while(aux!=0);

/**************************  Apresentação dos resultados    ********************************/
        printf("\n");
        printf("*************************************************\n");
        printf("*****       Os resultados possíveis      ********\n");
        printf("*************************************************\n");
        printf("\n");

        fclose(jogos);//usando fclose para fechar o arquivo

        jogos = fopen("resultados.txt", "r");//abrindo o arquivo modo leitura

  //while (!feof(jogos))
  for(i=0;i<numero_de_jogos;i++)
    {
       fread(bolas_sorteadas, sizeof(char), strlen(bolas_sorteadas), jogos); // lê as linhas do arquivo
       printf("%s",bolas_sorteadas); // mostra as linhas do arquivo na tela
    }


  fclose(jogos);            //usando fclose para fechar o arquivo
  free(bolas_sorteadas);    // libera o espaço que foi alocado dinamicamente

  printf("\n");
  printf("Dados gravados com sucesso!");

  printf("\n");

        printf("*************************************************\n");
        printf("************   Fim do código    *****************\n");
        printf("*************************************************\n");

    return 0;



}

void gerador_aleatorio(void){

    unsigned int  i;
    unsigned int  n;
    unsigned int aux=1,aux2=0;
    int *vetor;

    /*---------------------------- gera um vetor com números aleatórios não repetidos -----------------------------------------------*/

    vetor = calloc(numero_de_bolas,sizeof(int)); // cria um vetor dinâmico para guardar os números aleatórios no formato int
    vetor[0]=rand()%59+1;
    do{
            for(i=aux;i<numero_de_bolas;i++){

                        do{
                            vetor[i]=rand()%59+1;
                        }while(vetor[aux-1]==vetor[i]);

            }
        aux++;
    }while(aux!=numero_de_bolas-1);

    /*---------------------------- organiza os dados do vetor na forma crescente -----------------------------------------------*/
    aux=0;
    do{
            for(i=0;i<(numero_de_bolas-1);i++){
                    if(vetor[i]>vetor[i+1]){
                            aux2 = vetor[i+1];
                            vetor[i+1] = vetor[i];
                            vetor[i] = aux2;
                    }

            }
        aux++;
    }while(aux!=numero_de_bolas);



    /*---------------------------- coloca o vetor na forma char par ser arquivado -----------------------------------------------*/

    for(i = 0; i<(numero_de_bolas); i++){        // percorre o vetor auxiliar
        //n = rand()%59+1;                         // gera um número aleatório entre 1 e 60
        n = vetor[i];
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

      free(vetor);    // libera o espaço que foi alocado dinamicamente

}



/*O objetivo dessa função é fazer um calculo fatorial com o numero de entrada n.
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

/*O objetivo dessa função é fazer um calculo combinatório e obter o máximo de jogos possíveis que se pode fazer o numero de bolas="nb" dentre o numero total de bolas="nbt".
double combinatoria(int nbt,int nb){
    double vcomb;
    if(nbt>1 || nb>1){
            //Chamada recursiva
    vcomb = (fatorial(nbt)/(fatorial(nb)*fatorial(nbt-nb)))*combinatoria(nbt-1,nb-1);
    return (vcomb);
    }

}*/
