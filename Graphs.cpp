#include "Graphs.h"
#include "DFS.cpp"

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
		printf("Adjacency List - 0\nAdjacency Vector - 1\nAdjacency Matrix - 2(not recommended for +250k vertices)\n\n");
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

			// Dynamic_Bitset
	/*
			if (a == BITSETM){
				G->initAdjMatrixSet();
				printf("Finished initializing.\n");
				int a, b;
				while (fscanf(in, "%d %d", &a, &b) == 2){
					G->addEdgeMatrixSet(a, b);
				}
				printf("Finished assigning edges.\n");
			}*/
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
	int x;
	printf("\nEnter the 1st tree's root (the valid interval is [%d, %d]): ", 1, grafo->vertexNum);
	cin >> x;
	
	FILE* arq2;
	arq2 = fopen("components.txt", "w");
	fclose(arq2);
	
	int* a = new int (1);
	int* b = new int (grafo->vertexNum);
	while (*b > 0){
		iterDFS(grafo, &(x), b, arq2, a);
		printf("%d\n", *b);
	}

	fprintf(arq1, "Número de Componentes Conexos: %d\n\n", *a);
	for (int k = 1; k <= grafo->vertexNum; k++){
		fprintf(arq1, "# %d = Pai: %d; Nível: %d\n", k, grafo->pai[k], grafo->nivel[k]);
	}
	printf("Finished printing.\n");
}
