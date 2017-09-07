#include <stack>

void iterDFS(Graph grafo, int raiz){
	stack<int> pilha;
	vector<bool> marcados (grafo.vertexNum, false);
	vector<bool> explorados (grafo.vertexNum, false);

	int level = 0;
	int father = 0;

	grafo.pai[raiz] = father;
	grafo.nivel[raiz] = level;
	pilha.push(raiz);

	while (pilha.size() > 0){
		int x = pilha.top();
		
		if (grafo.representation == LINK_LIST){
			LinkList* p = grafo.AdjList[x];
			while (!p){
				if (marcados[p->vertex] == 0){
					pilha.push(p->vertex);
					p = p->nextVertex;
				}
			}
		}
		
		grafo.pai[pilha.top()] = x;
		grafo.nivel[pilha.top()] = ++level;
		while (pilha.size() > 0 && marcados[pilha.top()] == 1){
			if (explorados[pilha.top()] == 0){
				level--;
				father = grafo.pai[father];
				}
			pilha.pop();
		}
	}
}