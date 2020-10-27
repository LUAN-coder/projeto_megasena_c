
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
/*------------------------ Libraries -------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/*-------------variáveis globais-----------------------------*/
/*------------- global variables-----------------------------*/

    char *bolas_sorteadas;
    int numero_de_bolas;
    int numero_de_jogos;

/*------------------------Funções-----------------------------------------------*/
/*------------------------Functions ------------------- ------------------------*/

float  fatorial(int n)  //O objetivo dessa função é fazer um calculo fatorial com o numero de entrada n.
    {                   //The purpose of this function is to do a factorial calculation with the input number n.
        if (n>0){
            return n*fatorial(n-1);}
        else{
            return 1;}
    }

float  permutacao(int n)            //O objetivo dessa função é fazer uma permutação que nada mais é que um fatorial de n.
    {                               //The purpose of this function is to make a permutation that is nothing more than a factorial of n.
        return fatorial(n);
    }

float  arranjo(int n, int p)        //O objetivo dessa função é fazer um calculo de arranjo com o numero de entrada n.
    {                               // The purpose of this function is to make an arrangement calculation with the input number n.
        if (p>1){
            return n*arranjo(n-1,p-1);}
        else{
            return n;}
    }

float  combinacao(int n, int p)     //O objetivo dessa função é fazer uma combinatória com os dois números de entrada n e p.
    {                               //The purpose of this function is to make a combination with the two input numbers n and p.
        return arranjo(n,p)/fatorial(p);
    }


void gerador_aleatorio(void){       //O objetivo dessa é gerar números aleatórios, e guarda-los ordenados e sem repetição
                                    //dentro de um vetor chamado bolas_sorteadas.
                                    //The purpose of this is to generate random numbers, and keep them in order and without repetition
                                    //inside a vector called balls_sorteados.
    unsigned int  i;
    unsigned int  n;
    unsigned int aux=0,aux2=0;
    int *vetor;

    /*---------------------------- gera um vetor com números aleatórios não repetidos -----------------------------------------------*/
    /* ---------------------------- generates a vector with random numbers not repeated ------------ -----------------------------------*/

    vetor = calloc(numero_de_bolas,sizeof(int));    // cria um vetor dinâmico de inteiros para guardar os números aleatórios gerados
                                                    // creates a dynamic vector of integers to store the generated random numbers
            for(i=0;i<numero_de_bolas;i++){

                            vetor[i]=rand()%60+1;
            }

    /*---------------------------- organiza os dados do vetor na forma crescente -----------------------------------------------*/
    /*---------------------------- arranges the vector data in ascending form ------------ -----------------------------------*/
    do{
            for(i=0;i<(numero_de_bolas-1);i++){             //percorre o vetor                                      //cycle the vector
                    if(vetor[i]>vetor[i+1]){                //se tiver um numero que é maior que seu consecutivo    //if you have a number that is greater than your consecutive
                            aux2 = vetor[i+1];              //mude de posição com ele                               //change position with him
                            vetor[i+1] = vetor[i];
                            vetor[i] = aux2;
                    }else if(vetor[i]==vetor[i+1])          //se dois números forem iguais                          //if two numbers are the same
                    {
                        while(vetor[i]==vetor[i+1])         //enquanto for igual                                    //as long as it is the same
                            {
                            vetor[i+1]=rand()%60+1;         //gera um número randômico entre 1 e 60                 //generates a random number between 1 and 60
                            }
                    }
            }
        aux++;
    }while(aux!=numero_de_bolas);               //enquanto não verificar a realocação de números repita o código    //as long as you don't check the number reallocation repeat the code

    /*---------------------------- colocar o vetor na forma de caracteres para ser arquivado -----------------------------------------------*/
    /*---------------------------- put the vector as characters to be archived    ----------------------------------------------------------*/

    for(i = 0; i<(numero_de_bolas); i++){        // percorre o vetor auxiliar                                           // traverses the auxiliary vector
        n = vetor[i];                            // passa o valor inteiro vetor auxiliar para n                         // passes the auxiliary vector integer value to n
        if(n/10==0){                             // verifica se n é um numero menor que 10 se for passa pela condição   // check if n is a number less than 10 if it goes through the condition
            bolas_sorteadas[i*3] =48;            // recebe o "0"                                                        // receive "0"
            bolas_sorteadas[i*3+1] = n+48;       // recebe um numero que pode ser 1 até 9                               // receives a number that can be 1 to 9
        }
        else{                                    // caso contrário significa que o numero gerado aleatoriamente foi maior que 10   // otherwise means that the randomly generated number was greater than 10
            bolas_sorteadas[i*3] = n/10+48;      // recebe o primeiro algarismo                                         // receives the first digit
            bolas_sorteadas[i*3+1] = n%10+48;    // recebe o segundo algarismo                                           // receives the second digit
        }
        bolas_sorteadas[i*3+2] = 32;             // coloca um caractere espaço                                          // put a space character
    }
    bolas_sorteadas[3*numero_de_bolas-1] = '\n'; // substitui o ultimo espaço de caractere pelo caractere \n que representa uma quebra de linha  // replace the last character space with the character \ n that represents a line break
    free(vetor);                                 // libera o espaço que foi alocado dinamicamente                       // frees up space that has been dynamically allocated

}

