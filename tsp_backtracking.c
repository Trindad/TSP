/* 	Problema do caixeiro viajante usando backtracking.
	compile: gcc nome_prog.c -o nome_prog -Wall
	execute:./nome_prog

	Aluna: Silvana Trindade 
	email:syletri@gmail.com
*/
#include <stdio.h>
#define TAM 15

int x[TAM],usado[TAM];
int adj[TAM][TAM];
int caminho[TAM][TAM],wght[TAM];
int c,min;

int caminhoOk(int k,int n);
void ProblemaCaixeiroViajante(int k,int n);
void EncontrarMin(int n);

int main(void)
{
	int i,N,j;
	int edg;
	printf("\n\n\t\tPROBLEMA DO CAIXEIRO VIAJANTE\n\n");
	printf("\n\tEntre com o número de Cidades: ");
	scanf("%d",&N);
	printf("\n\n Digite o custo do caminho entre as cidades c1 e c2, se este existir. Do contrário, digite 0:\n\n");
	printf("\n\tCIDADES\t\tCUSTO\n\n");
	for(i = 0; i < N; i++)
		for(j = i+1;j < N; j++)
		{
			printf("\n\t %d------ %d \t:",i,j);
			scanf("%d",&edg);
			if(edg)
				adj[i][j] = adj[j][i] = edg;
		}
		usado[0] = 1;
		ProblemaCaixeiroViajante(1,N);
		if(!c)
			
			printf("\n\n\t\tNENHUM CAMINHO ENCONTRADO QUE CUBRA TODAS AS CIDADES\n\n");
		else
		{
			printf("\n\n\t\tCUSTO MINIMO %d E OS CAMINHOS SÃO \n\n",min);
			EncontrarMin(N);
		}
	return 0;
} 

int caminhoOk(int k,int N)
{
	if(usado[x[k]])
		return 0;
	if(k < N-1)
		return(adj[x[k-1]][x[k]]);
	else
		return(adj[x[k-1]][x[k]] && adj[x[k]][x[0]]);
}
void ProblemaCaixeiroViajante(int k,int N)
{
	int i,sum; 

	for(x[k] = 1;x[k] < N; x[k]++)
	{
		if(caminhoOk(k,N))
		{
			usado[x[k]]=1;
			if(k == N-1)
			{
				sum = 0;
				printf("\n\n\tPOSSÍVEL CAMINHO %d : ",c+1);
				for(i = 0; i < N; i++)
				{
					printf("%d\t",x[i]);
					caminho[c][i] = x[i];
					sum += adj[x[i]][x[i+1]];
				}
				printf(" : %d",sum);
				wght[c] = sum;
				if(c == 0 || sum < min)
					min = sum;
					c++;
					usado[x[k]] = 0;
			}
			else
				ProblemaCaixeiroViajante(k+1,N);
				usado[x[k]] = 0;
		}
	}
}
void EncontrarMin(int N)
{
	int i,j;
	for(i = 0; i < c; i++)
		if(wght[i] == min)
		{
			printf("\n\n\tCAMINHO MINIMO : ");
			for(j = 0; j < N; j++)
				printf("%d\t",caminho[i][j]);
		}
}
