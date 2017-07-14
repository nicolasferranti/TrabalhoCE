#include "Individuo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Individuo::Individuo(int qtdVertices){
    this->vetVertices = new bool[qtdVertices];
    this->qtdVerticesNaSolucao = 0;
}

//Individuo::Individuo(){}

void Individuo::preencherCaracteristicasAleatoriamente(int qtdVerticesTotal){
    int vertice = 0;
    for(int i=0; i<qtdVerticesTotal; ++i){
        vertice = rand() % 10;
        //std::cout << "y/n :" << vertice << std::endl;
        if( vertice >= 5){
            this->vetVertices[i] = true;
            this->qtdVerticesNaSolucao++;
        } else {
            this->vetVertices[i] = false;
        }
    }
}

void Individuo::preencherCaracteristicasCompletandoTudo(int qtdVerticesTotal){
    for(int i=0; i<qtdVerticesTotal; ++i){
        this->vetVertices[i] = true;
        this->qtdVerticesNaSolucao++;
    }
}

/// TODO
void Individuo::preencherCaracteristicasHeuristica(int *genes, int qtdVertices){
    int i;
    for(i=0; i< qtdVertices; ++i){
        this->vetVertices[i] = false;
    }
    for(i=0; genes[i]!= -1; ++i){
        if( !this->vetVertices[genes[i]] ){
            this->vetVertices[genes[i]] = true;
            this->qtdVerticesNaSolucao++;
        }
    }
}

void Individuo::printIndividuo(int qtdVerticesTotal){
    cout << "------------- Qtd Vertices na solucao: "<< this->qtdVerticesNaSolucao <<" -------------" << endl;
    /*
    cout << "Genes : ";
    for(int i=0; i<qtdVerticesTotal; ++i){
        cout << this->vetVertices[i] << " ";
    }
    cout << endl;
    */
}

void Individuo::setQtdVertices(int qtdVertices){
    this->qtdVerticesNaSolucao = 0;
    for(int i=0; i<qtdVertices;i++){
        if(this->vetVertices[i]){
            this->qtdVerticesNaSolucao++;
        }
    }
}

Individuo::~Individuo(){
    delete[] this->vetVertices;
}
