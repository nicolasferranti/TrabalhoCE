#include "Grafo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Grafo::Grafo(int qtdVertices) {
    this->matAdj = new bool*[qtdVertices];
    this->grau = new int[qtdVertices];
    this->qtdVertices =qtdVertices;

    for( int i=0; i<qtdVertices; ++i){
        this->matAdj[i] = new bool[qtdVertices];
        this->grau[i] = 0;
    }

    for(int l=0; l<qtdVertices; ++l){
        for(int c=0; c<qtdVertices; ++c){
            this->matAdj[l][c] = 0;
        }
    }


}

bool Grafo::addAresta(int v1, int v2){
    if( v1 < this->qtdVertices && v2 < this->qtdVertices){
        this->matAdj[v1][v2] = 1;
        this->grau[v1]++;

        this->matAdj[v2][v1] = 1;
        this->grau[v2]++;
        return true;
    }
    return false;
}


bool Grafo::removerAresta(int v1, int v2){
    if( v1 < this->qtdVertices && v2 < this->qtdVertices && this->matAdj[v1][v2]){
        this->matAdj[v1][v2] = 0;
        this->grau[v1]--;

        this->matAdj[v2][v1] = 0;
        this->grau[v2]--;
        return true;
    }
    return false;
}

void Grafo::printGrafo(){
    for(int i=0; i<this->qtdVertices; ++i){
        for(int j=0; j<this->qtdVertices; ++j){
                cout << this->matAdj[i][j] << " ";
        }
        cout << endl;
    }
}

void Grafo::printGrau(){
    for(int i=0; i<this->qtdVertices; ++i){
        cout << this->grau[i] << " ";
    }
    cout << endl;
}

int Grafo::fitness(Individuo *ind){
    int total = 0;
    int segundoSomatorio;
    for(int i=0; i<this->qtdVertices; ++i){

        segundoSomatorio = 0;
        for( int j=i; j<this->qtdVertices; ++j){
            if(this->matAdj[i][j]){
                segundoSomatorio += (1- ind->vetVertices[j]);
            }
        }
        total += ind->vetVertices[i] + (this->qtdVertices*(1 - ind->vetVertices[i] )*segundoSomatorio);
    }
    return total;
}


bool Grafo::ehValida(Individuo *ind){
    Grafo *clone = new Grafo(this->qtdVertices);
    int i,j;
    for( j=0; j<this->qtdVertices;j++){
        for( i=j; i<this->qtdVertices; i++ ){
            if(this->matAdj[i][j]){
                clone->addAresta(i,j);
            }
        }
    }

    for(i=0; i<this->qtdVertices; i++){
        if(ind->vetVertices[i]){
            for(j=0; j<this->qtdVertices;j++){
                clone->removerAresta(i,j);
            }
        }
    }

    /*
    clone->printGrafo();
    cout << "------------" << endl;
    clone->printGrau();
    */
    for(i=0; i<this->qtdVertices; i++){
        if(clone->grau[i] > 0){
            delete clone;
            return false;
        }
    }
    delete clone;
    return true;
}

void Grafo::validarIndividuo(Individuo *ind){

    /// Clono o grafo para fazer remocoes
    Grafo *clone = new Grafo(this->qtdVertices);
    int i,j;
    for( j=0; j<this->qtdVertices;j++){
        for( i=j; i<this->qtdVertices; i++ ){
            if(this->matAdj[i][j]){
                clone->addAresta(i,j);
            }
        }
    }

    /// Removo do clone as arestas dos nós que já estao no individuo
    for(i=0; i<this->qtdVertices; i++){
        if(ind->vetVertices[i]){
            for(j=0; j<this->qtdVertices;j++){
                clone->removerAresta(i,j);
            }
        }
    }

    /// crio o vetor com os #ids dos vertices para ordenacao
    int *vetNo = new int[this->qtdVertices];


    while(true){
        int *vetGrau = new int[this->qtdVertices];
        for(int i=0; i<this->qtdVertices; ++i){
            vetGrau[i] = clone->grau[i];
            vetNo[i] = i;
        }

        clone->quickSort(vetNo,vetGrau,0,this->qtdVertices-1);
        if( vetGrau[0] !=0 ){
            ind->vetVertices[vetNo[0]] = true;
            ind->qtdVerticesNaSolucao++;
            for(j=0; j<this->qtdVertices;j++){
                clone->removerAresta(vetNo[0],j);
            }
        } else {
            delete vetNo;
            delete vetGrau;
            delete clone;
            break;
        }
        delete vetGrau;
    }
    //cout << "------------- Valido? "<< this->ehValida(ind)  << "-------------" << endl;
    //cout << "------------- FIM DA VALIDACAO -------------" << endl;
}



