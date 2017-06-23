#include <iostream>
#include <fstream>
#include <string>
#include "Individuo.h"
#include "Grafo.h"
#include "AlgoritmoGenetico.h"

using namespace std;

int main()
{
    int op = -1;
    int qtdVertices,tamanhoPopulacao = 80;
    int melhorCobertura;
    int c1,c2;
    Grafo *g = NULL;
    AlgoritmoGenetico *ag = NULL;
    string caminhoArquivo,linha;
    fstream meuArquivo;
    while (op != 0){
        cout << "-------------" << endl;
        cout << "(0) Sair" << endl;
        cout << "(1) Instancia pequena teste" << endl;
        cout << "(2) Ler arquivo" << endl;
        cout << "(3) teste" << endl;
        cout << "-------------" << endl;
        cin >> op;
        switch(op){
            case 0:
                break;
            case 1:
                qtdVertices = 5;
                g = new Grafo(qtdVertices);
                g->addAresta(0,1);
                g->addAresta(0,2);
                g->addAresta(0,3);
                g->addAresta(0,4);
                g->addAresta(1,2);
                g->addAresta(1,3);
                //g->addAresta(1,4);
                g->printGrafo();
                cout << "-------------" << endl;
                g->printGrau();
                cout << "-------------" << endl;
                ag = new AlgoritmoGenetico(qtdVertices,g,1);
                ag->gerarPopulacao(true);
                //ag->teste();
                //ag->printPopulacao();
                ag->printMaisApto();
                //ag->gerarGeracoes(2,true);
                cout << "EOGERACOES" << endl;
                //ag->printPopulacao();
                ag->printMaisApto();
                delete ag;
                break;
            case 2:
                cout << "Digite o caminho e nome do arquivo(/home/nicolas/Downloads/frb30-15-mis/frb30-15-1.mis) : ";
                cin >> caminhoArquivo;
                meuArquivo.open(caminhoArquivo.c_str());
                meuArquivo >> c1 >> c2;
                melhorCobertura = c2;
                qtdVertices = c1;
                g = new Grafo(c1);
                while ( meuArquivo >> c1 >> c2 ){
                    g->addAresta(c1-1,c2-1);
                }
                cout << "------------- Finalizou a criacao do Grafo -------------" << endl;
                meuArquivo.close();
                ag = new AlgoritmoGenetico(qtdVertices,g,tamanhoPopulacao);
                ag->gerarPopulacao(false);
                cout << "------------- Iniciando AG -------------" << endl;
                ag->printMaisApto();
                ag->gerarGeracoes(200,true,true);
                ag->printMaisApto();
                cout << "------------- Melhor Cobertura :"<< melhorCobertura <<"-------------" << endl;
                delete ag;
                break;
            case 3:
                meuArquivo.open("/home/nicolas/Downloads/frb30-15-mis/frb30-15-1.mis");
                meuArquivo >> c1 >> c2;
                melhorCobertura = c2;
                qtdVertices = c1;
                g = new Grafo(qtdVertices);
                while ( meuArquivo >> c1 >> c2 ){
                    g->addAresta(c1-1,c2-1);
                }
                cout << "------------- Finalizou a criacao do Grafo -------------" << endl;
                meuArquivo.close();
                ag = new AlgoritmoGenetico(qtdVertices,g,tamanhoPopulacao);
                ag->gerarPopulacao(true);
                cout << "------------- Iniciando AG -------------" << endl;
                ag->printMaisApto();
                ag->gerarGeracoes(100,true,true);
                //ag->teste();
                ag->printMaisApto();
                cout << "------------- Melhor Cobertura :"<< melhorCobertura <<"-------------" << endl;
                delete ag;
                break;
            default:
                break;
        }
    }
    /***
    Pontos:
        Gerar população:
            -> (OK)   Método Randomico
            -> (OK)   Método Heurístico
        CrossOver:
            -> (OK)   Dois Pontos Fixos
            -> (OK)   Dois Pontos Variavel
        Roleta CrossOver:
            -> (OK)   Aleatoria
            -> (TODO) Aleatoria com maior probabilidade para menores fitness
        Mutação:
            -> (OK)   20% Aleatoria
        Regularizar Individuo:
            -> (OK)   Método Heuristico MaiorGrau
    **/
    return 0;
}
