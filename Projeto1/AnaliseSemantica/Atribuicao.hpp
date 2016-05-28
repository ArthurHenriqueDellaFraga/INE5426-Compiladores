#pragma once

#include "Contexto.hpp"
#include "Tipo.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename T = void, typename U = T>
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
                static_assert(std::is_convertible<T, U>::value, "Atribuicao incompatível");
            }

            void print(){
                variavel->print();
                cout << " := ";
                valor->print();
            }
            void executar(Contexto* contexto){
                variavel->setReferencia(new T(valor->executar(contexto)));
            }

            static NodoFundamental instanciar(VariavelFundamental variavel, NodoFundamental valor){
                return apply_visitor(createVisitor (), variavel, valor);
            }

        protected:
            struct createVisitor : public static_visitor<NodoFundamental>{
                template <typename V, typename W>
                NodoFundamental operator()(Variavel<V>*& variavel, Nodo<W>*& valor) const {
                    throw new string("erro");
                }

                template <typename V>
                NodoFundamental operator()(Variavel<V>*& variavel, Nodo<V>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<V>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<int>*& variavel, Nodo<double>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<int, double>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<int>*& variavel, Nodo<bool>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<int, bool>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<int>*& variavel, Nodo<char>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<int, char>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<double>*& variavel, Nodo<int>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<double, int>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<double>*& variavel, Nodo<bool>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<double, bool>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<double>*& variavel, Nodo<char>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<double, char>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<bool>*& variavel, Nodo<int>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<bool, int>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<bool>*& variavel, Nodo<double>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<bool, double>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<char>*& variavel, Nodo<int>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<char, int>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<char>*& variavel, Nodo<double>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<char, double>(variavel, valor);
                    return nodo;
                }

                NodoFundamental operator()(Variavel<char>*& variavel, Nodo<bool>*& valor) const {
                    NodoFundamental nodo;
                    nodo = new Atribuicao<char, bool>(variavel, valor);
                    return nodo;
                }
            };
    };
}
