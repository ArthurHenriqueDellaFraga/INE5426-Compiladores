#pragma once

#include "Operacao.hpp"

using namespace std;

namespace AnaliseSemantica {

    template <typename T = int, typename L = void, typename R = void>
    class Subtracao : public OperacaoBinaria<T, L, R>{

        public:
            Subtracao(Nodo<L>* left, Nodo<R>* right) : OperacaoBinaria<T, L, R>(left, "subtracao", right){ }

            T executar(Contexto* contexto){
                return *(new T);
                // return left->executar(contexto) + right->executar(contexto);
            }

            static NodoFundamental* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<NodoFundamental*>{
                string mensagemDeErro = "operacao Subtracao espera inteiro ou real mas recebeu ";

                NodoFundamental* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                    return new NodoFundamental(new Subtracao<int, int, int>(left, right));
                }

                NodoFundamental* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                    return new NodoFundamental(new Subtracao<double, double, double>(left, right));
                }

                NodoFundamental* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(right);
                    return new NodoFundamental(new Subtracao<double, double, double>(left, conversao));
                }

                NodoFundamental* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(left);
                    return new NodoFundamental(new Subtracao<double, double, double>(conversao, right));
                }



                template <typename V, typename W>
                NodoFundamental* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + " e " + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Subtracao<int, V, W>(left, right));
                }

                template <typename V>
                NodoFundamental* operator()(Nodo<int>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Subtracao<int, int, V>(left, right));
                }

                template <typename V>
                NodoFundamental* operator()(Nodo<V>*& left, Nodo<int>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Subtracao<int, V, int>(left, right));
                }

                template <typename V>
                NodoFundamental* operator()(Nodo<double>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Subtracao<double, double, V>(left, right));
                }

                template <typename V>
                NodoFundamental* operator()(Nodo<V>*& left, Nodo<double>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Subtracao<double, V, double>(left, right));
                }
            };
    };

    template <typename T = int, typename N = void>
    class SubtracaoUnaria : public OperacaoUnaria<T, N> {
        public:
            SubtracaoUnaria(Nodo<N>* nodo) : OperacaoUnaria<T, N>(nodo) { }

            void print(){
                cout << "((menos unario " << this->getTipo()->getIdentificadorMasculino() <<") ";
                this->nodo->print();
                cout << ")";
            }

            static NodoFundamental* instanciar(NodoFundamental nodo){
                return apply_visitor(createVisitor (), nodo);
            }

        protected:
            struct createVisitor : public static_visitor<NodoFundamental*>{
                string mensagemDeErro = "operacao SubtracaoUnaria espera inteiro ou real mas recebeu ";

                NodoFundamental* operator()(Nodo<int>*& nodo) const {
                    return new NodoFundamental(new SubtracaoUnaria<int, int>(nodo));
                }

                NodoFundamental* operator()(Nodo<double>*& nodo) const {
                    return new NodoFundamental(new SubtracaoUnaria<double, double>(nodo));
                }

                template <typename V>
                NodoFundamental* operator()(Nodo<V>*& nodo) const {
                    Erro* erro = new Erro(mensagemDeErro + nodo->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new SubtracaoUnaria<int, V>(nodo));
                }
            };

    };
}
