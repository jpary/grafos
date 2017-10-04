void prim(WeightGraph* grafo, FILE* file, int raiz){
	
	fprintf(file, "Número de Vértices:	%d\n\n", grafo->vertexNum);

	vector<float> cost;
	vector<int> pos;
	vector<int> heap;
	int componentes = 0;
	float totalWeight = 0;

	// 3 vetores de tamanho (N+1);

	cost.push_back(-1);
	pos.push_back(-1);

	for (int i = 1; i <= grafo->vertexNum; i++){
		cost.push_back(inf);
		heap.push_back(i);
		pos.push_back(i-1);
	}

	cost[raiz] = 0.0;
	grafo->pai[raiz] = 0;
	intSwap(&heap, raiz-1, 0);
	intSwap(&pos, raiz, 1);
	componentes++;

	while (!heap.empty()){ // usar "&& cost[heap[0]] != inf para calcular apenas uma dijkstra para um componente"
		int x = heap[0];

		if (cost[x] == inf){
			cost[x] = 0.0;
			grafo->pai[x] = 0;
			componentes++;
		}

		intHeapRemove(&heap, &cost, &pos);
		if (grafo->pai[x] != 0) fprintf(file, "%d	%d	%f\n", x, grafo->pai[x], cost[x]);
		totalWeight += cost[x];

		if (grafo->representation == LINK_LIST){
			LinkList* p = new LinkList();
			p = grafo->AdjList[x-1];
			while (p){
				int son = p->vertex;
				float weight = p->weight;

				if (cost[son] > weight){
					grafo->pai[son] = x;
					cost[son] = weight;
					intHeapifyBottomUp(&heap, &cost, &pos, pos[son]);
				}
				p = p->nextVertex;
			}
		}

		if (grafo->representation == VECTOR){
			for (int i = grafo->AdjVector[x-1].size()-1; i >= 0; i--){
				
				int son = grafo->AdjVector[x-1][i].vertex;
				int weight = grafo->AdjVector[x-1][i].weight;
				
				if (cost[son] > weight){
					grafo->pai[son] = x;
					cost[son] = weight;
					intHeapifyBottomUp(&heap, &cost, &pos, pos[son]);
				}
			}
		}

		if (grafo->representation == MATRIX){
			for (int i = 0; i < grafo->vertexNum; i++){
				
				if (cost[i+1] > cost[x] + grafo->AdjMatrix[x-1][i]){
					grafo->pai[i+1] = x;
					cost[i+1] = grafo->AdjMatrix[x-1][i];
					intHeapifyBottomUp(&heap, &cost, &pos, pos[i+1]);
				}
			}
		}
	}

	fprintf(file, "\nPeso Total:	%f\n", totalWeight);
}
