/*
*
*---------------------------------------------------------------------------------------------
*
*    Declaração de problema: Para obter a solução do Problema do Caixeiro-Viajante, utilizando:
*Bellman-Held-Karp algoritmos de programação dinâmica.
* Compile : gcc nome_arquivo.c -o main -g -lm 
* Execute : ./main
*
-----------------------------------------------------------------------------------------------
nome : silvana trindade
email: syletri@gmail
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//estrutura para a cidade 

typedef struct
{
        int x;
        int y;

} Cidade;


int main(void)
{
        
        clock_t t1, t2; /* Variaveis para controlar o tempo */
        double timeTotal; /* Total tempo*/

        int i,j,k; 
        int n; //numero de cidades
        int **dist_tab; //armazena na tabela, a distância entre as cidades
        
        /* 
            e desde que o custo é diretamente proporcional à distância,
            pode-se usar a distância total, como uma medição qualitativa de custo.
        */
        printf("\nEntre com o numero de cidades = ");
        scanf("%d", &n);

        if (n > 20)
        {
            printf("Numero de Cidades muito Grande para mim processar ...\n");
            exit(1);
        }
        
        Cidade* arr_Cidades  = (Cidade*) malloc ( n*sizeof(Cidade) ); //creating an array of cities
        
        dist_tab = (int**) malloc (n*sizeof(int*)); //allocating space for distance table

        if (dist_tab == NULL)
        {
            printf("ERROR ");
            exit(1);
        }

        for(i = 0; i < n; i++)
        {
                dist_tab[i] = (int*) malloc (sizeof(int)*n);

                if (dist_tab[i] == NULL)
                {
                    printf("ERROR ");exit(1);
                }
        }
        srand((unsigned int) time(NULL)); //gerar numeros aleatórios 
        
        //Gera Cidades

        printf("\nLista Cidades::\n");

        for(i = 0; i < n; i++)
         {
             /*        
                //caso queira digitar 
                printf("\n Entre com X e Y \n");
                scanf("%d",&arr_Cidades[i].x);
                scanf("%d",&arr_Cidades[i].y);
            */
                arr_Cidades[i].x = (int)rand()%9;
                arr_Cidades[i].y = (int)rand()%9;
         }

        printf("\n");

        for(i = 0; i < n; i++)
        {
            printf("(%d,%d) ", arr_Cidades[i].x, arr_Cidades[i].y); //imprime as cidades selementocionadas
        }
        printf("\n\n Imprime matriz de Adjacência :\n\n");
        for(i = 0; i < n; i++)
        {
                for(j = 0; j<n; j++)
                {
                        dist_tab[i][j] = sqrt(pow((arr_Cidades[i].x-arr_Cidades[j].x),2)+pow((arr_Cidades[i].y-arr_Cidades[j].y),2));
                        printf(" %d ", dist_tab[i][j]);
                }
                printf("\n");
        }
        printf("\n");
        
        int min;
                

        t1 = clock(); /*inicializa tempo*/

        printf("TSP Algoritmo Dinamico:\n");
        
        /*
            Matriz B e L são matrizes 2D de tamanho [2 ^ (n-1)] X [n-1]
          O índice de linha denota o conjunto X da Bellman-Herd-Karp algoritmo de programação dinâmica
          A cidade de partida é considerado 0. A turnê deve terminar na cidade (j +1). Aqui j é o índice de coluna.
          O número da linha, se expressa em binário, denota as cidades que estão incluídas no conjunto X.
          Um zero indica que a cidade não está presente em conjunto X e um indica que está presente.
          O bit menos significativo representa o Cidade 1, o segundo bit menos representa Cidade 2 e assim por diante.
          Do mesmo modo, o bit mais significativo representa o (n-1) po Cidade.
          B armazena o Custo mínimo possível de viajar de 0 a (j +1) ª cidade visitando cada cidade em X uma vez e volta a 0.
          L armazena a cidade anterior, que foi visitada antes de viajar para a cidade (j +1), dando-nos, assim, uma trilha para o caminho real tomada.
        */
        int** B = ( int** ) malloc ( ( (int)pow(2,n-1) ) * sizeof(int*) );
        int** L = ( int** ) malloc ( ( (int)pow(2,n-1) ) * sizeof(int*) );

        if (L == NULL || B == NULL )
        {
           printf("ERROR alocação L e B");
           exit(1);
        }
        for(i = 0; i < (int)pow(2,n-1); i++)
        { 
                B[i] = ( int* ) malloc ( sizeof(int)*(n-1) );
                L[i] = ( int* ) malloc ( sizeof(int)*(n-1) );

                if (L[i] == NULL || B[i] == NULL)
                {
                    printf("ERROR alocação");
                    exit(1);
                }
        }
        
        for(j = 0; j < n-1; j++)
        {
             B[0][j] = dist_tab[0][j+1]; //Para a primeira linha, o conjunto de X está vazio
             L[0][j] = 0; //a cidade visitada anterior é 0, neste caso
        }
        for(i = 0; i < (int)pow(2,n-1); i++)
        {
                for(j = 0; j < n-1; j++)
                {
                        
                    if(( i&( 1 << j )) != 0)
                    {
                         B[i][j] = -1; //para valores do conjunto X inválido, -1 é armazenada na matriz
                         L[i][j] = -1; //inválido, quer dizer conjunto X tal que contém destino cidade situada a 1
                    }
                    else
                    {
                        B[i][j] = 0; //para valores do conjunto X inválido, -1 é armazenada na matriz
                        L[i][j] = 0; //inválido, quer dizer conjunto X tal que contém destino cidade situada a 1
                    }
                }
        }
        for(i = 0; i < (int)pow(2,n-1); i++)
        {
                for(j = 0; j < n-1; j++)
                {
                        
                    
                        printf(" %d ",B[i][j] );
                }
                printf("\n");
        }

        
        /*progrmação dinamica Held-Karp*/
        
        for(i = 1; i < (int)pow(2,n-1); i++)
        {
                for(j = 0; j < (n-1); j++)
                {
                        if( B[i][j] != -1 && B[i] != NULL)
                        {
                                min =-1; 
                                for(k = 0; k < n-1; k++)
                                {
                                    if(( (1 << k) & i) != 0) //checando se o bit k de i é 1
                                    {
                                         //se é 1 o bit,que defini-lo para zero e calcular o mínimo com os valores nas linhas anteriores.
                                        int remcusto = B[i-(int)pow(2,k)][k]+dist_tab[k+1][j+1];

                                        if((min == -1) || (min > remcusto))
                                        {
                                                min = remcusto;
                                                L[i][j] = k+1; //once the minimum is obtained, the previously visited city is stored in matrix L
                                        }
                                    }
                                        
                                }
                                B[i][j] = min;    
                        }
                        
                }
                
        }
        int leg_min =-1;
        min =-1;
        
        for(i = 0; i < n-1; i++)
        {
                int mincusto = B[(int)(pow(2,n-1)-pow(2,i))-1][i] + dist_tab[i+1][0];

                if((mincusto < min) || (min == -1))
                {
                    min = mincusto; //calcular o custo mínimo global, definindo cada cidade possível, a última cidade visitada
                    leg_min = i+1; //leg_min  armazena a cidade que foi visitada última minima
                }
        }
        
        
        int set_min = (int)pow(2,n-1)-1-(int)pow(2,leg_min-1);

        printf("0-");

        while(leg_min != 0)
        {
                printf("%d-",leg_min);
                leg_min = L[set_min][leg_min-1]; //atualização leg_min para acompanhar o caminho percorrido para se obter o mínimo.
                set_min-= (int)pow(2,leg_min-1);
        }
        printf("Custo minimo = %d\n",min);
        
        t2 = clock(); /* Anote o tempo após o bloco sair */

        /* Calcula o tempo necessário por execução do bloco */
        timeTotal = ( (double)(t2 - t1) / (double)CLOCKS_PER_SEC);
        printf("%f\n",timeTotal);

        for (i = 0; i < n; i++) {free(dist_tab[i]);}
        free(dist_tab);

        for (i = 0; i < (int)pow(2,n-1); i++) {free(L[i]);free(B[i]);}
        free(L);free(B);

        
        free(arr_Cidades);

        return 0;
}
