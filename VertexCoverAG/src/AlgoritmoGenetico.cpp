#include "AlgoritmoGenetico.h"
#include "Individuo.h"
#include "Grafo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

AlgoritmoGenetico::AlgoritmoGenetico(int qtdVertices, Grafo *gr, int tamanhoPopulacao){
    this->numVertices = qtdVertices;
    this->g = gr;
    this->tamPopulacao = tamanhoPopulacao;
}

void AlgoritmoGenetico::gerarPopulacao(){
    this->populacao = new Individuo*[this->tamPopulacao];
    Individuo *ind;
    for(int i=0; i<this->tamPopulacao; ++i){
        ind = new Individuo(this->numVertices);
        ind->preencherCaracteristicasAleatoriamente(this->numVertices);
        this->populacao[i] = ind;
    }

    //this->g->AlimentaIndividuo(this->numVertices);
    /*
    ind = new Individuo(this->numVertices);
    ind->preencherCaracteristicasCompletandoTudo(this->numVertices);
    this->populacao[this->tamPopulacao-1] = ind;
    */
}

int AlgoritmoGenetico::fitness(Individuo *i){
    return this->g->fitness(i);
}

void AlgoritmoGenetico::printPopulacao(){
    for(int i=0; i<this->tamPopulacao; ++i){
        this->populacao[i]->printIndividuo(this->numVertices);
        cout << "Fitness :" << this->fitness(this->populacao[i]) << endl;
        cout << "---------" << endl;
    }
}

void AlgoritmoGenetico::printMaisApto(){
    Individuo *ind = this->populacao[0];
    for(int i=1; i< this->tamPopulacao; ++i){
        if( this->fitness(ind) > this->fitness(this->populacao[i]))
            ind = this->populacao[i];
    }
    bool valido = this->g->ehValida(ind);
    cout << "------------- Mais apto -------------" << endl;
    cout << "------------- Fitness :"<< this->fitness(ind) <<"-------------" << endl;
    if(valido){
        cout << "------------- Valido? : Sim -------------" << endl;
    } else {
        cout << "------------- Valido? : Nao -------------" << endl;
    }
    ind->printIndividuo(this->numVertices);

}

Individuo* AlgoritmoGenetico::getIndividuo(int indice){
    if( indice > -1 && indice < this->tamPopulacao){
        return this->populacao[indice];
    }
    return NULL;
}

void AlgoritmoGenetico::mutacao20(int indice){
    if( indice > -1 && indice < this->tamPopulacao){
        int vintepct = this->numVertices / 5;
        int indiceMuta;
        int i;
        Individuo *ind = new Individuo(this->numVertices);
        for(i=0; i< this->numVertices; ++i){
            ind->vetVertices[i] = this->populacao[indice]->vetVertices[i];
        }

        ind->qtdVerticesNaSolucao = this->populacao[indice]->qtdVerticesNaSolucao;

        for(i=0; i< vintepct; i++){
            indiceMuta = rand() % this->numVertices;
            if(this->populacao[indice]->vetVertices[indiceMuta]){
                this->populacao[indice]->qtdVerticesNaSolucao--;
            } else {
                this->populacao[indice]->qtdVerticesNaSolucao++;
            }
            this->populacao[indice]->vetVertices[indiceMuta] = (!this->populacao[indice]->vetVertices[indiceMuta]);
        }

        if( this->fitness(ind) < this->fitness(this->populacao[indice])){
            Individuo *old = this->populacao[indice];
            this->populacao[indice] = ind;
            delete old;
        }
    }
}


