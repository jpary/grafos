Grafo.cpp
DETALHES
ATIVIDADE
Grafo.cpp
Informações de compartilhamento

A
Informações gerais
Tipo
C++
Tamanho
7 KB (7.201 bytes)
Armazenamento usado
0 bytesDe propriedade de outra pessoa
Local
Código Limpo
Proprietário
Lucas Santos de Paula
Modificado
em 15 de dez de 2015 por Lucas Santos de Paula
Aberto
em 10:18 por mim
Criado em
15 de dez de 2015
Descrição
Adicionar uma descrição
Permissões de download
Os leitores podem fazer o download
Todas as seleções foram removidas

#include <iostream>
#include <cstring>
#include <fstream>
#include <list>
#include <queue>
#include <stack>
#include <time.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <stdio.h>
using namespace std;
struct adjList {
    list<int> vizinho;
    int pai;
    int nivel;
};

class Grafo {
private:
    int tipo;
    bool *marcados;
    int vertices, arestas;
    bool **matrizAdj;
    int *grau;
    int *nivel;
    int *pai;
    char *arqvtxt;
    int diametro; ////
    int para;     ////
    int parb;     ////Variáveis utilizadas 
    int aux;      ////
    int auxb;     //////////
    struct adjList *listaAdj;

    void iniciaMatriz(){
	ifstream myfile(arqvtxt);
	int n;
        myfile>>n;
	vertices = n;
	marcados=new bool[this->vertices];
	grau = new int[vertices];
	pai = new int[vertices];
	nivel = new int[vertices];
	matrizAdj = new bool*[vertices];
            for(int i=0; i<vertices;i++) {
                matrizAdj[i] = new bool[vertices];
		grau[i]=0;
		pai[i]=0;
		nivel[i]=0;
                memset(matrizAdj[i],0,sizeof(bool)*vertices);
            };
	int auxa;
        int auxb;
        
	
        while (myfile.good()){
            myfile>>auxa;
            myfile>>auxb;
	    grau[auxa-1]++;
	    grau[auxb-1]++;
	    this->matrizAdj[auxa-1][auxb-1] = true;
            this->matrizAdj[auxb-1][auxa-1] = true;
	}
	myfile.close();
	getchar();
    }
    
    void iniciaLista(){
	ifstream myfile(arqvtxt);
        int n;
	
        if (myfile.good()){
            myfile>>n;   
            grau = new int[n];
            this->vertices=n;
            
            listaAdj = new adjList[n];
            marcados=new bool[this->vertices];
        }
	 while (myfile.good()){
	    int auxa;
	    int auxb;
            myfile>>auxa;
            myfile>>auxb;
            arestas++;
            
            this->listaAdj[auxa-1].vizinho.push_back(auxb);
            grau[auxa-1]++;
            this->listaAdj[auxb-1].vizinho.push_back(auxa);
            grau[auxb-1]++;
        }
        myfile.close();
	for (int i=0; i<n; i++){
		this->listaAdj[i].vizinho.sort();
	}
     }

   void nBFS(int v) {
        queue<int> fila;	
	aux=v;
        int w;
	int x = v-1;
        memset(this->marcados,0,sizeof(bool)*this->vertices);
        this->marcados[v-1]=1;
        fila.push(v-1);
        while(!fila.empty()) {
            w=fila.front();
            fila.pop();
	    if (tipo==1){
		listaAdj[v-1].pai = 0;
		listaAdj[v-1].nivel = 0;
            	for(list<int>::iterator i = listaAdj[w].vizinho.begin(); i != listaAdj[w].vizinho.end(); i++) {
                	if(this->marcados[*i-1]==0) {
                	    fila.push(*i-1);
                	    this->marcados[*i-1] = 1;
			    listaAdj[*i-1].pai = w+1;
			    listaAdj[*i-1].nivel = listaAdj[w].nivel+1;
			    if (listaAdj[*i-1].nivel>diametro){ diametro = listaAdj[*i-1].nivel; para = aux; parb = *i;} 
                	}
           	 }
	    }		

	    if (tipo==0){
		this->pai[v-1] = 0;
		this->nivel[v-1] = 0;
	    	for(int i=0; i<vertices; i++){
			if(matrizAdj[w][i]==1 and marcados[i] == 0 and marcados[w] == 1){
				fila.push(i);
				marcados[i]=1;
				pai[i]=w+1;
				nivel[i]=nivel[w]+1;
				if (nivel[i]>diametro){ diametro = nivel[i]; para = aux; parb = i+1;}
			}	
            	 }
	    }
        }
    };

