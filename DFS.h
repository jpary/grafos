#include <stack>

void DFS(Graph* grafo, int *raiz, int *size, FILE* file, int* number, int d){

	if (d == 0) grafo->descobertos.assign(grafo->vertexNum, 0);

	stack<int> pilha;
	vector<int> vetor;

	int level = 0;
	int father = 0;

	pilha.push(*raiz);
	int x;

	while (!pilha.empty()){
		x = pilha.top();

		grafo->pai[x] = father;
		grafo->nivel[x] = level;
		grafo->descobertos[x-1] = 1;
		vetor.push_back(x);

		if (grafo->representation == LINK_LIST){
			LinkList* p = grafo->AdjList[x-1];
			while (p){
				int son = p->vertex;
				if (grafo->descobertos[son-1] == 0)	pilha.push(son);
				p = p->nextVertex;
			}
		}

		if (grafo->representation == VECTOR){
			for (int i = grafo->AdjVector[x-1].size()-1; i >= 0; i--){
				int son = grafo->AdjVector[x-1][i];
				if (grafo->descobertos[son-1] == 0)	pilha.push(son);
			}
		}

		if (grafo->representation == BOOL_MATRIX){
			for (int i = grafo->vertexNum-1; i >= 0; i--){
				if (grafo->descobertos[i] == 0 && grafo->AdjMatrixBool[x-1][i] == 1) pilha.push(i+1);
			}
		}

		father = x;
		level++;
		while (pilha.size() > 0 && grafo->descobertos[pilha.top()-1] == 1){
			if (grafo->explorados[pilha.top()-1] == 0){
				level--;
				father = grafo->pai[father];
				grafo->explorados[pilha.top()-1] = 1;
				}
			pilha.pop();
		}
	}

	if (d == 1){
		int steps = vetor.size();
		heapInsert(&(grafo->componentes), vetor);
		
		if (steps <= *size){
			while (grafo->componentes.size() > 0 && grafo->componentes[0].size() > (*size)-steps){
				
				vector<int> biggest;
				heapRemove(grafo, (&biggest));
				printf("Swapped.\n");
				
				file = fopen("components.txt", "a");
				fprintf(file, "Componente Conexo #%d; Qtd. de Vértices: %d\n[", *number, (int) biggest.size());
				
				(*number)++;
				int i = 0;
				
				for (; i < biggest.size()-1; i++) fprintf(file, "%d, ", biggest[i]);
				fprintf(file, "%d]\n\n", biggest[i]);
				
				fclose(file);
				printf("Cleared memory.\n");
			}
			if (steps == *size) (*number)--;
			*size -= steps;
			int i = 0;
			while (grafo->descobertos[i] & 1) i++;
			*raiz = i+1;
			return;
		}
	}
	if (d == 0){
		file = fopen("components.txt", "a");
		fprintf(file, "Componente Conexo #%d; Qtd. de Vértices: %d\n[", *number, (int) vetor.size());
		int i = 0;
				
		for (; i < vetor.size()-1; i++) fprintf(file, "%d, ", vetor[i]);
		fprintf(file, "%d]\n\n", vetor[i]);
				
		fclose(file);
	}
}
