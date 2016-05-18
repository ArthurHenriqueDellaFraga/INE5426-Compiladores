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
        Atribuicao<char>*, Atribuicao<string>*,
        Atribuicao<void>*
    > AtribuicaoFundamental;

    template <typename T>
    class Atribuicao : public Nodo<void>{
        public:
            Variavel<T>* variavel;
            Nodo<T>* valor;

            Atribuicao(Variavel<T>* variavel, Nodo<T>* valor) : variavel(variavel), valor(valor){ }

            void print(){
                variavel->print();
                cout << ":=";
                valor->print();
            }
            void executar(Contexto* contexto){
                variavel->setReferencia(&(valor->executar(contexto)));
            }

            static AtribuicaoFundamental atribuir(VariavelFundamental variavel, NodoFundamental valor){
                if(variavel.which() == valor.which()){
                    return apply_visitor(AtribuicaoVisitor (), variavel, valor);
                }
            }

            struct AtribuicaoVisitor : public static_visitor<AtribuicaoFundamental>{

                template <typename U, typename V>
                AtribuicaoFundamental operator()(U& variavel, V& valor) const {
                    variavel->print();
                    cout << " := ";
                    valor->print();

                    return atribur(variavel, valor);
                }

                static AtribuicaoFundamental atribuir(VariavelFundamental variavel, NodoFundamental valor){
                    map<string, AtribuicaoFundamental(*)(VariavelFundamental, NodoFundamental)> _atribuicao;
                      _atribuicao["int"] = &(new AtribuicaoVisitor<int>);
                      _atribuicao["double"] = &(new AtribuicaoVisitor<double>);
                      _atribuicao["bool"] = &(new AtribuicaoVisitor<bool>);
                      _atribuicao["char"] = &(new AtribuicaoVisitor<char>);
                      _atribuicao["string"] = &(new AtribuicaoVisitor<string>);
                      //CONTINUAR

                    AtribuicaoFundamental atribuicao;
                    atribuicao = _atribuicao[variavel.getTipo()](variavel, valor);
                    return atribuicao;
                }
            };
    };
}
