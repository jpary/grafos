#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int** alocarMatriz(int Linhas,int Colunas);

int main(void){
	char url[]="dblp.txt";
  int a1, a2, total, x, z, y, zz, cont=0;
	int** pM;
	FILE *arq;
	arq = fopen(url, "r");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
    fscanf(arq,"%d\n", &total);
		pM = alocarMatriz(total, total/32);
		/*
		while( (fscanf(arq,"%d %d\n", &a1, &a2))!=EOF ){
			x = a2/16;
			z = a2 - (x*16);
			int pot= pow(2, z);
			pM[a1][x]+= pot;
			//y = a1/16;
			//zz = a1 - (y*16);
			//int pott= pow(2, zz);
			//pM[a2][y]+= pott;
			cont++;
			//printf("%d %d\n", a1, a2);
		}*/
  }
	fclose(arq);
	printf("Coube: %d\n", cont);
	printf("%d\n", pM[0][1]);
	/*
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			printf("%d ", pM[i][j]);
		}
		printf("\n");
	}*/

	return 0;
}

int** alocarMatriz(int Linhas,int Colunas){ //Recebe a quantidade de Linhas e Colunas como Parâmetro

  int i,j; //Variáveis Auxiliares

  int **m = malloc(Linhas * sizeof(unsigned*)); //Aloca um Vetor de Ponteiros

  for (i = 0; i < Linhas; i++){ //Percorre as linhas do Vetor de Ponteiros
       m[i] = malloc(Colunas * sizeof(unsigned)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
       for (j = 0; j < Colunas; j++){ //Percorre o Vetor de Inteiros atual.
            m[i][j] = 0; //Inicializa com 0.
       }
  }
return m; //Retorna o Ponteiro para a Matriz Alocada
}
