#pragma once

#include "Contexto.hpp"

using namespace std;

namespace AnaliseSemantica {

    template <typename T>
    class Primitivo : public Nodo<T> {
        public:
            T valor;
            Primitivo(T valor) : valor(valor) { }
            Primitivo() { }

            void print(){
                cout << "valor " << this->getTipo()->getIdentificadorMasculino() << " " << valor;
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


    template<>
    class Primitivo<bool> : public Nodo<bool>{
        public:
            bool valor;
            Primitivo(bool valor) : valor(valor) { };

            void print(){
                cout << "valor " << "booleano" << " ";
                if(valor){
                    cout << "TRUE";
                }else{
                    cout << "FALSE";
                }
            }

            bool executar(Contexto* contexto){
                return valor;
            }
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
