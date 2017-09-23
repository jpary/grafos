#define INF -1;

void dijkstra(Graph* grafo, FILE* file, int raiz){
	vector<int> dist = new vector<int> ();
	vector<int> pos = new vector<int> ();
	vector<int> heap = new vector<int> ();

	for (int i = 0; i < grafo->vertexNum; i++){
		dist[i] = INF;
		heap.push_back(i+1);
		pos.push_back(i);
	}

	dist[raiz-1] = 0.0;
	grafo->pai[raiz] = 0;
	grafo->nivel[raiz] = 0;
	swap(&heap, raiz-1, 0);
	swap(&pos, raiz-1, 0);

	if (!heap.empty()){
		int x = heap[0];
		if (dist[x-1] == INF){
			dist[x-1] = 0.0;
			grafo->pai[x] = 0;
			grafo->nivel[x] = 0;
		}
		heapRemove(&heap, &dist, &pos);

		if (grafo->representation == LINK_LIST){
			LinkList* p = new LinkList();
			p = grafo->AdjList[x-1];
			while (p){
				int son = p->vertex;
				float weight = p->weight;

				if (dist[son-1] == INF || dist[son-1] > dist[x-1] + weight){
					grafo->pai[son] = x;
					grafo->nivel[son] = grafo->nivel[x]+1;
					dist[son-1] = dist[x-1] + weight;
					heapifyBottomUp(&heap, &distance, pos[son-1])
				}
				p = p->nextVertex;
			}
		}

		if (grafo->representation == VECTOR){
			for (int i = grafo->AdjVector[x-1].size()-1; i >= 0; i--){
				
				int son = grafo->AdjVector[x-1][i].vertex;
				int weight = grafo->AdjVector[x-1][i].weight;
				
				if (dist[son-1] == INF || dist[son-1] > dist[x-1] + weight){
					grafo->pai[son] = x;
					grafo->nivel[son] = grafo->nivel[x]+1;
					dist[son-1] = dist[x-1] + weight;
					heapifyBottomUp(&heap, &distance, pos[son-1])
				}
			}
		}

		if (grafo->representation == MATRIX){
			for (int i = 0; i < grafo->vertexNum; i++){
				
				if (grafo->AdjMatrixBool[x-1][i] == 1 && (dist[i] == INF || dist[i] > dist[x-1] + weight)){
					grafo->pai[i+1] = x;
					grafo->nivel[i+1] = grafo->nivel[x]+1;
					dist[i] = dist[x-1] + weight;
					heapifyBottomUp(&heap, &distance, pos[i])
				}
			}
		}

	}
}
