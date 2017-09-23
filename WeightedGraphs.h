#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

using namespace std;

#define LINK_LIST 0
#define VECTOR 1
#define MATRIX 2

typedef struct a{
	int vertex;
	float weight;
	struct a* nextVertex;
} LinkList;

typedef struct{
	int vertex;
	float weight;
} VectorElem;

class WeightGraph{
	
	public:

		int representation;
		int* pai;
		int* nivel;
		vector<vector<int> > componentes;
		
		LinkList** AdjList; // Lista de Adjacência
		vector<VectorElem>* AdjVector; // Vetor de Adjacência
		vector<float>* AdjMatrix; // Matriz de Adjacência; vector<bool>
		// boost::dynamic_bitset<>* AdjMatrixSet; // Matriz de Adjacência; boost::dynamic_bitset
		
		int vertexNum; // Número de Vértices
		int edgeNum; // Número de Arestas
		int* vertexDegree; // Vetor de Grau de Vértices
		int* degrees; // Vetor Número de Vértices com grau x
		
		vector<bool> descobertos;
		vector<int> distancias;

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
			
			this->diametro = 0;

			return 0;
		}

//-------------------Lista de Adjacência---------------------------------------------------------------//
	
		void initAdjList(){
			this->AdjList = new LinkList* [vertexNum]();
			this->vertexDegree = new int [vertexNum]();
		}

		void addEdgeList(int v1, int v2, float w){
			LinkList* newItem1 = new LinkList();
			LinkList* newItem2 = new LinkList();
			
			newItem1->vertex = v2;
			newItem2->vertex = v1;

			newItem1->weight = w;
			newItem2->weight = w;
			
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

//-----------------Vetor de Adjacência-----------------------------------------------------------------//
		
		void initAdjVector(){
			this->AdjVector = new vector<VectorElem> [vertexNum];
		}

		void addEdgeVector(int v1, int v2, float w){
			VectorElem e1;
			VectorElem e2;

			int size1 = AdjVector[v1-1].size();
			int size2 = AdjVector[v2-1].size();

			e1.vertex = v1;
			e2.vertex = v2;

			e1.weight = w;
			e2.weight = w;

			this->AdjVector[v1-1].push_back(e2);
			this->AdjVector[v2-1].push_back(e1); 

			this->edgeNum++;

			this->degrees[size1]--;
			this->degrees[size1+1]++;
			this->degrees[size2]--;
			this->degrees[size2+1]++;
		}

//-------------------Matriz de Adjacência; vector<float>[]----------------------------------------------//
		
		void initAdjMatrix(){
			this->AdjMatrix = new vector<float> [vertexNum];
			for (int i = 0; i < vertexNum; i++){
				this->AdjMatrix[i].resize(vertexNum, false);
			}
			this->vertexDegree = new int [vertexNum] ();
		}

		void addEdgeMatrixBool(int v1, int v2, float w){
			this->AdjMatrix[v1-1][v2-1] = w;
			this->AdjMatrix[v2-1][v1-1] = w;

			this->edgeNum++;
			
			this->degrees[vertexDegree[v1-1]]--;
			this->degrees[vertexDegree[v1-1]+1]++;
			this->degrees[vertexDegree[v2-1]]--;
			this->degrees[vertexDegree[v2-1]+1]++;

			this->vertexDegree[v1-1]++;
			this->vertexDegree[v2-1]++;

		}
	
//-----------------Funções Adicionais-----------------------------------------------------------------//
	
		void componentRemover(){
			int index = this->componentes.size()-1;
			vector<int>::iterator inicio = this->componentes[index].begin();
			vector<int>::iterator fim = this->componentes[index].end();
			this->componentes[index-1].erase(inicio, fim);
			this->componentes.pop_back();
		}

		void printObj(FILE* file){
			fprintf(file, "# n = %d\n", vertexNum); // Printar número de vértices
			fprintf(file, "# m = %d\n", edgeNum); // Printar número de arestas
			fprintf(file, "# d_medio = %.10f\n", (float) (2*edgeNum)/vertexNum);
			int maior = 0;
			int c = 0;
			int menor = 0;
			for (int i = 0; i < vertexNum; i++){
				if (degrees[i] == 0) fprintf(file, "%d	%d\n", i, 0);
				else{
					if (c == 0){
						menor = i;
						c = 1;
					}
					fprintf(file, "%d	%.20f\n", i, (float) degrees[i]/vertexNum);	
					maior = i;
				}
			}
			fprintf(file, "\nMenor Grau: %d\n", menor);
			fprintf(file, "Maior Grau: %d", maior);	
		}
};