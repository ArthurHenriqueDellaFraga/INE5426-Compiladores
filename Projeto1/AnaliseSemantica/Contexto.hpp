#pragma once

#include "AnaliseSemantica.hpp"

#include <iostream>

#include "boost/variant/apply_visitor.hpp"
#include "boost/variant/static_visitor.hpp"

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
    VariavelFundamental instanciar(string identificador) {
        VariavelFundamental variavel;
        variavel = new Variavel<T>(identificador);

        return variavel;
    };

    class Contexto {
        public:
            map<string, VariavelFundamental(*)(string)> _tipo;

            Contexto(){
                _tipo["int"] = &instanciar<int>;
                _tipo["double"] = &instanciar<double>;
                _tipo["bool"] = &instanciar<bool>;
                _tipo["char"] = &instanciar<char>;
                _tipo["string"] = &instanciar<string>;
                // _tipo["void"] = &instanciar<void>;
            }
    };

    class Bloco : public Nodo<void> {
        protected:
            vector<NodoFundamental> listaDeInstrucoes;
            Contexto* contexto;
        public:
            Bloco() : Nodo() { }

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

                PrintFundamentalVisitor visitor;
                apply_visitor(visitor, instrucao);
            }

        class PrintFundamentalVisitor : public static_visitor<void>{
            public:
                void operator()(Nodo<int>*& nodo) const {
                    nodo->print();
                    cout << endl;
                }
                void operator()(Nodo<double>*& nodo) const {
                    nodo->print();
                    cout << endl;
                }
                void operator()(Nodo<bool>*& nodo) const {
                    nodo->print();
                    cout << endl;
                }
                void operator()(Nodo<char>*& nodo) const {
                    nodo->print();
                    cout << endl;
                }
                void operator()(Nodo<string>*& nodo) const {
                    nodo->print();
                    cout << endl;
                }
                void operator()(Nodo<void>*& nodo) const {
                    nodo->print();
                    cout << endl;
                }
        };

        class ExecutarFundamentalVisitor : public static_visitor<void>{
            public:
                Contexto* contexto;

                void operator()(Nodo<int>*& nodo) const {
                    nodo->executar(contexto);
                }
                void operator()(Nodo<double>*& nodo) const {
                    nodo->executar(contexto);
                }
                void operator()(Nodo<bool>*& nodo) const {
                    nodo->executar(contexto);
                }
                void operator()(Nodo<char>*& nodo) const {
                    nodo->executar(contexto);
                }
                void operator()(Nodo<string>*& nodo) const {
                    nodo->executar(contexto);
                }
                void operator()(Nodo<void>*& nodo) const {
                    nodo->executar(contexto);
                }
        };
    };

}
