#pragma once

#include "../Nodo.hpp"

using namespace std;

namespace AnaliseSemantica {

    template <typename T, typename L, typename R>
    class OperacaoBinaria : public Nodo<T> {
        protected:
            Nodo<L>* left;
            string simbolo;
            Nodo<R>* right;
            OperacaoBinaria(Nodo<L>* left, string simbolo, Nodo<R>* right) : left(left), simbolo(simbolo), right(right) { }
        public:
            void print(){
                cout << "(";
                left->print();
                cout << " (" << simbolo << " " << this->getTipo()->getIdentificadorFeminino() << ") ";
                right->print();
                cout << ")";
            };
    };

    template <typename T>
    class OperacaoUnaria : public Nodo<T> {
        protected:
            Nodo<T>* nodo;

            OperacaoUnaria(Nodo<T>* nodo) : nodo(nodo) { }
    };
}
