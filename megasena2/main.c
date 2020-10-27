/*********************************************************************************/
/**  Desenvolvedor: Luan Vinicius Arruda da Silva                                */
/**                                                                              */
/**  Objetivo do código: Criar N jogos da Mega-sena com M bolas, onde os números */
/**  dentro de cada jogo não pode se repetir, e os jogos criados também não      */
/**  podem se repetir. O resultado dos jogos sera mostrado na tela, mas terá um  */
/**  arquivo que vai armazenar os últimos jogos feitos.                          */
/**                                                                              */
/**  Desenvolvido entre os dias 23 a 27 de outubro de 2020                       */
/*********************************************************************************/

/*------------------------Bibliotecas-------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/*-------------variáveis globais-----------------------------*/
    char *bolas_sorteadas;
    int numero_de_bolas;
    int numero_de_jogos;
/*--------------------------------------------------*/

/*------------------------Funções-----------------------------------------------*/

float  fatorial(int n)  //O objetivo dessa função é fazer um calculo fatorial com o numero de entrada n.
    {
        if (n>0){
            return n*fatorial(n-1);}
        else{
            return 1;}
    }

float  permutacao(int n)            //O objetivo dessa função é fazer uma permutação que nada mais é que um fatorial de n.
    {
        return fatorial(n);
    }

float  arranjo(int n, int p)        //O objetivo dessa função é fazer um calculo de arranjo com o numero de entrada n.
    {
        if (p>1){
            return n*arranjo(n-1,p-1);}
        else{
            return n;}
    }

float  combinacao(int n, int p)     //O objetivo dessa função é fazer um calculo fatorial com o numero de entrada n.
    {
        return arranjo(n,p)/fatorial(p);
    }


void gerador_aleatorio(void){       //O objetivo dessa é gerar números aleatórios, e guarda-los ordenados e sem repetição
                                    //dentro de um vetor chamado bolas_sorteadas.

    unsigned int  i;
    unsigned int  n;
    unsigned int aux=0,aux2=0;
    int *vetor;

    /*---------------------------- gera um vetor com números aleatórios não repetidos -----------------------------------------------*/

    vetor = calloc(numero_de_bolas,sizeof(int));    // cria um vetor dinâmico de inteiros para guardar os números aleatórios gerados

            for(i=0;i<numero_de_bolas;i++){

                            vetor[i]=rand()%60+1;
            }

    /*---------------------------- organiza os dados do vetor na forma crescente     -----------------------------------------------*/
    do{
            for(i=0;i<(numero_de_bolas-1);i++){
                    if(vetor[i]>vetor[i+1]){
                            aux2 = vetor[i+1];
                            vetor[i+1] = vetor[i];
                            vetor[i] = aux2;
                    }else if(vetor[i]==vetor[i+1])
                    {
                        while(vetor[i]==vetor[i+1])
                            {
                            vetor[i+1]=rand()%60+1;
                            }
                    }
            }
        aux++;
    }while(aux!=numero_de_bolas);

    /*---------------------------- coloca o vetor na forma de caracteres para ser arquivado -----------------------------------------------*/

    for(i = 0; i<(numero_de_bolas); i++){        // percorre o vetor auxiliar
        n = vetor[i];                            // passa o valor inteiro vetor auxiliar para n
        if(n/10==0){                             // verifica se n é um numero menor que 10 se for passa pela condição
            bolas_sorteadas[i*3] =48;            // recebe o "0"
            bolas_sorteadas[i*3+1] = n+48;       // recebe um numero que pode ser 1 até 9
        }
        else{                                    // caso contrário significa que o numero gerado aleatoriamente foi maior que 10
            bolas_sorteadas[i*3] = n/10+48;      // recebe o primeiro algarismo
            bolas_sorteadas[i*3+1] = n%10+48;    // recebe o segundo algarismo
        }
        bolas_sorteadas[i*3+2] = 32;             // coloca um caractere espaço
    }
    bolas_sorteadas[3*numero_de_bolas-1] = '\n'; // substitui o ultimo espaço de caractere pelo caractere \n que representa uma quebra de linha
    free(vetor);                                 // libera o espaço que foi alocado dinamicamente

}

