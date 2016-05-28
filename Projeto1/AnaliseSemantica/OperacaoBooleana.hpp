#pragma once

#include "Contexto.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename T, typename L, typename R>
    class OperacaoBooleana : public Nodo<T> {
        protected:
            Nodo<L>* left;
            string simbolo;
            Nodo<R>* right;
            OperacaoBooleana(Nodo<L>* left, string simbolo, Nodo<R>* right) : left(left), simbolo(simbolo), right(right) { }
        public:
            void print(){
                left->print();
                cout << " " << simbolo << " ";
                right->print();
            }

            bool executar(Contexto* contexto){
                // return left->executar(contexto) != right->executar(contexto);
                return true;
            }
    };

    template <typename L = void, typename R = void>
    class Igual : public OperacaoBooleana<bool, L, R>{
        public:
            Igual(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<bool, L, R>(left, "=", right){ }

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
    class Diferente : public OperacaoBooleana<bool, L, R>{
        public:
            Diferente(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<bool, L, R>(left, "~=", right){ }

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
    class Maior : public OperacaoBooleana<bool, L, R>{
        public:
            Maior(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<bool, L, R>(left, ">", right){ }

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
    class Menor : public OperacaoBooleana<bool, L, R>{
        public:
            Menor(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<bool, L, R>(left, "<", right){ }

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
    class MaiorIgual : public OperacaoBooleana<bool, L, R>{
        public:
            MaiorIgual(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<bool, L, R>(left, ">=", right){ }

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
    class MenorIgual : public OperacaoBooleana<bool, L, R>{
        public:
            MenorIgual(Nodo<L>* left, Nodo<R>* right) : OperacaoBooleana<bool, L, R>(left, "<=", right){ }

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
