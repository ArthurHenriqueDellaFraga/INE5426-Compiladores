#pragma once

#include "Operacao.hpp"
#include "../Contexto.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename L, typename R>
    class OperacaoBinariaBooleana : public OperacaoBinaria<bool, L, R> {
        protected:
            OperacaoBinariaBooleana(Nodo<L>* left, string simbolo, Nodo<R>* right) : OperacaoBinaria<bool, L, R>(left, simbolo, right) { }
        public:
            bool executar(Contexto* contexto){
                // return left->executar(contexto) != right->executar(contexto);
                return true;
            }
    };

    template <typename L = void, typename R = void>
    class Igual : public OperacaoBinariaBooleana<L, R>{
        public:
            Igual(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "=", right){ }

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
            Diferente(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "~=", right){ }

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
            Maior(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, ">", right){ }

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
            Menor(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "<", right){ }

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
            MaiorIgual(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, ">=", right){ }

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
            MenorIgual(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "<=", right){ }

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
}
