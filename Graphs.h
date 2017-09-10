#include <iostream>
#include <bitset>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <set>
// #include <boost/dynamic_bitset.hpp>

using namespace std;

#define LINK_LIST 0
#define VECTOR 1
#define BOOL_MATRIX 2
#define BITSET 3

typedef struct a{
	int vertex;
	struct a* nextVertex;
} LinkList;

class Graph{
	
	public:

		int representation;
		int* pai;
		int* nivel;
		vector<vector<int> > componentes;
		
		LinkList** AdjList; // Lista de Adjacência
		vector<int>* AdjVector; // Vetor de Adjacência
		vector<bool>* AdjMatrixBool; // Matriz de Adjacência; vector<bool>
		// boost::dynamic_bitset<>* AdjMatrixSet; // Matriz de Adjacência; boost::dynamic_bitset
		
		int vertexNum; // Número de Vértices
		int edgeNum; // Número de Arestas
		int* vertexDegree; // Vetor de Grau de Vértices
		int* degrees; // Vetor Número de Vértices com grau x
		
		vector<bool> descobertos;
		vector<bool> explorados;

		int initEssentials(int size, int x){
			if (size <= 0) return 1;
			
			this->representation = x;
			this->edgeNum = 0; // Nenhuma aresta formada
			this->vertexNum = size; // Inicializando número de vértices
			
			this->degrees = new int [size] ();
			this->degrees[0] = size;
			
			this->pai = new int[size+1];
			this->nivel = new int [size+1];
			
			this->pai[0] = -1;
			this->nivel[0] = -1;
			
			this->descobertos.resize(vertexNum);
			this->explorados.resize(vertexNum);
			
			return 0;
		}

//-------------------Lista de Adjacência---------------------------------------------------------------//
	
		void initAdjList(){
			this->AdjList = new LinkList* [vertexNum]();
			this->vertexDegree = new int [vertexNum]();
		}

		void addEdgeList(int v1, int v2){
			LinkList* newItem1 = new LinkList();
			LinkList* newItem2 = new LinkList();
			
			newItem1->vertex = v2;
			newItem2->vertex = v1;
			
			newItem1->nextVertex = AdjList[v1-1];
			newItem2->nextVertex = AdjList[v2-1];

			this->AdjList[v1-1] = newItem1;
			this->AdjList[v2-1] = newItem2;

			this->edgeNum++;

			this->degrees[vertexDegree[v1-1]]--;
			this->degrees[vertexDegree[v1-1]+1]++;
			this->degrees[vertexDegree[v2-1]]--;
			this->degrees[vertexDegree[v2-1]+1]++;

			this->vertexDegree[v1-1]++;
			this->vertexDegree[v2-1]++;
		}

		void componentRemover(){
			int index = this->componentes.size()-1;
			printf("%d\n", this->componentes[index].size());
			vector<int>::iterator inicio = this->componentes[index].begin();
			vector<int>::iterator fim = this->componentes[index].end();
			this->componentes[index-1].erase(inicio, fim);
			this->componentes.pop_back();
		}

//-----------------Vetor de Adjacência-----------------------------------------------------------------//
		
		void initAdjVector(){
			AdjVector = new vector<int> [vertexNum];
		}

		void addEdgeVector(int v1, int v2){
			int size1 = AdjVector[v1-1].size();
			int size2 = AdjVector[v2-1].size();

			AdjVector[v1-1].push_back(v2);
			AdjVector[v2-1].push_back(v1); 

			edgeNum++;

			degrees[size1]--;
			degrees[size1+1]++;
			degrees[size2]--;
			degrees[size2+1]++;
		}

//-------------------Matriz de Adjacência; vector<bool>------------------------------------------------//
		
		void initAdjMatrixBool(){
			AdjMatrixBool = new vector<bool> [vertexNum];
			for (int i = 0; i < vertexNum; i++){
				AdjMatrixBool[i].resize(vertexNum, false);
			}
			vertexDegree = new int [vertexNum] ();
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
/*
		void initAdjMatrixSet(){
			boost:: dynamic_bitset<> x (vertexNum);
			AdjMatrixSet = new boost::dynamic_bitset<> [vertexNum];
			for (int i = 0; i < vertexNum; i++){
				AdjMatrixSet[i] (x);
			}
			vertexDegree = new int [vertexNum] ();
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
*/
//--------------Printando informações do Grafo---------------------------------------------------------//
	
		void printObj(FILE* file){
			fprintf(file, "# n = %d\n", vertexNum); // Printar número de vértices
			fprintf(file, "# m = %d\n", edgeNum); // Printar número de arestas
			fprintf(file, "# d_medio = %.10f\n", (float) (2*edgeNum)/vertexNum); //
			for (int i = 0; i < vertexNum; i++){
				fprintf(file, "%d %.10f\n", i, (float) degrees[i]/vertexNum);
			}
		}
};
