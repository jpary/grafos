#include <stack>

void iterDFS(Graph* grafo, int raiz, int size){
	stack<int>* pilha;
	pilha = new stack<int>;
	int index = grafo->componentes.size()-1;
	printf("%d\n", index);

	int level = 0;
	int father = 0;

	pilha->push(raiz);
	int x;
	printf("Finished initializing.\n");

	while (pilha->size() > 0){
		x = pilha->top();
		printf("%d\n", x);
		grafo->pai[x] = father;
		grafo->nivel[x] = level;
		grafo->descobertos[x-1] = 1;
		grafo->componentes[index].push_back(x);
		
		if (grafo->representation == LINK_LIST){
			LinkList* p = grafo->AdjList[x-1];
			while (p){
				printf("%d\n", p->vertex);
				if (grafo->descobertos[(p->vertex)-1] == 0){
					pilha->push(p->vertex);
					p = p->nextVertex;
					printf("%d\n", p->vertex);
					printf("Pushing.\n");
				}
			}
		}

		if (grafo->representation == VECTOR){
			for (int i = 0; i < grafo->AdjVector[x-1].size(); i++){
				if (grafo->descobertos[i-1] == 0) pilha->push(grafo->AdjVector[x-1][i]);
				printf("Pushing.\n");
			}
		}

		if (grafo->representation == BOOL_MATRIX){
			for (int i = 0; i < grafo->vertexNum; i++){
				if (grafo->AdjMatrixBool[x-1][i-1] == 1 && grafo->descobertos[i-1] == 0) pilha->push(i);
				printf("Pushing.\n");
			}
		}

		father = x;
		level++;
		while (pilha->size() > 0 && grafo->descobertos[pilha->top()-1] == 1){
			if (grafo->explorados[pilha->top()-1] == 0){
				level--;
				father = grafo->pai[father];
				grafo->explorados[pilha->top()-1] = 1;
				}
			pilha->pop();
			printf("Popping.\n");
		}
	}

	int steps = grafo->componentes[index].size();
	printf("%d\n", steps);

	if (steps < size){
		int i = 0;
		while (grafo->descobertos[i-1] != 0){
			i++;
			printf("%d\n", i);
		}
		vector<int> y;
		grafo->componentes.push_back(y);
		
		printf("Next Phase.\n");

		iterDFS(grafo, i, size-steps);
	}
}

void recDFS(Graph* grafo, int vertice, int father, int level){
	int index = grafo->componentes.size()-1;

	grafo->pai[vertice] = father;
	grafo->nivel[vertice] = level;
	grafo->descobertos[vertice-1] = 1;

	if (grafo->representation == LINK_LIST){
		LinkList* p = grafo->AdjList[vertice-1];
		while (!p){
			if (grafo->descobertos[(p->vertex)-1] == 0){
				recDFS(grafo, p->vertex, vertice, level+1);
				p = p->nextVertex;
			}
		}
	}

	if (grafo->representation == VECTOR){
		for (int i = 0; i < grafo->AdjVector[vertice-1].size(); i++){
			if (grafo->descobertos[i-1] == 0) recDFS(grafo, grafo->AdjVector[vertice-1][i], vertice, level+1);
		}
	}

	if (grafo->representation == BOOL_MATRIX){
		for (int i = 0; i < grafo->vertexNum; i++){
			if (grafo->AdjMatrixBool[vertice-1][i-1] == 1 && grafo->descobertos[i-1] == 0) recDFS(grafo, i, vertice, level+1);
		}
	}

}

void callRecDFS(Graph* grafo, int vertice){
	recDFS(grafo, vertice, 0, 0);
}
