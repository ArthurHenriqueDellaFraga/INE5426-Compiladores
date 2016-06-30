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
                cout << " (" << this->simbolo << " " << this->getTipo()->getIdentificadorMasculino() << ") ";
                this->right->print();
                cout << ")";
            }

            bool executar(Contexto* contexto){
                return true;
            }
    };

    template <typename L = void, typename R = L>
    class Igual : public OperacaoBinariaBooleana<L, R>{
        public:
            Igual(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "igual", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                string mensagemDeErro = "operacao Igual espera inteiro ou real mas recebeu ";

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                    return new Igual<int>(left, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                    return new Igual<double>(left, right);
                }

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(left);
                    return new Igual<double>(conversao, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(right);
                    return new Igual<double>(left, conversao);
                }



                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + " e " + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Igual<V, W>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Igual<int, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<int>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Igual<V, int>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Igual<double, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<double>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Igual<V, double>(left, right);
                }
            };
    };

    template <typename L = void, typename R = L>
    class Diferente : public OperacaoBinariaBooleana<L, R>{
        public:
            Diferente(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "diferente", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                string mensagemDeErro = "operacao Diferente espera inteiro ou real mas recebeu ";

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                    return new Diferente<int>(left, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                    return new Diferente<double>(left, right);
                }

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(left);
                    return new Diferente<double>(conversao, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(right);
                    return new Diferente<double>(left, conversao);
                }



                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + " e " + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Diferente<V, W>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Diferente<int, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<int>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Diferente<V, int>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Diferente<double, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<double>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Diferente<V, double>(left, right);
                }
            };
    };

    template <typename L = void, typename R = L>
    class Maior : public OperacaoBinariaBooleana<L, R>{
        public:
            Maior(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "maior", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                string mensagemDeErro = "operacao Maior espera inteiro ou real mas recebeu ";

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                    return new Maior<int>(left, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                    return new Maior<double>(left, right);
                }

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(left);
                    return new Maior<double>(conversao, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(right);
                    return new Maior<double>(left, conversao);
                }



                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + " e " + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Maior<V, W>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Maior<int, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<int>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Maior<V, int>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Maior<double, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<double>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Maior<V, double>(left, right);
                }
            };
    };

    template <typename L = void, typename R = L>
    class Menor : public OperacaoBinariaBooleana<L, R>{
        public:
            Menor(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "menor", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                string mensagemDeErro = "operacao Menor espera inteiro ou real mas recebeu ";

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                    return new Menor<int>(left, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                    return new Menor<double>(left, right);
                }

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(left);
                    return new Menor<double>(conversao, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(right);
                    return new Menor<double>(left, conversao);
                }



                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + " e " + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Menor<V, W>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Menor<int, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<int>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Menor<V, int>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Menor<double, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<double>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Menor<V, double>(left, right);
                }
            };
    };

    template <typename L = void, typename R = L>
    class MaiorIgual : public OperacaoBinariaBooleana<L, R>{
        public:
            MaiorIgual(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "maior igual", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                string mensagemDeErro = "operacao MaiorIgual espera inteiro ou real mas recebeu ";

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                    return new MaiorIgual<int>(left, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                    return new MaiorIgual<double>(left, right);
                }

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(left);
                    return new MaiorIgual<double>(conversao, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(right);
                    return new MaiorIgual<double>(left, conversao);
                }



                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + " e " + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new MaiorIgual<V, W>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new MaiorIgual<int, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<int>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new MaiorIgual<V, int>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new MaiorIgual<double, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<double>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new MaiorIgual<V, double>(left, right);
                }
            };
    };

    template <typename L = void, typename R = L>
    class MenorIgual : public OperacaoBinariaBooleana<L, R>{
        public:
            MenorIgual(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "menor igual", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                string mensagemDeErro = "operacao MenorIgual espera inteiro ou real mas recebeu ";

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                    return new MenorIgual<int>(left, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                    return new MenorIgual<double>(left, right);
                }

                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(left);
                    return new MenorIgual<double>(conversao, right);
                }

                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(right);
                    return new MenorIgual<double>(left, conversao);
                }



                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + " e " + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new MenorIgual<V, W>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<int>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new MenorIgual<int, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<int>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new MenorIgual<V, int>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<double>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new MenorIgual<double, V>(left, right);
                }

                template<typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<double>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new MenorIgual<V, double>(left, right);
                }
            };
    };


    template <typename L = void, typename R = L>
    class Or : public OperacaoBinariaBooleana<L, R>{
        public:
            Or(Nodo<L>* left, Nodo<R>* right) : OperacaoBinariaBooleana<L, R>(left, "or", right){ }

            static Nodo<bool>* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                string mensagemDeErro = "operacao Or espera booleano mas recebeu ";

                Nodo<bool>* operator()(Nodo<bool>*& left, Nodo<bool>*& right) const {
                    return new Or<bool, bool>(left, right);
                }



                template <typename V, typename W>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + " e " + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Or<V, W>(left, right);
                }

                template <typename V>
                Nodo<bool>* operator()(Nodo<bool>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Or<bool, V>(left, right);
                }

                template <typename V>
                Nodo<bool>* operator()(Nodo<V>*& left, Nodo<bool>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new Or<V, bool>(left, right);
                }
            };
    };

    template <typename T = void>
    class NegacaoBooleana : public OperacaoUnaria<bool, T> {
        public:
            NegacaoBooleana(Nodo<T>* nodo) : OperacaoUnaria<bool, T>(nodo) { }

            void print(){
                cout << "((negacao booleana) ";
                this->nodo->print();
                cout << ")";

            }

            static Nodo<bool>* instanciar(NodoFundamental nodo) {
                return apply_visitor(createVisitor (), nodo);
            }

        protected:
            struct createVisitor : public static_visitor<Nodo<bool>*>{
                string mensagemDeErro = "operacao NegacaoBooleana espera booleano mas recebeu ";

                Nodo<bool>* operator()(Nodo<bool>*& nodo) const {
                    return new NegacaoBooleana<bool>(nodo);
                }



                template <typename V>
                Nodo<bool>* operator()(Nodo<V>*& nodo) const {
                    Erro* erro = new Erro(mensagemDeErro + nodo->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NegacaoBooleana<V>(nodo);
                }
            };
    };
}
