//=================================================================================================================
// Bibliotecas:

#include <vector>
#include <queue>

//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------

//=================================================================================================================
// Variáveis:
#define GRAFO Graph
#define VERTICE Vertex
#define NUMERO_DE_VERTICES numVertex
#define VECTOR_BOOL_VISITADOS visitados

//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------

//=================================================================================================================
// TODO:
// -> Estrutura de marcação de vértices.	======> BITSET PARA OS VÉRTICES MARCADOS!!!!
// -> função marcar vértice. 				======> BITSET.set(i)
// -> função desmarcar vértice.				======> BITSET.reset(i)
// ->
//=================================================================================================================

// bitset::test(pos) => retorna true if bit at position pos




int breadth_first_search(GRAFO, VERTICE){
	G.VECTOR_BOOL_VISITADOS.reset();					// Desmarca todos os vertices de G ======> VECTOR_BOOL_VISITADOS.reset();
	std::queue<int> Q;									// Inicializa a lista Q vazia
														// Marca s
	Q.push(s);											// Inserir s em Q
	while (Q.empty){									// Inicio do loop. Só para quando Q for vazia
		Q.pop();
		for (i = 0; i <= VECTOR_BOOL_VISITADOS.size(); i++){
			if (VECTOR_BOOL_VISITADOS[i] == 1){
				if (VECTOR_BOOL_VISITADOS[i].marked() == false){
					VECTOR_BOOL_VISITADOS[i] = 1; // mark(bitset[i]);
					Q.push(i);
				}
			}
		}
	}


}