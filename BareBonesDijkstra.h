void reversePrint(FILE* file, int* array, int a){
	if (a == 0)	return;
	reversePrint(file, array, array[a]);
	fprintf(file, "%d, ", a);
}

float dijkstra(WeightGraph* grafo, FILE* file, int raiz, bool avg, int min){

	vector<float> dist;
	vector<int> pos;
	vector<int> heap;
	
	// 3 vetores de tamanho (N+1);
	
	//vector<int> componentes;
	int comp = 0;

	dist.push_back(-1);
	pos.push_back(-1);

	for (int i = 1; i <= grafo->vertexNum; i++){
		dist.push_back(inf);
		heap.push_back(i);
		pos.push_back(i-1);
	}

	//grafo->pai[raiz] = 0;
	dist[raiz] = 0.0;
	intSwap(&heap, raiz-1, 0);
	intSwap(&pos, raiz, 1);
	//grafo->descobertos[raiz-1] = 1;
	comp++;

	while (!heap.empty()){ // usar "&& dist[heap[0]] != inf para calcular apenas uma dijkstra para um componente"
		int x = heap[0];

		if (dist[x] == inf){
			
			if (avg) break;

			dist[x] = 0.0;
			//grafo->pai[x] = 0;
			//grafo->descobertos[x-1] = 1;
			comp++;
		}

		//if (avg && grafo->descobertos[x-1] == 0) componentes.push_back(x);
		intHeapRemove(&heap, &dist, &pos);

		if (grafo->representation == LINK_LIST){
			LinkList* p = new LinkList();
			p = grafo->AdjList[x-1];
			while (p){
				int son = p->vertex;
				float weight = p->weight;

				if (dist[son] > dist[x] + weight){
					//grafo->pai[son] = x;
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
					//grafo->pai[son] = x;
					dist[son] = dist[x] + weight;
					intHeapifyBottomUp(&heap, &dist, &pos, pos[son]);
				}
			}
		}

		if (grafo->representation == MATRIX){
			for (int i = 0; i < grafo->vertexNum; i++){
				if (dist[i+1] > dist[x] + grafo->AdjMatrix[x-1][i]){
					//grafo->pai[i+1] = x;
					dist[i+1] = dist[x] + grafo->AdjMatrix[x-1][i];
					intHeapifyBottomUp(&heap, &dist, &pos, pos[i+1]);
				}
			}
		}
	}
/*
	if (avg){
		float sum = 0.0;
		for (int j = 0; j < componentes.size(); j++){
			if (grafo->descobertos[componentes[j]-1] == 0) sum += dist[componentes[j]];
		}
		float vNum = (float) grafo->vertexNum;
		float total = (vNum*(vNum-1))/2;
		return sum/total;
	}

	else{	
		if (min != 0){
			if (dist[min] == inf) fprintf(file, "# %d:	Distância = infinita;	Não existe caminho mínimo entre %d e %d\n", min, raiz, min);
			else{
				fprintf(file, "# %d:	Distância = %.10f;	Caminho Mínimo = ", min, dist[min]);
				fprintf(file, "[");
				reversePrint(file, grafo->pai, grafo->pai[min]);
				fprintf(file, "%d]\n", min);		
			}
		}

		else{
			fprintf(file, "Número de componentes:	%d\n\n", comp);
			for (int j = 1; j <= grafo->vertexNum; j++){
				if (dist[j] == inf) fprintf(file, "# %d:	Distância = infinita;	Não existe caminho mínimo entre %d e %d\n", j, raiz, j);
				else{
					fprintf(file, "# %d:	Distância = %.10f;	Caminho Mínimo = ", j, dist[j]);
					fprintf(file, "[");
					reversePrint(file, grafo->pai, grafo->pai[j]);
					fprintf(file, "%d]\n", j);
				}
			}	
		}
		return 0.0;
	}
}*/


void avgDistance(WeightGraph* grafo, FILE* file){
	double mean = 0.0;
	
	for (int i = 1; i < grafo->vertexNum; i++) mean += (double) dijkstra(grafo, file, i, true, 0);
	
	printf("\nAverage Distance: %.10f\n\n", mean);
	fprintf(file, "Distância Média:	%.10f\n", mean);
}