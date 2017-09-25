#include "WeightGraph.h"
#include "IntHeapFunctions.h"
#include "Dijkstra.h"
#include <string>

WeightGraph* repr(){
	
	WeightGraph* G;
	
	FILE* in;
	FILE* out;
	string s;
	printf("\nEnter .txt filename:");
	cin >> s;
	string str = s+".txt";
	in = fopen(str.c_str(), "r");

	while(!in){
		printf("\nNo file found\n");
		printf("\nEnter .txt filename:");
		cin >> s;
		string str = s+".txt";
		in = fopen(str.c_str(), "r");
	}

	out = fopen("output.txt", "w");
	
	if (!in) fprintf(out, "Could not open file.\n");
	else{
		int n, a;
		fscanf(in, "%d", &n);
		
		printf("\nPlease choose one of the 3\nPossible graph representations:\n\n");
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
	printf("Dijkstra - 0\nPrim - 1\n\n");
	cin >> search;

	if (grafo->dijkstra == 0 && search == 0){
		printf("Cannot calculate Dijkstra because of negative edge weights.\n");
		return 1;
	}

	int root;
	printf("\nEnter the 1st tree's root (the valid interval is [%d, %d]): ", 1, grafo->vertexNum);
	cin >> root;
	printf("\n");

	if (search == 0 && grafo->dijkstra == true) dijkstra(grafo, arq1, root);
	return 0;
}
