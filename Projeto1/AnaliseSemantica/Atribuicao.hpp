#pragma once

#include "Contexto.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename T>
    class Atribuicao;

    typedef Polimorfo<
        Atribuicao<int>*, Atribuicao<double>*,
        Atribuicao<bool>*,
        Atribuicao<char>*, Atribuicao<string>*
    > AtribuicaoFundamental;

    template <typename T>
    class Atribuicao : public Nodo<void>{
        public:
            Variavel<T>* variavel;
            NodoFundamental valor;

            Atribuicao(Variavel<T>* variavel, NodoFundamental valor) : variavel(variavel), valor(valor){ }

            void print(){
                variavel->print();
                cout << " := ";
                valor.print();
            }
            void executar(Contexto* contexto){
                //variavel->setReferencia(&(valor->executar(contexto)));
            }

            static AtribuicaoFundamental getAtribuicao(VariavelFundamental variavel, NodoFundamental valor){
                return apply_visitor(AtribuicaoVisitor (), variavel, valor);
            };

        protected:
            struct AtribuicaoVisitor : public static_visitor<AtribuicaoFundamental>{

                template <typename V, typename W>
                AtribuicaoFundamental operator()(Variavel<V>*& variavel, Nodo<W>*& valor) const {

                    NodoFundamental nodo;
                    nodo = valor;

                    AtribuicaoFundamental atribuicao;
                    atribuicao = new Atribuicao<V>(variavel, nodo);
                    return atribuicao;
                }
            };
    };
}
