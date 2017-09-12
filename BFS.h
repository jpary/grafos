#include <queue>

int BFS(Graph* grafo, int* raiz, int* size, FILE* file, int* number, int d, int diam){

	if (d == 0) grafo->descobertos.assign(grafo->vertexNum, 0);

	queue<int> fila;
	vector<int> vetor;

	int level = 0;

	grafo->pai[*raiz] = 0;
	grafo->nivel[*raiz] = 0;
	grafo->descobertos[(*raiz)-1] = 1;
	vetor.push_back(*raiz);

	fila.push(*raiz);
	int x;

	while (!fila.empty()){
		x = fila.front();
		fila.pop();

		if (grafo->representation == LINK_LIST){
			LinkList* p = new LinkList();
			p = grafo->AdjList[x-1];
			while (p){
				
				int son = p->vertex;

				if (grafo->descobertos[son-1] == 0){
					grafo->pai[son] = x;
					grafo->nivel[son] = grafo->nivel[x]+1;
					grafo->descobertos[son-1] = 1;
					vetor.push_back(son);
					fila.push(son);
				}
				p = p->nextVertex;
			}
		}

		if (grafo->representation == VECTOR){
			for (int i = grafo->AdjVector[x-1].size()-1; i >= 0; i--){
				
				int son = grafo->AdjVector[x-1][i];
				
				if (grafo->descobertos[son-1] == 0){
					grafo->pai[son] = x;
					grafo->nivel[son] = grafo->nivel[x]+1;
					grafo->descobertos[son-1] = 1;
					vetor.push_back(son);		
					fila.push(son);
				}
			}
		}

		if (grafo->representation == BOOL_MATRIX){
			for (int i = 0; i < grafo->vertexNum; i++){
				
				if (grafo->descobertos[i] == 0 && grafo->AdjMatrixBool[x-1][i] == 1){
					grafo->pai[i+1] = x;
					grafo->nivel[i+1] = grafo->nivel[x]+1;
					grafo->descobertos[i] = 1;
					vetor.push_back(i+1);
					fila.push(i+1);
				}
			}
		}
	
		level = grafo->nivel[x];
	
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
			return 0;
		}
	}
	if (d == 0){
		if (diam == 0){	
			file = fopen("components.txt", "a");
			fprintf(file, "Componente Conexo #%d; Qtd. de Vértices: %d\n[", *number, (int) vetor.size());
			
			int i = 0;
			for (; i < vetor.size()-1; i++) fprintf(file, "%d, ", vetor[i]);
			fprintf(file, "%d]\n\n", vetor[i]);
						
			fclose(file);
		}
		return level;
	}
}

void diameter(Graph* grafo, int size, FILE* file, int* number){
	int level = 0;
	for (int i = 1; i <= size; i++){
		level = BFS(grafo, &i, &size, file, number, 0, 1);
		printf("%d\n", i);
		if (grafo->diametro < level) grafo->diametro = level;
		printf("%d\n", grafo->diametro);
	}
	printf("%d\n", grafo->diametro);
}
