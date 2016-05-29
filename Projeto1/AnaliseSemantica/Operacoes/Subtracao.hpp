#pragma once

#include "Operacao.hpp"

using namespace std;

namespace AnaliseSemantica {

    template <typename T = void, typename L = void, typename R = void>
    class Subtracao : public OperacaoBinaria<T, L, R>{

        public:
            Subtracao(Nodo<L>* left, Nodo<R>* right) : OperacaoBinaria<T, L, R>(left, "subtracao", right){ }

        public:

            T executar(Contexto* contexto){
                return *(new T);
                // return left->executar(contexto) + right->executar(contexto);
            }

            static NodoFundamental instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
        struct createVisitor : public static_visitor<NodoFundamental>{
            string errorMessage = "operacao subtracao espera inteiro ou real mas recebeu ";

            NodoFundamental operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                NodoFundamental nodo;
                nodo = new Subtracao<int, int, int>(left, right);
                return nodo;
            }

            NodoFundamental operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                NodoFundamental nodo;
                nodo = new Subtracao<double, double, double>(left, right);
                return nodo;
            }

            NodoFundamental operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                NodoFundamental nodo;
                nodo = new Subtracao<double, double, int>(left, right);
                return nodo;
            }

            NodoFundamental operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                NodoFundamental nodo;
                nodo = new Subtracao<double, int, double>(left, right);
                return nodo;
            }

            template <typename V, typename W>
            NodoFundamental operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                throw new Erro(errorMessage + left->getTipo().getIdentificadorMasculino() + " e " + right->getTipo().getIdentificadorMasculino() + ".");
            }

            template<typename V>
            NodoFundamental operator()(Nodo<int>*& left, Nodo<V>*& right) const {
                throw new Erro(errorMessage + right->getTipo().getIdentificadorMasculino() + ".");
            }

            template<typename V>
            NodoFundamental operator()(Nodo<V>*& left, Nodo<int>*& right) const {
                throw new Erro(errorMessage + left->getTipo().getIdentificadorMasculino() + ".");
            }

            template<typename V>
            NodoFundamental operator()(Nodo<double>*& left, Nodo<V>*& right) const {
                throw new Erro(errorMessage + right->getTipo().getIdentificadorMasculino() + ".");
            }

            template<typename V>
            NodoFundamental operator()(Nodo<V>*& left, Nodo<double>*& right) const {
                throw new Erro(errorMessage + left->getTipo().getIdentificadorMasculino() + ".");
            }
        };
    };

    template<typename T>
    class Subtracao_unaria : public OperacaoUnaria<T> {
        public:
            Subtracao_unaria(Nodo<T>* nodo) : OperacaoUnaria<T>(nodo) { }

            void print(){
                cout << "((menos unario " << this->nodo->getTipo().getIdentificadorMasculino() <<") ";
                this->nodo->print();
                cout << ")";

            }

            T executar(Contexto* contexto){
                return this->nodo->executar(contexto);
            }
    };
}