int Grafo::existeGrau1(){
    for(int i=0; i<this->qtdVertices; ++i){
        if( this->grau[i] == 1){
            return i;
        }
    }
    return -1;
}

/**
    Retorna vetor com #IDs de vertices para compor genes de um individuo
    OBS.: pode vir repetido ex.: 0,0,1,4,3,3,-1,-1,-1
                                             /\ valor inicial
**/
int *Grafo::AlimentaIndividuo(int qtd){

    int *retorno = new int[this->qtdVertices];
    int indiceRetorno = 0, geneEscolhido;

    /// Clono o grafo para fazer remocoes
    Grafo *clone = new Grafo(this->qtdVertices);
    int i,j;
    for( j=0; j<this->qtdVertices;j++){
        /// preencho retorno com valores indesejados
        retorno[j] = -1;
        for( i=j; i<this->qtdVertices; i++ ){
            if(this->matAdj[i][j]){
                clone->addAresta(i,j);
            }
        }
    }

    /// pegar todos os vertices adjacentes aos vertices de grau 1 e jogar na solucao
    int vGrau1 = clone->existeGrau1();
    while(vGrau1 != -1){
        for(i=0; i<this->qtdVertices; ++i){
            if(clone->matAdj[vGrau1][i]){
                retorno[indiceRetorno] = i;
                indiceRetorno++;
                clone->removerAresta(vGrau1,i);
                break;
            }
        }
        vGrau1 = clone->existeGrau1();
    }

    /// crio o vetor com os #ids dos vertices para ordenacao
    int *vetNo = new int[this->qtdVertices];

    /// cria o vetor com os graus dos vertices
    int *vetGrau = new int[this->qtdVertices];
    for(int i=0; i<this->qtdVertices; ++i){
        vetGrau[i] = clone->grau[i];
        vetNo[i] = i;
    }

    /// ordena em ordem decrescente de grau
    this->quickSort(vetNo,vetGrau,0,this->qtdVertices-1);
    for(j=0; j<qtd; j++ ){
        geneEscolhido = rand() % int(this->qtdVertices*0.5);
        retorno[indiceRetorno] = vetNo[geneEscolhido];
        indiceRetorno++;

    }
    /*
    cout << "Grau1 :";
    for(int i=0; i<this->qtdVertices; ++i){
        cout << retorno[i] << " ";
    }
    cout << endl;
    */
    delete vetNo;
    delete vetGrau;
    delete clone;
    return retorno;
}

void Grafo::quickSort(int *vetNo, int *vetGrau, int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = vetGrau[(left + right) / 2];
    /* partition */
    while (i <= j) {
        while (vetGrau[i] > pivot && i < right)
            i++;
        while (vetGrau[j] < pivot && j > left)
            j--;
        if (i <= j) {
            tmp = vetNo[i];
            vetNo[i] = vetNo[j];
            vetNo[j] = tmp;

            tmp = vetGrau[i];
            vetGrau[i] = vetGrau[j];
            vetGrau[j] = tmp;

            i++;
            j--;

        }
    }
    /* recursion */
    if (left < j)
        quickSort(vetNo,vetGrau, left, j);
    if (i < right)
        quickSort(vetNo,vetGrau, i, right);
}


Grafo::~Grafo() {
    for(int i=0; i<this->qtdVertices; ++i){
        delete[] this->matAdj[i];
    }
    delete[] this->matAdj;
    delete[] this->grau;

}