void verificar_repeticoes(FILE *arquivo){           //O objetivo dessa é verificar se tem repetição de jogos no arquivo resultados.txt
                                                    // The purpose of this is to check if there are repetitions of games in the results.txt file
    int i;
    char *vetor;
    char *vetor2;

    /*---------------------------- gera dois vetores auxiliares para organizar e modificar o arquivo -----------------------------------------------*/
    /*---------------------------- generates two auxiliary vectors to organize and modify the file   -----------------------------------------------*/

    vetor = calloc(numero_de_bolas,sizeof(char));   // cria um vetor dinâmico para guardar os jogos         // create a dynamic array to store games
    vetor2 = calloc(numero_de_bolas,sizeof(char));  // cria um vetor dinâmico para guardar os jogos         // create a dynamic array to store games


    //aqui é iniciado um processo de repetição que vai pegar cada linha do arquivo para comparar com as outras linhas
    //here a repetition process is started that will take each line of the file to compare with the other lines
    for(i=0;i<(numero_de_jogos-1);i++){
            fread(vetor, sizeof(char), strlen(vetor), arquivo);    // pega os dados de uma linha do arquivo         // get data from one line of file
                for(i=0;i<(numero_de_jogos-2);i++){
                    fread(vetor2, sizeof(char), strlen(vetor2), arquivo);    //pega os dados de outra linha do arquivo para comparação               // get data from another line in the file for comparison
                    while(vetor==vetor2){                                    //se forem iguais é criado um loop que gera uma novo jogo e enquanto    // if they are the same a loop is created that generates a new game and while
                        gerador_aleatorio();
                        fwrite(bolas_sorteadas,sizeof(char),strlen(bolas_sorteadas),arquivo);
                        fread(vetor2, sizeof(char), strlen(vetor2), arquivo);    //pega os dados da linha para nova comparação          // get row data for new comparison
                    }
                }
    }
        free(vetor);    // libera o espaço que foi alocado dinamicamente    // frees up space that has been dynamically allocated
        free(vetor2);   // libera o espaço que foi alocado dinamicamente    // frees up space that has been dynamically allocated

}



/********************   Início do código principal   *********************************/
/********************   Start of main code           *********************************/

