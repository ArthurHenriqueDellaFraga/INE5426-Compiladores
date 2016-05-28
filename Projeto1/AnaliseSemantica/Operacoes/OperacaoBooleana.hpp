#pragma once

#include "Operacao.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename L, typename R>
    class OperacaoBinariaBooleana : public OperacaoBinaria<bool, L, R> {
        protected:
            OperacaoBinariaBooleana(Nodo<L>* left, string simbolo, Nodo<R>* right) : OperacaoBinaria<bool, L, R>(left, simbolo, right) { }
        public:
            void print(){
                cout << "(";
                this->left->print();
                cout << " (" << this->simbolo << " " << this->getTipo().getIdentificadorMasculino() << ") ";
                this->right->print();
                cout << ")";
            }

            bool executar(Contexto* contexto){
                // return left->executar(contexto) != right->executar(contexto);
                return true;
            }
    };

    template <typename L = void, typename R = void>
    class Igual : public OperacaoBinariaBooleana<L, R>{
        public:
            Igual(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "igual", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    return new Igual<V, W>(left, right);
                }
            };
    };

    template <typename L = void, typename R = void>
    class Diferente : public OperacaoBinariaBooleana<L, R>{
        public:
            Diferente(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "diferente", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    return new Diferente<V, W>(left, right);
                }
            };
    };

    template <typename L = void, typename R = void>
    class Maior : public OperacaoBinariaBooleana<L, R>{
        public:
            Maior(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "maior", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    return new Maior<V, W>(left, right);
                }
            };
    };

    template <typename L = void, typename R = void>
    class Menor : public OperacaoBinariaBooleana<L, R>{
        public:
            Menor(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "menor", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    return new Menor<V, W>(left, right);
                }
            };
    };

    template <typename L = void, typename R = void>
    class MaiorIgual : public OperacaoBinariaBooleana<L, R>{
        public:
            MaiorIgual(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "maior igual", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    return new MaiorIgual<V, W>(left, right);
                }
            };
    };

    template <typename L = void, typename R = void>
    class MenorIgual : public OperacaoBinariaBooleana<L, R>{
        public:
            MenorIgual(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "menor igual", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    return new MenorIgual<V, W>(left, right);
                }
            };
    };

    template <typename L = void, typename R = void>
    class And : public OperacaoBinariaBooleana<L, R>{
        public:
            And(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "and", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                string errorMessage = "operacao and espera booleano mas recebeu ";

                Nodo<bool>* operator()(Nodo<bool>*& left, Nodo<bool>*& right) const {
                    return new And<bool, bool>(left, right);
                }

                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    throw new Erro(errorMessage + left->getTipo().getIdentificadorMasculino() + " e " + right->getTipo().getIdentificadorMasculino() + ".");
                }

                template <typename V>
                Nodo<bool>* operator()(Nodo<bool>*& left, Nodo<V>*& right) const {
                    throw new Erro(errorMessage + right->getTipo().getIdentificadorMasculino() + ".");
                }

                template <typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<bool>*& right) const {
                    throw new Erro(errorMessage + left->getTipo().getIdentificadorMasculino() + ".");
                }
            };
    };

    template <typename L = void, typename R = void>
    class Or : public OperacaoBinariaBooleana<L, R>{
        public:
            Or(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "or", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                string errorMessage = "operacao or espera booleano mas recebeu ";

                Nodo<bool>* operator()(Nodo<bool>*& left, Nodo<bool>*& right) const {
                    return new Or<bool, bool>(left, right);
                }

                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    throw new Erro(errorMessage + left->getTipo().getIdentificadorMasculino() + " e " + right->getTipo().getIdentificadorMasculino() + ".");
                }

                template <typename V>
                Nodo<bool>* operator()(Nodo<bool>*& left, Nodo<V>*& right) const {
                    throw new Erro(errorMessage + right->getTipo().getIdentificadorMasculino() + ".");
                }

                template <typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<bool>*& right) const {
                    throw new Erro(errorMessage + left->getTipo().getIdentificadorMasculino() + ".");
                }
            };
    };

    class Negacao_booleana : public OperacaoUnaria<bool> {
        public:
            Negacao_booleana(Nodo<bool>* nodo) : OperacaoUnaria<bool>(nodo) { }

            void print(){
                cout << "((negacao " << this->nodo->getTipo().getIdentificadorFeminino() <<") ";
                this->nodo->print();
                cout << ")";

            }

            bool executar(Contexto* contexto){
                return !this->nodo->executar(contexto);
            }
    };
}
