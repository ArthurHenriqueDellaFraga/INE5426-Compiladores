#pragma once

#include "Operacao.hpp"
#include "../Contexto.hpp"

#include <iostream>

using namespace std;

namespace AnaliseSemantica {

    class Multiplicacao_inteiro_inteiro : public OperacaoBinaria<int, int, int> {
        
    public:
        Multiplicacao_inteiro_inteiro(Nodo<int>* left, Nodo<int>* right) : OperacaoBinaria<int, int, int>(left, "(multiplicacao inteira)", right) { }

        int executar(Contexto* contexto){
            return this->left->executar(contexto) * this->right->executar(contexto);
        }
    };

    template <typename L, typename R>
    class Multiplicacao_racional : public OperacaoBinaria<double, L, R> {
    
    protected:
        Multiplicacao_racional(Nodo<L>* left, Nodo<R>* right) : OperacaoBinaria<double, L, R>(left, "(multiplicacao real)", right) { }
    };

    class Multiplicacao_racional_racional : public Multiplicacao_racional<double, double> {

    public:
        Multiplicacao_racional_racional(Nodo<double>* left, Nodo<double>* right) : Multiplicacao_racional<double, double>(left, right) { }

        double executar(Contexto* contexto){
            return this->left->executar(contexto) * this->right->executar(contexto);
        }
    };

    class Multiplicacao_racional_inteiro : public Multiplicacao_racional<double, int> {
    public:
        Multiplicacao_racional_inteiro(Nodo<double>* left, Nodo<int>* right) : Multiplicacao_racional<double, int>(left, right) { }

        double executar(Contexto* contexto){
            return this->left->executar(contexto) * this->right->executar(contexto);
        }
    };

    class Multiplicacao_inteiro_racional : public Multiplicacao_racional<int, double> {
    public:
        Multiplicacao_inteiro_racional(Nodo<int>* left, Nodo<double>* right) : Multiplicacao_racional<int, double>(left, right) { }

        double executar(Contexto* contexto){
            return this->left->executar(contexto) * this->right->executar(contexto);
        }
    };
}