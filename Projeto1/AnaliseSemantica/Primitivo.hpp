#pragma once

#include "AnaliseSemantica.hpp"

#include <iostream>

#include "boost/variant.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename T>
    class Primitivo : public Nodo<T> {
        protected:
            T valor;
            Primitivo(T valor) : valor(valor) { }
        public:
            void print(){
                cout << valor;
            };
            T executar( ){
                return valor;
            }
    };

    template<>
    class Primitivo<void> : public Nodo<void>{
        protected:
            Primitivo() { };
        public:
            void print(){
                cout << '@';
            }
            void executar( ){ }
    };

    typedef variant<
        Primitivo<int>*, Primitivo<double>*,
        Primitivo<bool>*,
        Primitivo<char>*, Primitivo<string>*,
        Primitivo<void>*
    > TipoPrimitivo;

    class Inteiro : public Primitivo<int> {
        public:
            Inteiro(int valor = 0) : Primitivo(valor) { }
    };

    class Racional : public Primitivo<double> {
        public:
            Racional(double valor = 0.0) : Primitivo(valor) { }
    };

    class Booleano : public Primitivo<bool> {
        public:
            Booleano(bool valor = false) : Primitivo(valor) { }
    };

    class Caracter : public Primitivo<char> {
        public:
            Caracter(char valor = ' ') : Primitivo(valor) { }
    };

    class Sentenca : public Primitivo<string> {
        public:
            Sentenca(string valor = "") : Primitivo(valor) { }
    };

    class Vazio : public Primitivo<void>{
        public:
            Vazio() : Primitivo<void>() { }
    };

}
