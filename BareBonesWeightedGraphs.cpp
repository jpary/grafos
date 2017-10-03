#include "WeightGraph.h"
#include "IntHeapFunctions.h"
#include "Dijkstra.h"
#include "Prim.h"
#include <string>
/*#include <windows.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter(){
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}*/

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
	
	double time;

	if (!in) fprintf(out, "Could not open file.\n");
	else{
		int n, a;
		fscanf(in, "%d", &n);
		
		printf("\nPlease choose one of the 3\nPossible graph representations:\n\n");
		printf("Adjacency List - 0\nAdjacency Vector - 1\nAdjacency Matrix - 2 (not recommended for +250k vertices)\n\n");
		
		cin >> a;
		
		//StartCounter();

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
		//time = GetCounter();
	}
	//StartCounter();
	G->printObj(out);
	//double y = GetCounter();

	printf("Finished printing.\n\n");
	//cout << time+y << "s.\n";

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
	printf("Dijkstra - 0\nPrim - 1\nAverage Distance (Dijkstra-only) - 2\n\n");
	cin >> search;

	if (!grafo->dijkstra && (search == 2 || search == 0)){
		printf("Cannot calculate Dijkstra because of negative edge weights.\n");
		return 1;
	}

	int path;
	int root;
	
	if (search != 2){
		printf("\nEnter the 1st tree's root (the valid interval is [1, %d]): ", grafo->vertexNum);
		cin >> root;
		printf("\n");		
		if (search == 0){
			printf("Would you like to calculate:\n0 - Every minimum path?; or\n[1, %d] - Only the chosen vertex's?: ", grafo->vertexNum);
			cin >> path;
			printf("\n");	
		}
	}

	if (search == 0){
		//StartCounter();
		dijkstra(grafo, arq1, root, false, path);
		//cout << GetCounter() << "s.\n";
		fclose(arq1);
	}

	if (search == 1){
	//	StartCounter();
		prim(grafo, arq1, root);
	//	cout << GetCounter() << "s.\n";
		fclose(arq1);	
	}

	if (search == 2){
	//	StartCounter();
		avgDistance(grafo, arq1);
	//	cout << GetCounter() << "s.\n";
		fclose(arq1);
	}
	return 0;
}