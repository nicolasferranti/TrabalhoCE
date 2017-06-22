#ifndef GRAFO_H
#define GRAFO_H

#include "Individuo.h"

class Grafo
{
    public:
        Grafo(int qtdVertices);
        bool addAresta(int v1, int v2);
        void printGrafo();
        void printGrau();
        int fitness(Individuo *ind);
        bool ehValida(Individuo *ind);
        bool removerAresta(int v1, int v2);
        int *grau;
        void validarIndividuo(Individuo *ind);
        int *AlimentaIndividuo(int qtd);
        void quickSort(int *vetNo,int *vetGrau, int left, int right);
        ~Grafo();

    protected:

    private:
        bool **matAdj;
        int qtdVertices;
};

#endif // GRAFO_H
