#pragma once

#include <iostream>

using namespace std;

namespace AnaliseSemantica {

    template <typename T, typename L, typename R>
    class Operacao : public Nodo<T> {
        protected:
            Nodo<L>* left;
            string simbolo;
            Nodo<R>* right;
            Operacao(Nodo<L>* left, string simbolo, Nodo<R>* right) : left(left), simbolo(simbolo), right(right) { }
        public:
            void print(){
                cout << "(";
                left->print();
                cout << " " << simbolo << " ";
                right->print();
                cout << ")";
            };
    };
}