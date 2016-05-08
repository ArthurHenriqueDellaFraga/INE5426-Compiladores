#pragma once

#include "AnaliseSemantica.hpp"
#include "Primitivo.hpp"

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
            Primitivo<T>* referencia;
        public:
            Variavel(string identificador) : identificador(identificador), referencia(new Primitivo<T>()) { }

            void print(){
                cout << identificador << "->";
                referencia->print();
            }
            T executar(){
                return referencia->executar();
            }
    };

    template<typename T>
    TipoFundamental create(string identificador) {
        TipoFundamental fundamental;
        fundamental = new Variavel<T>(identificador);

        return fundamental;
    };

    class Contexto {
        public:
            map<string, TipoFundamental(*)(string)> _tipo;

            Contexto(){
                _tipo["int"] = &create<int>;
                _tipo["double"] = &create<double>;
                _tipo["bool"] = &create<bool>;
                _tipo["char"] = &create<char>;
                _tipo["string"] = &create<string>;
                _tipo["void"] = &create<void>;
            }
    };

    class Bloco : public Nodo<void> {
        protected:
            vector<TipoFundamental> listaDeInstrucoes;
            Contexto* contexto;
        public:
            Bloco() : Nodo() { }

            void print(){
                for(int i=0; i < listaDeInstrucoes.size(); i++){
                    apply_visitor(PrintFundamentalVisitor (), listaDeInstrucoes[i]);
                }
            }
            void executar(){
                for(int i=0; i < listaDeInstrucoes.size(); i++){
                    apply_visitor(ExecutarFundamentalVisitor (), listaDeInstrucoes[i]);
                }
            }

            void addInstrucao(TipoFundamental instrucao){
                listaDeInstrucoes.push_back(instrucao);
                apply_visitor(PrintFundamentalVisitor (), instrucao);
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
