#pragma once

#include "Operacao.hpp"

using namespace std;

namespace AnaliseSemantica {

    template <typename T = int, typename L = void, typename R = void>
    class Multiplicacao : public OperacaoBinaria<T, L, R>{
        public:
            Multiplicacao(Nodo<L>* left, Nodo<R>* right) : OperacaoBinaria<T, L, R>(left, "multiplicacao", right){ }

            T executar(Contexto* contexto){
                return *(new T());
                // return left->executar(contexto) * right->executar(contexto);
            }

            static NodoFundamental* instanciar(NodoFundamental left, NodoFundamental right){
                return apply_visitor(createVisitor (), left, right);
            }

        protected:
            struct createVisitor : public static_visitor<NodoFundamental*>{
                string errorMessage = "operacao Multiplicacao espera inteiro ou real mas recebeu ";

                NodoFundamental* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                    return new NodoFundamental(new Multiplicacao<int, int, int>(left, right));
                }

                NodoFundamental* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                    return new NodoFundamental(new Multiplicacao<double, double, double>(left, right));
                }

                NodoFundamental* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(right);
                    return new NodoFundamental(new Multiplicacao<double, double, double>(left, conversao));
                }

                NodoFundamental* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                    Nodo<double>* conversao = new Conversao<double, int>(left);
                    return new NodoFundamental(new Multiplicacao<double, double, double>(conversao, right));
                }



                template <typename V, typename W>
                NodoFundamental* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                    Erro* erro = new Erro(errorMessage + left->getTipo()->getIdentificadorMasculino() + " e " + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Multiplicacao<int, V, W>(left, right));
                }

                template<typename V>
                NodoFundamental* operator()(Nodo<int>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(errorMessage + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Multiplicacao<int, int, V>(left, right));
                }

                template<typename V>
                NodoFundamental* operator()(Nodo<V>*& left, Nodo<int>*& right) const {
                    Erro* erro = new Erro(errorMessage + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Multiplicacao<int, V, int>(left, right));
                }

                template<typename V>
                NodoFundamental* operator()(Nodo<double>*& left, Nodo<V>*& right) const {
                    Erro* erro = new Erro(errorMessage + right->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Multiplicacao<double, double, V>(left, right));
                }

                template<typename V>
                NodoFundamental* operator()(Nodo<V>*& left, Nodo<double>*& right) const {
                    Erro* erro = new Erro(errorMessage + left->getTipo()->getIdentificadorMasculino() + ".");
                    erro->print();
                    return new NodoFundamental(new Multiplicacao<double, V, double>(left, right));
                }
            };
    };
}
