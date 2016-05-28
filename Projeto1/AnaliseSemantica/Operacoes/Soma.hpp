#pragma once

#include "Operacao.hpp"
#include "../Contexto.hpp"

#include <iostream>

using namespace std;

namespace AnaliseSemantica {

	class Soma_inteiro_inteiro : public OperacaoBinaria<int, int, int> {
        
    public:
    	Soma_inteiro_inteiro(Nodo<int>* left, Nodo<int>* right) : OperacaoBinaria<int, int, int>(left, "(soma inteira)", right) { }

    	int executar(Contexto* contexto){
    		return this->left->executar(contexto) + this->right->executar(contexto);
    	}
    };

    template <typename L, typename R>
    class Soma_racional : public OperacaoBinaria<double, L, R> {
	
    protected:
    	Soma_racional(Nodo<L>* left, Nodo<R>* right) : OperacaoBinaria<double, L, R>(left, "(soma real)", right) { }
    };

    class Soma_racional_racional : public Soma_racional<double, double> {

    public:
    	Soma_racional_racional(Nodo<double>* left, Nodo<double>* right) : Soma_racional<double, double>(left, right) { }

		double executar(Contexto* contexto){
    		return this->left->executar(contexto) + this->right->executar(contexto);
    	}
    };

    class Soma_racional_inteiro : public Soma_racional<double, int> {
    public:
    	Soma_racional_inteiro(Nodo<double>* left, Nodo<int>* right) : Soma_racional<double, int>(left, right) { }

    	double executar(Contexto* contexto){
    		return this->left->executar(contexto) + this->right->executar(contexto);
    	}
    };

    class Soma_inteiro_racional : public Soma_racional<int, double> {
    public:
    	Soma_inteiro_racional(Nodo<int>* left, Nodo<double>* right) : Soma_racional<int, double>(left, right) { }

    	double executar(Contexto* contexto){
    		return this->left->executar(contexto) + this->right->executar(contexto);
    	}
    };
}