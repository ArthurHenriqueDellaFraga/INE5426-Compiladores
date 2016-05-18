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

    template <typename T>
    class Nodo {
        public:
            // virtual ~Nodo();
            virtual void print() = 0;
            virtual T executar(Contexto* contexto) = 0;
    };

    template <typename... Types>
    class Polimorfo : public variant<Types...>{
        public:
            Polimorfo() : variant<Types...>(){}

            void print(){
                apply_visitor(PrintVisitor(), *this);
            }

            void executar(Contexto* contexto){
                ExecutarVisitor visitor;
                visitor.contexto = contexto;
                apply_visitor(visitor, *this);
            }

            template<typename T>
            Polimorfo<Types...>& operator=(const T& t){
                variant<Types...>::operator=(t);
                return *this;
            }

            string getTipo(){
                switch (this->which()){
                    case 0: return "int";
                    case 1: return "double";
                    case 2: return "bool";
                    case 3: return "char";
                    case 4: return "string";
                    default: return "void";
                }
            }

        protected:
            struct PrintVisitor : public static_visitor<void> {
                template <typename T>
                void operator()(T t) const {
                    t->print();
                }
            };

            struct ExecutarVisitor : public static_visitor<void> {
                Contexto* contexto;

                template <typename T>
                void operator()(T t) const {
                    t->executar(contexto);
                }
            };
    };

    typedef variant<
        int, double, bool, char, string, void
    > TipoFundamental;

    typedef Polimorfo<
        Nodo<int>*, Nodo<double>*,
        Nodo<bool>*,
        Nodo<char>*, Nodo<string>*,
        Nodo<void>*
    > NodoFundamental;

    struct NodoConversorVisitor : public static_visitor<NodoFundamental>{
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
                    listaDeInstrucoes[i].print();
                }
            }
            void executar(Contexto* contexto){
                for(int i=0; i < listaDeInstrucoes.size(); i++){
                    listaDeInstrucoes[i].executar(contexto);
                }
            }

            void addInstrucao(NodoFundamental instrucao){
                listaDeInstrucoes.push_back(instrucao);
                cout << "Bloco->addInstrucao :: ";

                instrucao.print();
                cout << endl;

                instrucao.executar(contexto);
            }

            Contexto* getContexto(){
                return contexto;
            }
    };

}
