#pragma once

#include "Contexto.hpp"

#include <iostream>

#include "boost/variant.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename T>
    class Primitivo : public Nodo<T> {
        public:
            T valor;
            Primitivo(T valor) : valor(valor) { }
            Primitivo() { }

            void print(){
                this->getTipo().print();
                cout << valor;

            };
            T executar(Contexto* contexto){
                return valor;
            }
    };

    template<>
    class Primitivo<void> : public Nodo<void>{
        public:
            Primitivo() { };

            void print(){
                cout << '@';
            }
            void executar(Contexto* contexto){ }
    };

    typedef Primitivo<int> Inteiro;
    typedef Primitivo<double> Racional;
    typedef Primitivo<bool> Booleano;
    typedef Primitivo<char> Caracter;
    typedef Primitivo<string> Sentenca;
    typedef Primitivo<void> Vazio;

    typedef Polimorfo<
        Inteiro*, Racional*,
        Booleano*,
        Caracter*, Sentenca*,
        Vazio*
    > PrimitivoFundamental;

}
