#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void swap(vector<int>* vec, int index1, int index2){
	int temp = (*vec)[index1];
	(*vec)[index1] = (*vec)[index2];
	(*vec)[index2] = temp;
}

void heapifyBottomUp(vector<int>* heap, vector<int>* dist, vector<int>* pos, int son){
	int father;
	if (son % 2 == 1) father = (son-1)/2;
	else father = (son-2)/2;

	if (dist[(*heap)[son]-1] != INF && dist[(*heap)[son]-1] < dist[(*heap)[father]-1]){
		swap(heap, father, son);
		swap(pos, (*heap)[father], (*heap)[son]);
		heapifyBottomUp(heap, dist, pos, father);
	}
}

void heapifyTopDown(vector<int>* heap, vector<int>* dist, vector<int>* pos, int root){
	int smallest = root;
	int leftSon = 2*root+1;
	int rightSon = 2*root+2;

	if (leftSon < heap->size() && dist[(*heap)[leftSon]-1] != INF && dist[(*heap)[leftSon]-1] < dist[(*heap)[smallest]-1]) smallest = leftSon;
	if (rightSon < heap->size() && dist[(*heap)[rightSon]-1] != INF && dist[(*heap)[rightSon]-1] < dist[(*heap)[smallest]-1]) smallest = rightSon;

	if (smallest != root){
		swap(heap, smallest, root);
		swap(pos, (*heap)[smallest], (*heap)[root])
		heapifyTopDown(heap, dist, pos, smallest);
	}
}

void heapInsert(vector<int>* heap, vector<int>* dist, vector<int>* pos, int vertex){
	int index = heap->size();
	heap->push_back(vertex);
	pos->push_back(vertex);
	if (index != 0) heapifyBottomUp(heap, dist, pos, index);
}

void heapRemove(vector<int>* heap, vector<int>* dist, vector<int>* pos){
	int index = grafo->componentes.size()-1;
	if (index < 0) return;
	vector<int> temp = new vector<int> ();

	swap(heap, index, 0);
	swap(pos, (*heap)[index], (*heap)[0]);
	heap->swap(temp);
	temp.pop_back();
	temp.swap(*heap);

	heapifyTopDown(heap, dist, pos, 0);
}
