#pragma once

#include "Contexto.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename T = void, typename W = void>
    class Atribuicao;

    typedef Polimorfo<
        Atribuicao<int>*, Atribuicao<double>*,
        Atribuicao<bool>*,
        Atribuicao<char>*, Atribuicao<string>*
    > AtribuicaoFundamental;

    template <typename T, typename U>
    class Atribuicao : public Nodo<void>{
        public:
            Variavel<T>* variavel;
            Nodo<U>* valor;

            Atribuicao(Variavel<T>* variavel, Nodo<U>* valor) : variavel(variavel), valor(valor){
                // if(!std::is_convertible<T, U>::value){
                //     throw new string("erro");
                // }
                cout << "Atribuição - ";
            }

            void print(){
                variavel->print();
                cout << " := ";
                valor->print();
            }
            void executar(Contexto* contexto){
              //  variavel->setReferencia(new T(valor->executar(contexto)));
            }

            static NodoFundamental instanciar(VariavelFundamental variavel, NodoFundamental valor){
                return apply_visitor(AtribuicaoVisitor (), variavel, valor);
            }

        protected:
            struct AtribuicaoVisitor : public static_visitor<NodoFundamental>{
                template <typename V, typename W>
                NodoFundamental operator()(Variavel<V>*& variavel, Nodo<W>*& valor) const {
                    throw new string("Erro");
                }
            };
    };
}
