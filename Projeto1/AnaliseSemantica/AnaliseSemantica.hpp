#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "boost/variant.hpp"
#include "boost/variant/apply_visitor.hpp"
#include "boost/variant/static_visitor.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    class Contexto;

    typedef variant<
        int, double, bool, char, string, void
    > TipoFundamental;

    template <typename T>
    class Nodo {
        public:
            // virtual ~Nodo();
            virtual void print() = 0;
            virtual T executar(Contexto* contexto) = 0;
    };

    typedef variant<
        Nodo<int>*, Nodo<double>*,
        Nodo<bool>*,
        Nodo<char>*, Nodo<string>*,
        Nodo<void>*
    > NodoFundamental;

    class NodoConversorVisitor : public static_visitor<NodoFundamental>{
        public:
            template <typename T>
            NodoFundamental operator()(T& t) const {
                NodoFundamental nodo;
                nodo = t;
                return nodo;
            }
    };

    class Bloco : public Nodo<void> {
        protected:
            vector<NodoFundamental> listaDeInstrucoes;
            Contexto* contexto;
        public:
            Bloco(Contexto* contexto) : contexto(contexto), Nodo() { }

            void print(){
                for(int i=0; i < listaDeInstrucoes.size(); i++){
                    apply_visitor(PrintFundamentalVisitor (), listaDeInstrucoes[i]);
                }
            }
            void executar(Contexto* contexto){
                for(int i=0; i < listaDeInstrucoes.size(); i++){
                    ExecutarFundamentalVisitor visitor;
                    visitor.contexto = this->contexto;
                    apply_visitor(visitor, listaDeInstrucoes[i]);
                }
            }

            void addInstrucao(NodoFundamental instrucao){
                listaDeInstrucoes.push_back(instrucao);
                cout << "Bloco->addInstrucao :: ";

                apply_visitor(PrintFundamentalVisitor (), instrucao);

                ExecutarFundamentalVisitor visitor;
                visitor.contexto = this->contexto;
                apply_visitor(visitor, instrucao);
            }

            Contexto* getContexto(){
                return contexto;
            }

        class PrintFundamentalVisitor : public static_visitor<void>{
            public:
                template <typename T>
                void operator()(T& instrucao) const {
                    instrucao->print();
                    cout << endl;
                }
        };

        class ExecutarFundamentalVisitor : public static_visitor<void>{
            public:
                Contexto* contexto;

                template <typename T>
                void operator()(T& instrucao) const {
                    instrucao->executar(contexto);
                }
        };
    };

}
