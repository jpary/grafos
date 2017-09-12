#include "Graphs.h"
#include "HeapFunctions.h"
#include "DFS.h"
#include "BFS.h"
#include <string>

Graph* repr(){
	Graph* G;
	
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
		
		G = new Graph;
		int x = G->initEssentials(n, a);
		
		if (x) printf("Couldn't create graph.");
		else{
		
			// Lista Encadeada

			if (a == LINK_LIST){
				printf("List\n\n");
				G->initAdjList();
				printf("Finished initializing.\n");
				int a, b;
				while (fscanf(in, "%d %d", &a, &b) == 2){
					G->addEdgeList(a, b);
				}
				printf("Finished assigning edges.\n");
			}

			// Vetor

			if (a == VECTOR){
				printf("Vector\n\n");
				G->initAdjVector();
				printf("Finished initializing.\n");
				int a, b;
				while (fscanf(in, "%d %d", &a, &b) == 2){
					G->addEdgeVector(a, b);
				}
				printf("Finished assigning edges.\n");
			}

			// Vector<bool>

			if (a == BOOL_MATRIX){
				printf("Bool Matrix\n\n");
				G->initAdjMatrixBool();
				printf("Finished initializing.\n");
				int a, b;
				while (fscanf(in, "%d %d", &a, &b) == 2){
					G->addEdgeMatrixBool(a, b);
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
	Graph* grafo = repr();
	FILE* arq1;
	arq1 = fopen("vertices.txt", "w");
	
	int search;
	printf("\nWhich search method would you like?\n\n");
	printf("BFS (Breadth-First Search) - 0\nDFS (Depth-First Search) - 1\nDiameter (BFS-only) - 2\n\n");
	cin >> search;

	FILE* arq2;
	arq2 = fopen("components.txt", "w");
	fclose(arq2);

	string s;
	if (search == 1) s = "DFS";
	else s = "BFS";

	int* a = new int (1);
		
	int* tamanho = new int (grafo->vertexNum);
	if (search != 2){
		
		int root;
		printf("\nEnter the 1st tree's root (the valid interval is [%d, %d]): ", 1, grafo->vertexNum);
		cin >> root;
		printf("\n");

		int d;
		printf("\nWould you like to do a single %s - 0\nOr calculate all of its components? - 1\n\n", s.c_str());
		cin >> d;
		
		if (d == 1){
			
			while (*tamanho > 0){
				if (search == 0) BFS(grafo, &root, tamanho, arq2, a, d, 0);
				if (search == 1) DFS(grafo, &root, tamanho, arq2, a, d);
				printf("%d\n", *tamanho);
			}
			fprintf(arq1, "Número de Componentes Conexos: %d\n\n", *a);
		}

		if (d == 0){
			if (search == 0) BFS(grafo, &root, tamanho, arq2, a, d, 0);
			if (search == 1) DFS(grafo, &root, tamanho, arq2, a, d);
		}	

		for (int k = 1; k <= grafo->vertexNum; k++){
			if (grafo->descobertos[k-1] == 1) fprintf(arq1, "# %d = Pai: %d; Nível: %d\n", k, grafo->pai[k], grafo->nivel[k]);
		}
		printf("Finished printing.\n");
	}
	else{
		diameter(grafo, grafo->vertexNum, arq2, a);
	}
}
