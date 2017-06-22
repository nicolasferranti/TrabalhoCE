#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H
#include "Individuo.h"
#include "Grafo.h"

class AlgoritmoGenetico
{
    public:
        AlgoritmoGenetico(int qtdVertices, Grafo *gr, int tamanhoPopulacao);
        ~AlgoritmoGenetico();
        void gerarPopulacao();
        void printPopulacao();
        Individuo* getIndividuo(int indice);
        void gerarGeracoes(int qtdGeracoes, bool regularizar);
        void printMaisApto();
        void teste();
    protected:

    private:
        int fitness(Individuo *i);
        void mutacao20(int indice);
        void crossoverDoisPontosCorteVariavel(int i1, int i2);
        void crossoverDoisPontosCorteFixo(int i1,int i2);
        Individuo **populacao;
        int tamPopulacao;
        int numVertices;
        Grafo *g;
};

#endif // ALGORITMOGENETICO_H
