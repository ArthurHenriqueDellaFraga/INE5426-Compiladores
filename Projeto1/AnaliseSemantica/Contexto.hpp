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

            void setReferencia(T* referencia){
                this->referencia = referencia;
            }

            class NodoConversorVisitor : public static_visitor<NodoFundamental>{
                public:
                    NodoFundamental operator()(Variavel<int>*& variavel) const {
                        NodoFundamental nodo;
                        nodo = variavel;
                        return nodo;
                    }
                    NodoFundamental operator()(Variavel<double>*& variavel) const {
                        NodoFundamental nodo;
                        nodo = variavel;
                        return nodo;
                    }
                    NodoFundamental operator()(Variavel<bool>*& variavel) const {
                        NodoFundamental nodo;
                        nodo = variavel;
                        return nodo;
                    }
                    NodoFundamental operator()(Variavel<char>*& variavel) const {
                        NodoFundamental nodo;
                        nodo = variavel;
                        return nodo;
                    }
                    NodoFundamental operator()(Variavel<string>*& variavel) const {
                        NodoFundamental nodo;
                        nodo = variavel;
                        return nodo;
                    }
                    NodoFundamental operator()(Variavel<void>*& variavel) const {
                        NodoFundamental nodo;
                        nodo = variavel;
                        return nodo;
                    }
            };
    };

    typedef variant<
        Variavel<int>*, Variavel<double>*,
        Variavel<bool>*,
        Variavel<char>*, Variavel<string>*,
        Variavel<void>*
    > VariavelFundamental;

    class Contexto {
        protected:
            map<string, TipoFundamental(*)()> _tipo;
        public:
            map<string, VariavelFundamental> _variavel;

            Contexto(){ }
    };

    template <typename T>
    class Definicao;

    typedef variant<
        Definicao<int>*, Definicao<double>*,
        Definicao<bool>*,
        Definicao<char>*, Definicao<string>*,
        Definicao<void>*
    > DefinicaoFundamental;

    template <typename T>
    class Definicao : public Nodo<void>{
        protected:
            template<typename U>
            static DefinicaoFundamental getDefinicao(string tipo, string identificador) {
                DefinicaoFundamental definicao;
                definicao = new Definicao<U>(tipo, identificador);

                return definicao;
            };

        public:
            string tipo;
            string identificador;

            Definicao(string tipo, string identificador) : tipo(tipo), identificador(identificador){ }

            void print(){
                cout << tipo << ": " << identificador;
            }
            void executar(Contexto* contexto){
                VariavelFundamental variavel;
                variavel = new Variavel<T>(identificador);

                contexto->_variavel[identificador] = variavel;
            }

            static DefinicaoFundamental definir(string tipo, string identificador){
                map<string, DefinicaoFundamental(*)(string, string)> _definicao;
                    _definicao["int"] = &getDefinicao<int>;
                    _definicao["double"] = &getDefinicao<double>;
                    _definicao["bool"] = &getDefinicao<bool>;
                    _definicao["char"] = &getDefinicao<char>;
                    _definicao["string"] = &getDefinicao<string>;


                return _definicao[tipo](tipo, identificador);
            }

            class NodoConversorVisitor : public static_visitor<NodoFundamental>{
                public:
                    NodoFundamental operator()(Definicao<int>*& definicao) const {
                        NodoFundamental nodo;
                        nodo = definicao;
                        return nodo;
                    }
                    NodoFundamental operator()(Definicao<double>*& definicao) const {
                        NodoFundamental nodo;
                        nodo = definicao;
                        return nodo;
                    }
                    NodoFundamental operator()(Definicao<bool>*& definicao) const {
                        NodoFundamental nodo;
                        nodo = definicao;
                        return nodo;
                    }
                    NodoFundamental operator()(Definicao<char>*& definicao) const {
                        NodoFundamental nodo;
                        nodo = definicao;
                        return nodo;
                    }
                    NodoFundamental operator()(Definicao<string>*& definicao) const {
                        NodoFundamental nodo;
                        nodo = definicao;
                        return nodo;
                    }
                    NodoFundamental operator()(Definicao<void>*& definicao) const {
                        NodoFundamental nodo;
                        nodo = definicao;
                        return nodo;
                    }
            };
    };

    // template <typename T>
    // class Atribuicao : public Nodo<void>{
    //     public:
    //         Variavel<T>* variavel;
    //         Nodo<T>* valor;
    //
    //         Atribuicao(Variavel<T>* variavel, Nodo<T>* valor) : variavel(variavel), valor(valor){ }
    //
    //         void print(){
    //             variavel->print();
    //             cout << ":=";
    //             valor->print();
    //         }
    //         void executar(Contexto* contexto){
    //             variavel->setReferencia(&(valor->executar(contexto)));
    //         }
    // }
    //
    // typedef variant<
    //     Atribuicao<int>*, Atribuicao<double>*,
    //     Atribuicao<bool>*,
    //     Atribuicao<char>*, Atribuicao<string>*,
    //     Atribuicao<void>*
    // > AtribuicaoFundamental;
    //
    // class AtribuicaoVisitor : public static_visitor<AtribuicaoFundamental>{
    //     public:
    //         AtribuicaoFundamental atribuicao;
    //         NodoFundamental valor;
    //
    //         AtribuicaoFundamental operator()(Variavel<int>*& variavel) const {
    //             Nodo<int>* nodo = get<Nodo<int>*>(valor);
    //
    //             variavel->print()
    //             cout << " := "
    //             valor->print();
    //
    //             atribuicao = new Atribuicao<int>(variavel, nodo);
    //             return atribuicao;
    //         }
    //         AtribuicaoFundamental operator()(Variavel<double>*& variavel) const {
    //             Nodo<double>* nodo = get<Nodo<double>*>(valor);
    //
    //             atribuicao = new Atribuicao<double>(variavel, nodo);
    //             return atribuicao;
    //         }
    //         AtribuicaoFundamental operator()(Variavel<bool>*& variavel) const {
    //             Nodo<bool>* nodo = get<Nodo<bool>*>(valor);
    //
    //             atribuicao = new Atribuicao<bool>(variavel, nodo);
    //             return atribuicao;
    //         }
    //         AtribuicaoFundamental operator()(Variavel<char>*& variavel) const {
    //             Nodo<char>* nodo = get<Nodo<char>*>(valor);
    //
    //             atribuicao = new Atribuicao<char>(variavel, nodo);
    //             return atribuicao;
    //         }
    //         AtribuicaoFundamental operator()(Variavel<string>*& variavel) const {
    //             Nodo<string>* nodo = get<Nodo<string>*>(valor);
    //
    //             atribuicao = new Atribuicao<string>(variavel, nodo);
    //             return atribuicao;
    //         }
    //         AtribuicaoFundamental operator()(Variavel<void>*& variavel) const {
    //             Nodo<void>* nodo = get<Nodo<void>*>(valor);
    //
    //             atribuicao = new Atribuicao<void>(variavel, nodo);
    //             return atribuicao;
    //         }
    // };

}