void AlgoritmoGenetico::crossoverDoisPontosCorteFixo(int i1, int i2){
    if( i1 > -1 && i2 > -1 && i1 < this->tamPopulacao && i2 < this->tamPopulacao ){
        Individuo *i3 = new Individuo(this->numVertices);
        Individuo *i4 = new Individuo(this->numVertices);
        int jump = this->numVertices / 3;
        int i;
        for( i=0; i<=jump; ++i){
            i3->vetVertices[i] = this->populacao[i1]->vetVertices[i];
            i4->vetVertices[i] = this->populacao[i2]->vetVertices[i];
        }
        for( i=jump+1; i<=2*jump; ++i){
            i3->vetVertices[i] = this->populacao[i2]->vetVertices[i];
            i4->vetVertices[i] = this->populacao[i1]->vetVertices[i];
        }
        for( i=(2*jump) +1; i<this->numVertices; ++i){
            i3->vetVertices[i] = this->populacao[i1]->vetVertices[i];
            i4->vetVertices[i] = this->populacao[i2]->vetVertices[i];
        }

        i3->setQtdVertices(this->numVertices);
        i4->setQtdVertices(this->numVertices);

        /// selecionar os 2 mais aptos entre os 4
        Individuo **vetI = new Individuo*[4];
        vetI[0] = this->populacao[i2];
        vetI[1] = this->populacao[i1];
        vetI[2] = i3;
        vetI[3] = i4;

        for(int b=0; b<4; b++ ){
            for( i=b+1; i<4; i++){
                if(this->fitness(vetI[b]) > this->fitness(vetI[i]) ){
                    Individuo *x = vetI[b];
                    vetI[b] = vetI[i];
                    vetI[i] = x;
                }
            }
        }

        this->populacao[i1] = vetI[0];
        this->populacao[i2] = vetI[1];
    }
}

void AlgoritmoGenetico::crossoverDoisPontosCorteVariavel(int i1, int i2){
    if( i1 > -1 && i2 > -1 && i1 < this->tamPopulacao && i2 < this->tamPopulacao ){
        Individuo *i3 = new Individuo(this->numVertices);
        Individuo *i4 = new Individuo(this->numVertices);
        int primeiroTerco = rand() % (this->numVertices/2);
        int segundoTerco = primeiroTerco + (this->numVertices/3);
        int i;
        for( i=0; i<=primeiroTerco; ++i){
            i3->vetVertices[i] = this->populacao[i1]->vetVertices[i];
            i4->vetVertices[i] = this->populacao[i2]->vetVertices[i];
        }
        for( i=primeiroTerco+1; i<=segundoTerco; ++i){
            i3->vetVertices[i] = this->populacao[i2]->vetVertices[i];
            i4->vetVertices[i] = this->populacao[i1]->vetVertices[i];
        }
        for( i=segundoTerco +1; i<this->numVertices; ++i){
            i3->vetVertices[i] = this->populacao[i1]->vetVertices[i];
            i4->vetVertices[i] = this->populacao[i2]->vetVertices[i];
        }

        i3->setQtdVertices(this->numVertices);
        i4->setQtdVertices(this->numVertices);

        /// selecionar os 2 mais aptos entre os 4
        Individuo **vetI = new Individuo*[4];
        vetI[0] = this->populacao[i2];
        vetI[1] = this->populacao[i1];
        vetI[2] = i3;
        vetI[3] = i4;

        for(int b=0; b<4; b++ ){
            for( i=b+1; i<4; i++){
                if(this->fitness(vetI[b]) > this->fitness(vetI[i]) ){
                    Individuo *x = vetI[b];
                    vetI[b] = vetI[i];
                    vetI[i] = x;
                }
            }
        }

        this->populacao[i1] = vetI[0];
        this->populacao[i2] = vetI[1];
    }
}

void AlgoritmoGenetico::gerarGeracoes(int qtdGeracoes, bool regularizar){
    int r1,r2;
    for(int i=0; i<qtdGeracoes; i++){
        for(int k=0; k< this->tamPopulacao/2; k++){
            r1 = rand() % this->tamPopulacao;
            r2 = rand() % this->tamPopulacao;
            this->crossoverDoisPontosCorteFixo(r1,r2);
            //this->crossoverDoisPontosCorteVariavel(r1,r2);
            this->mutacao20(r1);
            this->mutacao20(r2);
            if(regularizar){
                this->g->validarIndividuo(this->getIndividuo(r1));
                //this->g->validarIndividuo(this->getIndividuo(r2));
            }
        }
    }
}

void AlgoritmoGenetico::teste(){
    this->g->validarIndividuo(this->getIndividuo(0));
}

AlgoritmoGenetico::~AlgoritmoGenetico(){
    for(int i=0; i<this->tamPopulacao; ++i){
        delete this->populacao[i];
    }
    delete[] this->populacao;
    delete g;
}
