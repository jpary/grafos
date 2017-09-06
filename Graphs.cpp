#include <iostream>
#include <bitset>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <boost/dynamic_bitset.hpp>

using namespace std;

typedef struct a{
	int vertex;
	struct a* nextVertex;
} LinkList;

class Graph{

	LinkList** AdjList; // Lista de Adjacência
	vector<int>* AdjVector; // Vetor de Adjacência 
	vector<bool>* AdjMatrixBool; // Matriz de Adjacência; vector<bool>
	boost::dynamic_bitset<>* AdjMatrixSet; // Matriz de Adjacência; boost::dynamic_bitset
	int vertexNum; // Número de Vértices
	int edgeNum; // Número de Arestas
	int* vertexDegree; // Vetor de Grau de Arestas
	int* degrees; // Vetor Número de Vértices com grau x

	public:

//-------------------Lista de Adjacência---------------------------------------------------------------//
	
		int initAdjList(int size){
			if (size <= 0) return 1;
			edgeNum = 0; // Nenhuma aresta formada
			AdjList = new LinkList* [size]; // Criando array dos ponteiros iniciais 
							// das listas de adjacências de cada vértice
			vertexNum = size; // Inicializando número de vértices
			vertexDegree = new int [size] ();
			degrees = new int [size] ();
			degrees[0] = vertexNum;
			return 0;
		}

		void addEdgeList(int v1, int v2){
			LinkList* newItem1 = new LinkList;
			LinkList* newItem2 = new LinkList;
			
			newItem1->vertex = v2;
			newItem2->vertex = v1;
			
			newItem1->nextVertex = AdjList[v2-1];
			newItem2->nextVertex = AdjList[v1-1];

			AdjList[v1-1] = newItem1;
			AdjList[v2-1] = newItem2;

			edgeNum++;	

			degrees[vertexDegree[v1-1]]--;
			degrees[vertexDegree[v1-1]+1]++;
			degrees[vertexDegree[v2-1]]--;
			degrees[vertexDegree[v2-1]+1]++;

			vertexDegree[v1-1]++;
			vertexDegree[v2-1]++;
		}

//-----------------Vetor de Adjacência-----------------------------------------------------------------//
		
		int initAdjVector(int size){
			if (size <= 0) return 1;
			edgeNum = 0; 
			AdjVector = new vector<int> [size];
			vertexNum = size;
			free(vertexDegree);
			degrees = new int [size] ();
			degrees[0] = vertexNum;
			return 0;
		}

		void addEdgeVector(int v1, int v2){
			int size1 = AdjVector[v1-1].size();
			int size2 = AdjVector[v2-1].size();

			insert(AdjVector[v1-1], v2);
			insert(AdjVector[v2-1], v1);

			edgeNum++;

			degrees[size1]--;
			degrees[size1+1]++;
			degrees[size2]--;
			degrees[size2+1]++;
		}

//-------------------Matriz de Adjacência; vector<bool>------------------------------------------------//
		
		int initAdjMatrixBool(int size){
			if (size <= 0) return 1;
			edgeNum = 0;
			vertexNum = size;
			AdjMatrixBool = new vector<bool> [size];
			for (int i = 0; i < size; i++){
				AdjMatrixBool[i].resize(size, false);
			}
			vertexDegree = new int [size] ();
			degrees = new int [size] ();
			degrees[0] = vertexNum;
			return 0;
		}

		void addEdgeMatrixBool(int v1, int v2){
			AdjMatrixBool[v1-1][v2-1] = 1;
			AdjMatrixBool[v2-1][v1-1] = 1;

			edgeNum++;
			
			degrees[vertexDegree[v1-1]]--;
			degrees[vertexDegree[v1-1]+1]++;
			degrees[vertexDegree[v2-1]]--;
			degrees[vertexDegree[v2-1]+1]++;

			vertexDegree[v1-1]++;
			vertexDegree[v2-1]++;
		}
	
//-------------------Matriz de Adjacência; boost::dynamic_bitset--------------------------------------//

		int initAdjMatrixSet(int size){
			if (size <= 0) return 1;
			edgeNum = 0;
			vertexNum = size;
			boost:: dynamic_bitset<> x (size);
			AdjMatrixSet = new boost::dynamic_bitset<> [size];
			for (int i = 0; i < size; i++){
				AdjMatrixSet[i] (x);
			}
			vertexDegree = new int [size] ();
			degrees = new int [size] ();
			degrees[0] = vertexNum;
			return 0;
		}

		void addEdgeMatrixSet(int v1, int v2){
			AdjMatrixSet[v1-1][v2-1] = 1;
			AdjMatrixSet[v2-1][v1-1] = 1;
			
			edgeNum++;

			degrees[vertexDegree[v1-1]]--;
			degrees[vertexDegree[v1-1]+1]++;
			degrees[vertexDegree[v2-1]]--;
			degrees[vertexDegree[v2-1]+1]++;

			vertexDegree[v1-1]++;
			vertexDegree[v2-1]++;
		}
	
//--------------Printando informações do Grafo---------------------------------------------------------//
	
		void printObj(FILE* file){
			fprintf(file, "# n = %d\n", vertexNum);
			fprintf(file, "# m = %d\n", edgeNum);
			fprintf(file, "# d_medio = %.10f\n", (float) (2*edgeNum)/vertexNum);
			for (int i = 0; i < vertexNum; i++){
				fprintf(file, "%d %.10f\n", i, (float) degrees[i]/vertexNum);
			}
		}
};

int main(){
	vector<int> v {100, 101, 103, 104};
	printf("%d\n", insert(v, 102));
	Graph G;
	FILE* in;
	FILE* out;
	int a;	
	cin >> a;
	in = fopen("dblp.txt", "r");
	out = fopen("output.txt", "w");
	if (!in) fprintf(out, "Could not open file.\n");
	else{
		int n;
		fscanf(in, "%d", &n);
		if (a == 0){
			int x = G.initAdjList(n);
			printf("Finished initializing.\n");
			if (x == 1) fprintf(out, "Couldn't create graph.\n");
			else{
				int a, b;
				while (fscanf(in, "%d %d", &a, &b) == 2){
					G.addEdgeList(a, b);
				}
				printf("Finished assigning edges.\n");
			}
		}
		if (a == 1){
			int x = G.initAdjVector(n);
			printf("Finished initializing.\n");
			if (x == 1) fprintf(out, "Couldn't create graph.\n");
			else{
				int a, b;
				while (fscanf(in, "%d %d", &a, &b) == 2){
					G.addEdgeVector(a, b);
				}
				printf("Finished assigning edges.\n");
			}
		}
		if (a == 2){
			int x = G.initAdjMatrixBool(n);
			printf("Finished initializing.\n");
			if (x == 1) fprintf(out, "Couldn't create graph.\n");
			else{
				int a, b;
				while (fscanf(in, "%d %d", &a, &b) == 2){
					G.addEdgeMatrixBool(a, b);
				}
				printf("Finished assigning edges.\n");
			}
		}
		if (a == 3){
			int x = G.initAdjMatrixSet(n);
			printf("Finished initializing.\n");
			if (x == 1) fprintf(out, "Couldn't create graph.\n");
			else{
				int a, b;
				while (fscanf(in, "%d %d", &a, &b) == 2){
					G.addEdgeMatrixSet(a, b);
				}
				printf("Finished assigning edges.\n");
			}
		}
	}
	G.printObj(out);
	printf("Finished printing.\n");
	fclose(in);
	fclose(out);
}
