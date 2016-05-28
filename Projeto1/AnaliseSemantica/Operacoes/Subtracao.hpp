#pragma once

#include "Operacao.hpp"
#include "../Contexto.hpp"

#include <iostream>

using namespace std;

namespace AnaliseSemantica {

    class Subtracao_inteiro_inteiro : public Operacao<int, int, int> {
        
    public:
        Subtracao_inteiro_inteiro(Nodo<int>* left, Nodo<int>* right) : Operacao<int, int, int>(left, "(subtracao inteira)", right) { }

        int executar(Contexto* contexto){
            return this->left->executar(contexto) - this->right->executar(contexto);
        }
    };

    template <typename L, typename R>
    class Subtracao_racional : public Operacao<double, L, R> {
    
    protected:
        Subtracao_racional(Nodo<L>* left, Nodo<R>* right) : Operacao<double, L, R>(left, "(subtracao real)", right) { }
    };

    class Subtracao_racional_racional : public Subtracao_racional<double, double> {

    public:
        Subtracao_racional_racional(Nodo<double>* left, Nodo<double>* right) : Subtracao_racional<double, double>(left, right) { }

        double executar(Contexto* contexto){
            return this->left->executar(contexto) - this->right->executar(contexto);
        }
    };

    class Subtracao_racional_inteiro : public Subtracao_racional<double, int> {
    public:
        Subtracao_racional_inteiro(Nodo<double>* left, Nodo<int>* right) : Subtracao_racional<double, int>(left, right) { }

        double executar(Contexto* contexto){
            return this->left->executar(contexto) - this->right->executar(contexto);
        }
    };

    class Subtracao_inteiro_racional : public Subtracao_racional<int, double> {
    public:
        Subtracao_inteiro_racional(Nodo<int>* left, Nodo<double>* right) : Subtracao_racional<int, double>(left, right) { }

        double executar(Contexto* contexto){
            return this->left->executar(contexto) - this->right->executar(contexto);
        }
    };
}