void verificar_repeticoes(FILE *arquivo){           //O objetivo dessa é verificar se tem repetição de jogos no arquivo resultados.txt

    int i;
    char *vetor;
    char *vetor2;

    /*---------------------------- gera dois vetores auxiliares para organizar e modificar o arquivo -----------------------------------------------*/

    vetor = calloc(numero_de_bolas,sizeof(char));   // cria um vetor dinâmico para guardar os jogos
    vetor2 = calloc(numero_de_bolas,sizeof(char)); // cria um vetor dinâmico para guardar os jogos


    for(i=0;i<(numero_de_jogos-1);i++){                            // aqui é iniciado um processo de repetição que vai pegar cada linha do arquivo para comparar com as outras linhas
            fread(vetor, sizeof(char), strlen(vetor), arquivo);    // pega os dados de uma linha do arquivo
                for(i=0;i<(numero_de_jogos-2);i++){
                    fread(vetor2, sizeof(char), strlen(vetor2), arquivo);    //pega os dados de outra linha do arquivo para comparação
                    while(vetor==vetor2){                                    //se forem iguais é criado um loop que gera uma novo jogo e enquanto
                        gerador_aleatorio();
                        fwrite(bolas_sorteadas,sizeof(char),strlen(bolas_sorteadas),arquivo);
                        fread(vetor2, sizeof(char), strlen(vetor2), arquivo);    //pega os dados da linha para nova comparação
                    }
                }
    }
        free(vetor);    // libera o espaço que foi alocado dinamicamente
        free(vetor2);   // libera o espaço que foi alocado dinamicamente

}



/********************   Início do código principal   *********************************/
int main()
{
    /*---------------------variáveis-------------------------------------------------*/
    int resposta;
    float numero_max_jogos;
    int aux,i,j;


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
            resposta=0;
            do{
                printf("1) Digite quantos jogos quer fazer:");
                scanf("%d",&numero_de_jogos);                       //inserção do número de jogos
            }while(numero_de_jogos<1);                              //se o número de jogos for menor que 1 repete o pedido

            do{
                printf("2) Digite o número de bolas que os jogos devem ter:");
                scanf("%d",&numero_de_bolas);                       //inserção do número de bolas
            }while(numero_de_bolas<6||numero_de_bolas>15);          //se o número de bolas não estiver entre 6 e 15 repete o pedido

            numero_max_jogos = combinacao(60,numero_de_bolas);      //verifica por análise combinatória a quantidade máxima de jogos que pode existir com essa quantidade de bolas

            if(numero_max_jogos<numero_de_jogos){                   //se a quantidade de jogos não for possível de realizar apresenta a quantidade máxima possível e
                printf("\n");                                       //pergunta se quer recolocar os dados para continuar, ou se deseja sair
                printf("o numero de jogos que foi pedido não é possível de realizar, o número máximo para essa quantidade de bolas é %f",numero_max_jogos);
                printf("\n");
                printf("se deseja colocar novamente os dados digite 1 e pressione enter ou qualquer tecla pra sair");
                scanf("%d",&resposta);                              //coleta a decisão
                if(resposta!=1){                                    //se decisão for diferente de repetir a colocação de dados novos
                    exit(1);                                        //o programa é finalizado
                }
            }
        }while(resposta==1);                                        //enquanto a resposta for de recolocar os dados repita


        printf("\n");
        printf("      Espere um pouco......    ");
        printf("\n");
        printf("\n");

/***************************  Gera os números aleatórios   ********************************/

        bolas_sorteadas = calloc(3*numero_de_bolas,sizeof(char));   // cria um vetor dinâmico para guardar os números aleatórios no formato char

        srand(time(NULL));                                          //inicializar o gerador de números aleatórios

        aux = numero_de_jogos;                                      //passa o valor do numero de jogos para variável aux
        do{

            gerador_aleatorio();                                                //gera os números aleatórios e guar no vetor bolas_sorteadas

            fwrite(bolas_sorteadas,sizeof(char),strlen(bolas_sorteadas),jogos); //usando fwrite para armazenar a string no arquivo

        aux--;                                                                  //decrementa o aux
        }while(aux!=0);

        fclose(jogos);                                                           //usando fclose para fechar o arquivo

/*************************** Verificar se tem jogos repetidos, modificar se tiver ********************************/

        verificar_repeticoes(jogos);

/*****************************        Apresentação dos resultados    ********************************/

        printf("\n");
        printf("*************************************************\n");
        printf("*****       Os resultados possíveis      ********\n");
        printf("*************************************************\n");
        printf("\n");

        jogos = fopen("resultados.txt", "r");      //abrindo o arquivo modo leitura mas permite escrita

  for(i=0;i<numero_de_jogos;i++)
    {
       fread(bolas_sorteadas, sizeof(char), strlen(bolas_sorteadas), jogos);    // lê as linhas do arquivo
       printf("%s",bolas_sorteadas);                                            // mostra as linhas do arquivo na tela
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
/********************   Fim do código principal   *********************************/