int main()
{
    /*-------------------- variáveis -------------------------------------------------*/
    /*-------------------- variables -------------------------------------------------*/
    int resposta;
    float numero_max_jogos;
    int aux,i,j;


/******* Cria ou abre o arquivo se já existir onde ficará alocado os resultados ******/
/******* Create or open the file if it already exists where the results will be allocated ******/

        // criando a variável ponteiro para o arquivo
        // creating the pointer variable for the file
        FILE *jogos;

        //abrindo o arquivo
        //opening the file
        jogos = fopen("resultados.txt", "w+");

        //testando se o arquivo foi realmente criado
        //testing whether the file was actually created
        if(jogos == NULL)
            {
                printf("Erro na abertura do arquivo!");
            return 1;
            }


/******** Pede as informações de quantidade de jogos e número de bolas ao usuário ********/
/******** Ask the user for the number of games and number of balls ********/

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
                scanf("%d",&numero_de_jogos);                       //inserção do número de jogos                                //insert number of games
            }while(numero_de_jogos<1);                              //se o número de jogos for menor que 1 repete o pedido       //if the number of games is less than 1 repeat the request

            do{
                printf("2) Digite o número de bolas que os jogos devem ter:");
                scanf("%d",&numero_de_bolas);                       //inserção do número de bolas                                       //insert number of balls
            }while(numero_de_bolas<6||numero_de_bolas>15);          //se o número de bolas não estiver entre 6 e 15 repete o pedido     //if the number of balls is not between 6 and 15 repeat the order

            numero_max_jogos = combinacao(60,numero_de_bolas);      //verifica por análise combinatória a quantidade máxima de jogos que pode existir com essa quantidade de bolas
                                                                    // checks by combinatorial analysis the maximum number of games that can exist with that number of balls

            if(numero_max_jogos<numero_de_jogos){                   //se a quantidade de jogos não for possível de realizar apresenta a quantidade máxima possível e
                                                                    //pergunta se quer recolocar os dados para continuar, ou se deseja sair

                printf("\n");                                       // if the number of games is not possible, it shows the maximum amount possible and asks if
                                                                    //you want to re-enter the data to continue, or if you want to leave
                printf("o numero de jogos que foi pedido não é possível de realizar, o número máximo para essa quantidade de bolas é %f",numero_max_jogos);
                printf("\n");
                printf("se deseja colocar novamente os dados digite 1 e pressione enter ou qualquer tecla pra sair");
                scanf("%d",&resposta);                              //coleta a decisão                                                      // collect the decision
                if(resposta!=1){                                    //se decisão for diferente de repetir a colocação de dados novos        // if the decision is different to repeat the placement of new data
                    exit(1);                                        //o programa é finalizado                                               // the program is terminated
                }
            }
        }while(resposta==1);                                        //enquanto a resposta for de recolocar os dados repita                  // as long as the answer is to reload the data repeat


        printf("\n");
        printf("      Espere um pouco......    ");
        printf("\n");
        printf("\n");

/***************************  Gera os números aleatórios   ********************************/
/***************************  Generates random numbers     ********************************/

        bolas_sorteadas = calloc(3*numero_de_bolas,sizeof(char));   // cria um vetor dinâmico para guardar os números aleatórios no formato char
                                                                    // create a dynamic array to store random numbers in char format

        srand(time(NULL));                                          // inicializar a semente do gerador de números aleatórios
                                                                    // initialize the seed of the random number generator

        aux = numero_de_jogos;                                      // passa o valor do numero de jogos para variável aux
        do{                                                         // passes the value of the number of games to the aux variable

            gerador_aleatorio();                                                //gera os números aleatórios e guar no vetor bolas_sorteadas
                                                                                // generate the random numbers and keep in the vector balls_sorteados

            fwrite(bolas_sorteadas,sizeof(char),strlen(bolas_sorteadas),jogos); //usando fwrite para armazenar a string no arquivo
                                                                                //using fwrite to store the string in the file

        aux--;                                                                  //decrementa o aux
        }while(aux!=0);                                                         //decrement or aux

        fclose(jogos);                                                           //usando fclose para fechar o arquivo
                                                                                 //using fclose to close the file

/*************************** Verificar se tem jogos repetidos, modificar se tiver ********************************/
/*************************** Check if you have repeated games, modify if you have ********************************/

        verificar_repeticoes(jogos);

/*****************************        Apresentação dos resultados    ********************************/
/*****************************        Results presentation           ********************************/

        printf("\n");
        printf("*************************************************\n");
        printf("*****       Os resultados possíveis      ********\n");
        printf("*************************************************\n");
        printf("\n");

        jogos = fopen("resultados.txt", "r");       //abrindo o arquivo modo leitura mas permite escrita
                                                    //opening the file in read mode but allows writing
  for(i=0;i<numero_de_jogos;i++)
    {
       fread(bolas_sorteadas, sizeof(char), strlen(bolas_sorteadas), jogos);    // lê as linhas do arquivo              //read lines from file
       printf("%s",bolas_sorteadas);                                            // mostra as linhas do arquivo na tela  //shows the file lines on the screen
    }

  fclose(jogos);            //usando fclose para fechar o arquivo               //using fclose to close the file
  free(bolas_sorteadas);    //libera o espaço que foi alocado dinamicamente     //frees up space that has been dynamically allocated

  printf("\n");
  printf("Dados gravados com sucesso!");

  printf("\n");

        printf("*************************************************\n");
        printf("************   Fim do código    *****************\n");
        printf("*************************************************\n");

    return 0;
}
/********************   Fim do código principal   *********************************/
/********************   End of main code          *********************************/
