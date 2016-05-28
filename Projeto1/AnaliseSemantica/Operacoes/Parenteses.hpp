#pragma once

#include "Operacao.hpp"
#include "../Contexto.hpp"

#include <iostream>

using namespace std;

namespace AnaliseSemantica {

	template<typename T>
    class Parenteses : public OperacaoUnaria<T> {
        
    public:
        Parenteses(Nodo<T>* nodo) : OperacaoUnaria<T>(nodo) { }

        void print(){
        	cout << "((abre parenteses) ";
        	this->nodo->print();
        	cout<< " (fecha parenteses))"; 
        }

        T executar(Contexto* contexto){
            return this->nodo->executar(contexto);
        }
    };
}