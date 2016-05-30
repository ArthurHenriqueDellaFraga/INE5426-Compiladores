#pragma once

#include "Conversao.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename T = void, typename U = T>
    class Atribuicao;

    typedef Polimorfo<
        Atribuicao<int>*, Atribuicao<double>*,
        Atribuicao<bool>*,
        Atribuicao<char>*, Atribuicao<string>*,
        Atribuicao<void>*
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
                cout << "Atribuicao de valor para ";
                variavel->print();
                cout << ": ";
                valor-> print();
            }
            void executar(Contexto* contexto){
                //variavel->setReferencia(new T(valor->executar(contexto)));
            }

            static NodoFundamental* instanciar(VariavelFundamental variavel, NodoFundamental valor){
                return apply_visitor(createVisitor (), variavel, valor);
            }

        protected:
            struct createVisitor : public static_visitor<NodoFundamental*>{
                template <typename V, typename W>
                NodoFundamental* operator()(Variavel<V>*& variavel, Nodo<W>*& valor) const {
                      VariavelFundamental vF;
                      vF = variavel;
                      NodoFundamental nF;
                      nF = valor;

                      NodoFundamental conversao = *(Conversao<>::instanciar(vF.getTipo(), nF));
                      return Atribuicao<int>::instanciar(vF, conversao);
                }

                template <typename V>
                NodoFundamental* operator()(Variavel<V>*& variavel, Nodo<V>*& valor) const {
                    return new NodoFundamental(new Atribuicao<V>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<void>*& variavel, Nodo<void>*& valor) const {
                    throw new Erro("erro");
                }
            };
    };

    template <typename T>
    class AtribuicaoArranjo : public Atribuicao<T>{
        public:
            Arranjo<T>* arranjo;
            Nodo<int>* indice;
            Nodo<T>* valor;

            AtribuicaoArranjo(Arranjo<T>* arranjo, Nodo<int>* indice, Nodo<T>* valor) : arranjo(arranjo), indice(indice), valor(valor){
                // static_assert(std::is_convertible<T, U>::value, "Atribuicao incompatível");
            }

            void print(){
                cout << "Atribuicao de valor para ";
                // variavel->print();
                cout << ": ";
                valor-> print();
            }
            void executar(Contexto* contexto){
                //variavel->setReferencia(new T(valor->executar(contexto)));
            }

            static NodoFundamental* instanciarArranjo(ArranjoFundamental arranjo, NodoFundamental indice, NodoFundamental valor){
                Nodo<int>* nodo = apply_visitor(createInteiroVisitor (), indice);

                createTipoVisitor visitor;
                visitor.indice = nodo;
                return apply_visitor(visitor, arranjo, valor);
            }

        protected:
            struct createTipoVisitor : public static_visitor<NodoFundamental*>{
                Nodo<int>* indice;

                template <typename V, typename W>
                NodoFundamental* operator()(Arranjo<V>*& arranjo, Nodo<W>*& valor) const {
                      ArranjoFundamental aF;
                      aF = arranjo;
                      NodoFundamental nF;
                      nF = valor;
                      NodoFundamental iF;
                      iF = indice;

                      NodoFundamental conversao = *(Conversao<>::instanciar(aF.getTipo(), nF));
                      return AtribuicaoArranjo<V>::instanciarArranjo(aF, iF, conversao);
                }

                template <typename V>
                NodoFundamental* operator()(Arranjo<V>*& arranjo, Nodo<V>*& valor) const {
                    return new NodoFundamental(new AtribuicaoArranjo<V>(arranjo, indice, valor));
                }

                NodoFundamental* operator()(Variavel<void>*& variavel, Nodo<void>*& valor) const {
                    throw new Erro("erro");
                }
            };

            struct createInteiroVisitor : public static_visitor<Nodo<int>*>{
                string errorMessage = "indice de arranjo espera inteiro mas rececebeu ";

                template <typename V>
                Nodo<int>* operator()(Nodo<V>*& nodo) const {
                    throw new Erro(errorMessage + nodo->getTipo().getIdentificadorMasculino() + ".");
                }

                Nodo<int>* operator()(Nodo<int>*& nodo) const {
                    return nodo;
                }
            };
    };
}