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

    template <typename T = void, typename N = T>
    class OperacaoUnaria : public Nodo<T> {
        protected:
            Nodo<N>* nodo;

            OperacaoUnaria(Nodo<N>* nodo) : nodo(nodo) { }

            T executar(Contexto* contexto){
                return *(new T());
            }
    };

    template <typename N>
    class OperacaoUnaria<void, N> : public Nodo<void> {
        protected:
            Nodo<N>* nodo;

            OperacaoUnaria(Nodo<N>* nodo) : nodo(nodo) { }

            void executar(Contexto* contexto){ }
    };
}
