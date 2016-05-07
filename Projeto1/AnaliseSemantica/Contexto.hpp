#pragma once

#include "AnaliseSemantica.hpp"
#include "Primitivo.hpp"

#include <iostream>

#include "boost/variant/apply_visitor.hpp"
#include "boost/variant/static_visitor.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template<typename T>
    TipoFundamental create() {
        TipoFundamental fundamental;
        fundamental = new T();

        return fundamental;
    };

    class Contexto {
        public:
            map<string, TipoFundamental(*)()> _tipo;

            Contexto(){
                _tipo["int"] = &create<Inteiro>;
                _tipo["double"] = &create<Racional>;
                _tipo["bool"] = &create<Booleano>;
                _tipo["char"] = &create<Caracter>;
                _tipo["string"] = &create<Sentenca>;
                _tipo["void"] = &create<Vazio>;
            }
    };

    template <typename T>
    class Variavel : public Nodo<void> {
        private:
            string identificador;
        public:
            Variavel(string identificador) : identificador(identificador) { }
            void print(){
                cout << identificador;
            }
            void executar(){
                cout << identificador << endl;
            }
    };

    class Bloco : public Nodo<void> {
        public:
            vector<TipoFundamental> listaDeInstrucoes;
            Contexto* contexto;

            Bloco() : Nodo() { }

            void print(){
                for(int i=0; i < listaDeInstrucoes.size(); i++){
                    apply_visitor(PrintFundamentalVisitor(), listaDeInstrucoes[i]);
                }
            }
            void executar(){
                for(int i=0; i < listaDeInstrucoes.size(); i++){
                    apply_visitor(ExecutarFundamentalVisitor(), listaDeInstrucoes[i]);
                }
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
                void operator()(Nodo<int>*& nodo) const {
                    nodo->executar();
                }
                void operator()(Nodo<double>*& nodo) const {
                    nodo->executar();
                }
                void operator()(Nodo<bool>*& nodo) const {
                    nodo->executar();
                }
                void operator()(Nodo<char>*& nodo) const {
                    nodo->executar();
                }
                void operator()(Nodo<string>*& nodo) const {
                    nodo->executar();
                }
                void operator()(Nodo<void>*& nodo) const {
                    nodo->executar();
                }
        };
    };

}
