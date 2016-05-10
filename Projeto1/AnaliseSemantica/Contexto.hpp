#pragma once

#include "AnaliseSemantica.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename T>
    class Variavel : public Nodo<T> {
        private:
            string identificador;
            T* referencia;
        public:
            Variavel(string identificador) : identificador(identificador), referencia(new T()){ }

            void print(){
                cout << identificador << "->" << *referencia;
            }
            T executar(Contexto* contexto){
                return *referencia;
            }
    };

    typedef variant<
        Variavel<int>*, Variavel<double>*,
        Variavel<bool>*,
        Variavel<char>*, Variavel<string>*,
        Variavel<void>*
    > VariavelFundamental;

    template<typename T>
    NodoFundamental instanciar(string identificador) {
        NodoFundamental nodo;
        nodo = new Variavel<T>(identificador);

        return nodo;
    };

    class Contexto {
        public:
            map<string, NodoFundamental(*)(string)> _tipo;
            map<string, NodoFundamental> _variavel;

            Contexto(){
                _tipo["int"] = &instanciar<int>;
                _tipo["double"] = &instanciar<double>;
                _tipo["bool"] = &instanciar<bool>;
                _tipo["char"] = &instanciar<char>;
                _tipo["string"] = &instanciar<string>;
                // _tipo["void"] = &instanciar<void>;
            }
    };

    class Definicao : public Nodo<void>{
        public:
            string tipo;
            string variavel;

            Definicao(string tipo, string variavel) : tipo(tipo), variavel(variavel){ }

            void print(){
                cout << tipo << ": " << variavel;
            }
            void executar(Contexto* contexto){
                NodoFundamental nF;
                nF = contexto->_tipo[tipo](variavel);

                contexto->_variavel[variavel] = nF;
            }
    };

}
