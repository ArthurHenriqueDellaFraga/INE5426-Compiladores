#pragma once

#include "Operacao.hpp"
#include "../Contexto.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename L, typename R>
    class OperacaoBooleana : public Operacao<bool, L, R> {
        protected:
            OperacaoBooleana(Nodo<L>* left, string simbolo, Nodo<R>* right) : Operacao<bool, L, R>(left, simbolo, right) { }
        public:
            bool executar(Contexto* contexto){
                // return left->executar(contexto) != right->executar(contexto);
                return true;
            }
    };

    template <typename L = void, typename R = void>
    class Igual : public OperacaoBooleana<L, R>{
        public:
            Igual(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<L, R>(left, "=", right){ }

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
    class Diferente : public OperacaoBooleana<L, R>{
        public:
            Diferente(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<L, R>(left, "~=", right){ }

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
    class Maior : public OperacaoBooleana<L, R>{
        public:
            Maior(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<L, R>(left, ">", right){ }

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
    class Menor : public OperacaoBooleana<L, R>{
        public:
            Menor(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<L, R>(left, "<", right){ }

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
    class MaiorIgual : public OperacaoBooleana<L, R>{
        public:
            MaiorIgual(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<L, R>(left, ">=", right){ }

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
    class MenorIgual : public OperacaoBooleana<L, R>{
        public:
            MenorIgual(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<L, R>(left, "<=", right){ }

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
