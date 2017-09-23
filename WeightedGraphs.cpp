#include "Graphs.h"
#include "HeapFunctions.h"
#include "DFS.h"
#include "BFS.h"
#include <string>

WeightGraph* repr(){
	WeightGraph* G;
	
	FILE* in;
	FILE* out;
	
	in = fopen("dblp.txt", "r");
	out = fopen("output.txt", "w");
	
	if (!in) fprintf(out, "Could not open file.\n");
	else{
		int n, a;
		fscanf(in, "%d", &n);
		
		printf("Please choose one of the 3\nPossible graph representations:\n\n");
		printf("Adjacency List - 0\nAdjacency Vector - 1\nAdjacency Matrix - 2 (not recommended for +250k vertices)\n\n");
		
		cin >> a;
		
		G = new WeightGraph;
		int x = G->initEssentials(n, a);
		
		if (x) printf("Couldn't create graph.");
		else{
		
			// Lista Encadeada

			if (a == LINK_LIST){
				printf("List\n\n");
				G->initAdjList();
				printf("Finished initializing.\n");
				int a, b;
				float w;
				while (fscanf(in, "%d %d %f", &a, &b, &w) == 3){
					G->addEdgeList(a, b, w);
				}
				printf("Finished assigning edges.\n");
			}

			// Vetor

			if (a == VECTOR){
				printf("Vector\n\n");
				G->initAdjVector();
				printf("Finished initializing.\n");
				int a, b;
				float w;
				while (fscanf(in, "%d %d %f", &a, &b, &w) == 3){
					G->addEdgeVector(a, b, w);
				}
				printf("Finished assigning edges.\n");
			}

			// Vector<float>

			if (a == MATRIX){
				printf("Matrix\n\n");
				G->initAdjMatrix();
				printf("Finished initializing.\n");
				int a, b;
				float w;
				while (fscanf(in, "%d %d %f", &a, &b, &w) == 3){
					G->addEdgeMatrixBool(a, b, w);
				}
				printf("Finished assigning edges.\n");
			}
		}
	}
	G->printObj(out);
	printf("Finished printing.\n");
	fclose(in);
	fclose(out);
	return G;
}

int main(){
	WeightGraph* grafo = repr();
	FILE* arq1;
	arq1 = fopen("vertices.txt", "w");
	
	int search;
	printf("\nWhich search method would you like?\n\n");
	printf("Dijkstra - 0\nPrim - 1\nKruskal - 2\n\n");
	cin >> search;

	FILE* arq2;
	arq2 = fopen("components.txt", "w");
	fclose(arq2);

	int* a = new int (1);
		
	int* tamanho = new int (grafo->vertexNum);
		
		int root;
		printf("\nEnter the 1st tree's root (the valid interval is [%d, %d]): ", 1, grafo->vertexNum);
		cin >> root;
		printf("\n");

		//Aqui entra Dijkstra/Prim
		//Usar int search.

		for (int k = 1; k <= grafo->vertexNum; k++){
			if (grafo->descobertos[k-1] == 1) fprintf(arq1, "# %d = Pai: %d; Nível: %d\n", k, grafo->pai[k], grafo->nivel[k]);
		}
		printf("Finished printing.\n");
	}
}
