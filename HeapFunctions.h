#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void swap(vector<vector<int> >* v, int index1, int index2){
	vector<int> temp ((*v)[index1]);
	(*v)[index1] = (*v)[index2];
	(*v)[index2] = temp;
}

void heapifyBottomUp(vector<vector<int> >* comp, int i){
	int son = i;
	int father;
	if (son % 2 == 1) father = (son-1)/2;
	else father = (son-2)/2;

	if ((*comp)[son].size() > (*comp)[father].size()){
		swap(comp, father, son);
		heapifyBottomUp(comp, father);
	}
}

void heapifyTopDown(vector<vector<int> >* comp, int root){
	int largest = root;
	int leftSon = 2*root+1;
	int rightSon = 2*root+2;

	if (leftSon < comp->size() && (*comp)[leftSon].size() > (*comp)[largest].size()) largest = leftSon;
	if (rightSon < comp->size() && (*comp)[rightSon].size() > (*comp)[largest].size()) largest = rightSon;

	if (largest != root){
		swap(comp, largest, root);
		heapifyTopDown(comp, largest);
	}
}

void heapInsert(vector<vector<int> >* comp, vector<int> v){
	int index = comp->size();
	comp->push_back(v);
	if (index != 0) heapifyBottomUp(comp, index);
}

void heapRemove(Graph* grafo, vector<int>* swapper){
	int index = grafo->componentes.size()-1;
	if (index < 0) return;

	grafo->componentes[0].swap(*swapper);
	swap((&grafo->componentes), 0, index);
	grafo->componentRemover();
	heapifyTopDown((&grafo->componentes), 0);
}
