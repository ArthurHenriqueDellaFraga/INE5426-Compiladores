#include "AnaliseSemantica.h"

#include <iostream>

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
            T executar(){
                return valor;
            }
    };

    class Inteiro : public Primitivo<int> {
        public:
            Inteiro(int valor) : Primitivo(valor) { }
    };

    class Racional : public Primitivo<double> {
        public:
            Racional(double valor) : Primitivo(valor) { }
    };

    class Booleano : public Primitivo<bool> {
        public:
            Booleano(bool valor) : Primitivo(valor) { }
    };

    class Caracter : public Primitivo<char> {
        public:
            Caracter(char valor) : Primitivo(valor) { }
    };

    class Sentenca : public Primitivo<string> {
        public:
            Sentenca(string valor) : Primitivo(valor) { }
    };
}
