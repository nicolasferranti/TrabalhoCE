#ifndef INDIVIDUO_H
#define INDIVIDUO_H

class Individuo
{
    public:
        Individuo(int qtdVertices);
        bool *vetVertices;
        int arestasNaoAtendidas;
        int qtdVerticesNaSolucao;
        void printIndividuo(int qtdVerticesTotal);
        void setQtdVertices(int qtdVertices);
        ~Individuo();
        void preencherCaracteristicasAleatoriamente(int qtdVerticesTotal);
        void preencherCaracteristicasCompletandoTudo(int qtdVerticesTotal);
        void preencherCaracteristicasHeuristica();
    protected:

    private:
};

#endif // INDIVIDUO_H
