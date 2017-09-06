#include <iostream>
#include <bitset>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

using namespace std;

typedef struct a{
	int vertex;
	struct a* nextVertex;
} LinkList;

/*Vector already has a library, so no need to
  create another type specifically for that*/ 

class Graph{

	LinkList** AdjList; // Adjacency Linked List
	vector<int>* AdjVector; // Adjacency Vector
	vector<bool>* AdjMatrix;
	vector<bool> Rows;
	int vertexNum;
	int edgeNum;
	int* vertexDegree;
	int* degrees;

	public:
	
		int initAdjList(int size){
			if (size <= 0) return 1;
			edgeNum = 0; 
			AdjList = new LinkList* [size];
			vertexNum = size;
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

//-----------------------------------------------------------------------------------------------------//
		
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

			AdjVector[v1-1].push_back(v2);
			AdjVector[v2-1].push_back(v1);

			edgeNum++;

			degrees[size1]--;
			degrees[size1+1]++;
			degrees[size2]--;
			degrees[size2+1]++;
		}

//-----------------------------------------------------------------------------------------------------//
		
		int initAdjMatrix(int size){
			if (size <= 0) return 1;
			edgeNum = 0;
			vertexNum = size;
			printf("1\n");
			AdjMatrix = new vector<bool> [size];
			printf("2\n");
			for (int i = 0; i < size; i++){
				AdjMatrix[i].resize(size, false);
			}
			printf("3\n");
			vertexDegree = new int [size] ();
			degrees = new int [size] ();
			degrees[0] = vertexNum;
			return 0;	
		}

		void addEdgeMatrix(int v1, int v2){
			AdjMatrix[v1-1][v2-1] = 1;
			AdjMatrix[v2-1][v1-1] = 1;

			edgeNum++;
			
			degrees[vertexDegree[v1-1]]--;
			degrees[vertexDegree[v1-1]+1]++;
			degrees[vertexDegree[v2-1]]--;
			degrees[vertexDegree[v2-1]+1]++;

			vertexDegree[v1-1]++;
			vertexDegree[v2-1]++;
		}

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
	Graph G;
	FILE* in;
	FILE* out;
	int a;	
	cin >> a;
	in = fopen("subdblp.txt", "r");
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
			int x = G.initAdjMatrix(n);
			printf("Finished initializing.\n");
			if (x == 1) fprintf(out, "Couldn't create graph.\n");
			else{
				int a, b;
				while (fscanf(in, "%d %d", &a, &b) == 2){
					G.addEdgeMatrix(a, b);
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