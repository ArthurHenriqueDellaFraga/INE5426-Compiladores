#pragma once

#include "Operacao.hpp"
#include "../Contexto.hpp"

#include <iostream>

using namespace std;

namespace AnaliseSemantica {

    class Divisao_inteiro_inteiro : public Operacao<int, int, int> {
        
    public:
        Divisao_inteiro_inteiro(Nodo<int>* left, Nodo<int>* right) : Operacao<int, int, int>(left, "(divisao inteira)", right) { }

        int executar(Contexto* contexto){
            return this->left->executar(contexto) / this->right->executar(contexto);
        }
    };

    template <typename L, typename R>
    class Divisao_racional : public Operacao<double, L, R> {
    
    protected:
        Divisao_racional(Nodo<L>* left, Nodo<R>* right) : Operacao<double, L, R>(left, "(divisao real)", right) { }
    };

    class Divisao_racional_racional : public Divisao_racional<double, double> {

    public:
        Divisao_racional_racional(Nodo<double>* left, Nodo<double>* right) : Divisao_racional<double, double>(left, right) { }

        double executar(Contexto* contexto){
            return this->left->executar(contexto) / this->right->executar(contexto);
        }
    };

    class Divisao_racional_inteiro : public Divisao_racional<double, int> {
    public:
        Divisao_racional_inteiro(Nodo<double>* left, Nodo<int>* right) : Divisao_racional<double, int>(left, right) { }

        double executar(Contexto* contexto){
            return this->left->executar(contexto) / this->right->executar(contexto);
        }
    };

    class Divisao_inteiro_racional : public Divisao_racional<int, double> {
    public:
        Divisao_inteiro_racional(Nodo<int>* left, Nodo<double>* right) : Divisao_racional<int, double>(left, right) { }

        double executar(Contexto* contexto){
            return this->left->executar(contexto) / this->right->executar(contexto);
        }
    };
}