#pragma once

#include "Operacao.hpp"

using namespace std;

namespace AnaliseSemantica {

    template <typename T = void, typename L = void, typename R = void>
    class Divisao : public OperacaoBinaria<T, L, R>{
        public:
            Divisao(Nodo<L>* left, Nodo<R>* right) : OperacaoBinaria<T, L, R>(left, "divisao", right){ }

            T executar(Contexto* contexto){
                return *(new T());
                // return left->executar(contexto) / right->executar(contexto);
            }

            static NodoFundamental* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<NodoFundamental*>{
                string mensagemDeErro = "operacao Divisao espera inteiro ou real mas recebeu ";

                NodoFundamental* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                    return new NodoFundamental(new Divisao<int, int, int>(left, right));
                }

                NodoFundamental* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                    return new NodoFundamental(new Divisao<double, double, double>(left, right));
                }

                NodoFundamental* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(right);
                    return new NodoFundamental(new Divisao<double, double, double>(left, conversao));
                }

                NodoFundamental* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(left);
                    return new NodoFundamental(new Divisao<double, double, double>(conversao, right));
                }



                template <typename V, typename W>
                NodoFundamental* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + " e " + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Divisao<int, V, W>(left, right));
                }

                template<typename V>
                NodoFundamental* operator()(Nodo<int>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Divisao<int, int, V>(left, right));
                }

                template<typename V>
                NodoFundamental* operator()(Nodo<V>*& left, Nodo<int>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Divisao<int, V, int>(left, right));
                }

                template<typename V>
                NodoFundamental* operator()(Nodo<double>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Divisao<double, double, V>(left, right));
                }

                template<typename V>
                NodoFundamental* operator()(Nodo<V>*& left, Nodo<double>*& right) const {
                    Erro* erro = new Erro(mensagemDeErro + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Divisao<double, V, double>(left, right));
                }
            };
    };
}
