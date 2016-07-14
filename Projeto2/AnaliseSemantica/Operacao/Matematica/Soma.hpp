#pragma once

#include "../Operacao.hpp"

using namespace std;

namespace AnaliseSemantica {

  // INSTANCIAÇÃO

  template <typename T, typename ... U>
  class Soma : public Operacao<T, U...>{
      protected:
          Soma() : Operacao<T, U...>("soma"){ }
  };

  template <typename T>
  class Soma<T> : public Operacao<T, T>{
      public:
          Soma(Nodo<T>* nodo) : Operacao<T, T>(nodo, "soma"){ }

          T executar(Contexto* contexto){
              return (this->nodo->executar(contexto));
          }

          static NodoFundamental* instanciar(NodoFundamental* nodo){
              return apply_visitor(createVisitor(), *nodo);
          }

      protected:
          struct createVisitor : public static_visitor<NodoFundamental*>{
              string mensagemDeErro = "operacao Soma espera int ou double mas recebeu outro";

              NodoFundamental* operator()(Nodo<int>*& nodo) const {
                  return new NodoFundamental(new Soma<int>(nodo));
              }

              NodoFundamental* operator()(Nodo<double>*& nodo) const {
                  return new NodoFundamental(new Soma<double>(nodo));
              }


              template <typename V>
              NodoFundamental* operator()(Nodo<V>*& nodo) const {
                  throw new Erro(mensagemDeErro);
              }
          };
  };

  template <typename T, typename L, typename R>
  class Soma<T, L, R> : public Operacao<T, L, R>{
      public:
          Soma(Nodo<L>* left, Nodo<R>* right) : Operacao<T, L, R>(left, "soma", right){ }

          T executar(Contexto* contexto){
              return (this->left->executar(contexto)) + (this->right->executar(contexto));
          }

          static NodoFundamental* instanciar(NodoFundamental* left, NodoFundamental* right){
              return apply_visitor(create_visitor(), *left, *right);
          }

      protected:
          struct create_visitor : public static_visitor<NodoFundamental*>{
              string mensagemDeErro = "operacao Soma espera int ou double mas recebeu outros";

              NodoFundamental* operator()(Nodo<int>*& left, Nodo<int>*& right) const {
                  return new NodoFundamental(new Soma<int, int, int>(left, right));
              }

              NodoFundamental* operator()(Nodo<double>*& left, Nodo<int>*& right) const {
                  return new NodoFundamental(new Soma<double, double, int>(left, right));
              }

              NodoFundamental* operator()(Nodo<int>*& left, Nodo<double>*& right) const {
                  return new NodoFundamental(new Soma<double, int, double>(left, right));
              }

              NodoFundamental* operator()(Nodo<double>*& left, Nodo<double>*& right) const {
                  return new NodoFundamental(new Soma<double, double, double>(left, right));
              }


              template <typename V, typename W>
              NodoFundamental* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                  throw new Erro(mensagemDeErro);
              }
          };
  };
}
