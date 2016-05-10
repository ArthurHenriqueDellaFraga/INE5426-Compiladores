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
            map<string, VariavelFundamental> _variavel;

            Contexto(){
                _tipo["int"] = &instanciar<int>;
                _tipo["double"] = &instanciar<double>;
                _tipo["bool"] = &instanciar<bool>;
                _tipo["char"] = &instanciar<char>;
                _tipo["string"] = &instanciar<string>;
                // _tipo["void"] = &instanciar<void>;
            }
    };

    class Definicao : public Nodo<void>{
        public:
            string tipo;
            string variavel;

            Definicao(string tipo, string variavel) : tipo(tipo), variavel(variavel){ }

            void print(){
                cout << tipo << ": " << variavel;
            }
            void executar(Contexto* contexto){
                VariavelFundamental variavel;
                variavel = contexto->_tipo[tipo](variavel);

                contexto->_variavel[variavel] = variavel;
            }
    };

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
    }

    typedef variant<
        Atribuicao<int>*, Atribuicao<double>*,
        Atribuicao<bool>*,
        Atribuicao<char>*, Atribuicao<string>*,
        Atribuicao<void>*
    > AtribuicaoFundamental;

    class AtribuicaoVisitor : public static_visitor<AtribuicaoFundamental>{
        public:
            AtribuicaoFundamental atribuicao;
            NodoFundamental valor;

            AtribuicaoFundamental operator()(Variavel<int>*& variavel) const {
                Nodo<int> nodo = get<int>(valor);

                variavel->print()
                cout << " := "
                valor->print();

                atribuicao = new Atribuicao<int>(variavel, nodo);
                return atribuicao;
            }
            AtribuicaoFundamental operator()(Variavel<double>*& variavel) const {
                Nodo<double> nodo = get<double>(valor);

                atribuicao = new Atribuicao<double>(variavel, nodo);
                return atribuicao;
            }
            AtribuicaoFundamental operator()(Variavel<bool>*& variavel) const {
                Nodo<bool> nodo = get<bool>(valor);

                atribuicao = new Atribuicao<bool>(variavel, nodo);
                return atribuicao;
            }
            AtribuicaoFundamental operator()(Variavel<char>*& variavel) const {
                Nodo<char> nodo = get<char>(valor);

                atribuicao = new Atribuicao<char>(variavel, nodo);
                return atribuicao;
            }
            AtribuicaoFundamental operator()(Variavel<string>*& variavel) const {
                Nodo<string> nodo = get<string>(valor);

                atribuicao = new Atribuicao<string>(variavel, nodo);
                return atribuicao;
            }
            AtribuicaoFundamental operator()(Variavel<void>*& variavel) const {
                Nodo<void> nodo = get<void>(valor);

                atribuicao = new Atribuicao<void>(variavel, nodo);
                return atribuicao;
            }
    };

}