    void nDFS(int v) {
	stack<int> pilha;
        int w;
	int x = v-1;
        memset(this->marcados,0,sizeof(bool)*this->vertices);
        pilha.push(v-1);
        while(!pilha.empty()) {
            w=pilha.top();
            pilha.pop();
	    if (tipo==1){
	    	listaAdj[v-1].pai = 0;
		listaAdj[v-1].nivel = 0;
	    	if(marcados[w]==0){
	    		marcados[w]=1;
			for(list<int>::iterator i = listaAdj[w].vizinho.begin(); i != listaAdj[w].vizinho.end(); i++) {
                		if(this->marcados[*i-1]==0) {
                		    pilha.push(*i-1);
				    listaAdj[*i-1].pai = w+1;
				    listaAdj[*i-1].nivel = listaAdj[w].nivel+1;
                		}
           	 	}	
	    	}
		}
	    if (tipo==0){
		this->pai[v-1] = 0;
		this->nivel[v-1] = 0;
		if(marcados[w]==0){
			marcados[w]=1;
			for(int i=0; i<vertices; i++){
				if(matrizAdj[w][i]==1 and marcados[i] == 0){
					pilha.push(i);
					pai[i]=w+1;
					nivel[i]=nivel[w]+1;
				}	
            	 	}
		}
	    	
	    }
        }

    };

public:
	static bool maior_tamanho(const list<int>& a,const list<int>& b) {
	   return a.size() > b.size();
	}
    Grafo(char *txt, int i) {
	//////tipo = 1 -> lista
	//////tipo = 0 -> matriz
	tipo = i;
	arqvtxt = txt;
	diametro = 0;
        if (tipo==1) iniciaLista();
        if (tipo==0) iniciaMatriz();
    };

    ~Grafo(){
    	for (int i=0; i<vertices; i++){
    		delete matrizAdj[i];
    		
    	}
        //delete matrizAdj;
        delete listaAdj;
        delete marcados;
        delete grau;
	delete pai;
	delete nivel;
    };

    void BFS(int v) {
	ofstream txt("BFS.txt");
	nBFS(v);
    	for(int i = 0; i<vertices; i++){
    		if(marcados[i]==1){
    			if(tipo==1){
    				txt<<"Vértice: "<<i+1<<", pai: "<<listaAdj[i].pai<<", nível: "<<listaAdj[i].nivel<<"\r\n";
    			}
			if(tipo==0){
				txt<<"Vértice: "<<i+1<<", pai: "<<pai[i]<<", nível: "<<nivel[i]<<"\r\n";
			}
    			
    		}
    	}
	txt.close();
    }

    void DFS (int v){
	ofstream txt("DFS.txt");
    	nDFS(v);
	for(int i = 0; i<vertices; i++){
    		if(marcados[i]==1){
    			if(tipo==1){
    				txt<<"Vértice: "<<i+1<<", pai: "<<listaAdj[i].pai<<", nível: "<<listaAdj[i].nivel<<"\r\n";
    			}
			if(tipo==0){
				txt<<"Vértice: "<<i+1<<", pai: "<<pai[i]<<", nível: "<<nivel[i]<<"\r\n";
			}
    			
    		}
    	}
	txt.close();
    }

    void Saida(){
        ofstream txt("saida.txt");
        txt<<"# n = "<<vertices<<"\r\n";
        txt<<"# m = "<<arestas<<"\r\n";
        txt<<"# d_medio = "<<(2.0*arestas)/vertices<<"\r\n";
        for (int i = 0; i<vertices; i++){
            txt<<i+1<<" "<<grau[i]*1.0/vertices<<"\r\n";
        }
        txt.close();
    };

	void Diametro(){
		for (int i=0; i<vertices; i++){
			nBFS(i+1);
		}
		cout<<para<<" "<<parb<<" "<<diametro<<endl;
	}

	void Conexos(){
		ofstream txt("componentes.txt");
		memset(this->marcados,0,sizeof(bool)*this->vertices);
		int vinicio=1;
		int explorados[vertices];
		list< list<int> > componentes;
		for(int i = 0; i<vertices; i++){
			explorados[i] = 0;
		}
		int aux;
		int fim=0;
		int comcon = 0;
		while (vinicio!=-1){
			nBFS(vinicio);
			list<int> lista;
			for (int i=0; i<vertices; i++){
				if(marcados[i]==1){
					lista.push_back(i+1);
					explorados[i]=1;
					fim++;
				}
				if(explorados[i]==0){
					aux = i+1;
				}	
			}
			vinicio=aux;
			if(fim==vertices){
				vinicio=-1;
			}
			componentes.push_back(lista);
			comcon++;
		}
		txt<<"Foram encontrados "<<comcon<<" componentes conexos.\r\n";
		componentes.sort(maior_tamanho);
		int k=0;
		for(list< list<int> >::iterator i=componentes.begin();i!=componentes.end();i++){
			k++;
			txt << "Componente " << k << ": ";
			 for(list<int>::iterator j=(*i).begin(); j!=(*i).end(); j++){
			 	txt<<*j<<" ";
			 }
			txt<<"\r\n";
		}
		txt.close();
	}	
 };  

int main() {
	Grafo grafo("subdblp.txt",0);
	//grafo.Saida();
	grafo.BFS(22);
    return 0;
}
