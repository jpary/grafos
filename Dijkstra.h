void dijkstra(WeightGraph* grafo, FILE* file, int raiz){
	
	vector<float> dist;
	vector<int> pos;
	vector<int> heap;
	int componentes = 0;

	// 3 vetores de tamanho (N+1);

	dist.push_back(-1);
	pos.push_back(-1);

	for (int i = 1; i <= grafo->vertexNum; i++){
		dist.push_back(inf);
		heap.push_back(i);
		pos.push_back(i-1);
	}

	grafo->pai[raiz] = 0;
	grafo->nivel[raiz] = 0;
	dist[raiz] = 0.0;
	intSwap(&heap, raiz-1, 0);
	intSwap(&pos, raiz, 1);
	componentes++;

	while (!heap.empty()){ // usar "&& dist[heap[0]] != inf para calcular apenas uma dijkstra para um componente"
		int x = heap[0];

		if (dist[x] == inf){
			dist[x] = 0.0;
			grafo->pai[x] = 0;
			grafo->nivel[x] = 0;
			componentes++;
		}

		intHeapRemove(&heap, &dist, &pos);

		if (grafo->representation == LINK_LIST){
			LinkList* p = new LinkList();
			p = grafo->AdjList[x-1];
			while (p){
				int son = p->vertex;
				float weight = p->weight;

				if (dist[son] > dist[x] + weight){
					grafo->pai[son] = x;
					grafo->nivel[son] = grafo->nivel[x]+1;
					dist[son] = dist[x] + weight;
					intHeapifyBottomUp(&heap, &dist, &pos, pos[son]);
				}
				p = p->nextVertex;
			}
		}

		if (grafo->representation == VECTOR){
			for (int i = grafo->AdjVector[x-1].size()-1; i >= 0; i--){
				
				int son = grafo->AdjVector[x-1][i].vertex;
				int weight = grafo->AdjVector[x-1][i].weight;
				
				if (dist[son] > dist[x] + weight){
					grafo->pai[son] = x;
					grafo->nivel[son] = grafo->nivel[x]+1;
					dist[son] = dist[x] + weight;
					intHeapifyBottomUp(&heap, &dist, &pos, pos[son]);
				}
			}
		}

		if (grafo->representation == MATRIX){
			for (int i = 0; i < grafo->vertexNum; i++){
				
				if (dist[i+1] > dist[x] + grafo->AdjMatrix[x-1][i]){
					grafo->pai[i+1] = x;
					grafo->nivel[i+1] = grafo->nivel[x]+1;
					dist[i+1] > dist[x] + grafo->AdjMatrix[x-1][i];
					intHeapifyBottomUp(&heap, &dist, &pos, pos[i+1]);
				}
			}
		}
	}

	grafo->descobertos[raiz-1] = 1;
	float sum = 0.0;
	fprintf(file, "Número de componentes:	%d\n\n", componentes);
	for (int j = 1; j <= grafo->vertexNum; j++){
		if (grafo->descobertos[j-1] == 0) sum += dist[j];
		if (sum < 0) printf("hey\n");
		if (dist[j] == inf) fprintf(file, "# %d:	Pai = -1;	Nivel = -1;	Distância = inf;\n", j);
		else fprintf(file, "# %d:	Pai = %d;	Nivel = %d;	Distância = %.8f;\n", j, grafo->pai[j], grafo->nivel[j], dist[j]);
	}
	float total = (grafo->vertexNum*(grafo->vertexNum-1))/2;
	fprintf(file, "\nDistância Média = %.10f", sum/total);
}

// Código para fazer:

void meanDistance(WeightGraph* grafo, FILE* file){
	for (int i = 1; i <= grafo->vertexNum; i++){
	}
}
