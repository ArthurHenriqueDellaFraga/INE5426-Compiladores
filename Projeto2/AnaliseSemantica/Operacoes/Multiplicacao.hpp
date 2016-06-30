#pragma once

#include "Operacao.hpp"

using namespace std;

namespace AnaliseSemantica {

  template <typename T, typename L, typename R>
  class Multiplicacao : public Operacao<T, L, R>{
      public:
          Multiplicacao(Nodo<L>* left, Nodo<R>* right) : Operacao<T, L, R>(left, "multiplicacao", right){ }

          T executar(Contexto* contexto){
              return (this->left->executar(contexto)) * (this->right->executar(contexto));
          }

          static NodoFundamental* instanciar(NodoFundamental* left, NodoFundamental* right){
              return apply_visitor(create_visitor(), *left, *right);
          }

      protected:
          struct create_visitor : public static_visitor<NodoFundamental*>{
              string mensagemDeErro = "operacao Multiplicacao espera int ou double mas recebeu outros";

              NodoFundamental* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                  return new NodoFundamental(new Multiplicacao<int, int, int>(left, right));
              }

              NodoFundamental* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                  return new NodoFundamental(new Multiplicacao<double, double, int>(left, right));
              }

              NodoFundamental* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                  return new NodoFundamental(new Multiplicacao<double, int, double>(left, right));
              }

              NodoFundamental* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                  return new NodoFundamental(new Multiplicacao<double, double, double>(left, right));
              }


              template <typename V, typename W>
              NodoFundamental* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                  throw new Erro(mensagemDeErro);
              }
          };
  };
}
