#pragma once

#include "Erro.hpp"
#include "Polimorfo.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T = void>
  class NodoAbstrato {
      public:
          // virtual ~NodoAbstrato();
          virtual void print() = 0;
          virtual T executar(Contexto* contexto) = 0;

          Tipo<T>* getTipo(){
              return new Tipo<T>();
          }
  };

  template <typename T = void>
  class Nodo : public NodoAbstrato<T>{
      public:
          virtual T executar(Contexto* contexto) {
              return *(new T());
          }
  };

  typedef Polimorfo<
      Nodo<int>*, Nodo<double>*,
      Nodo<bool>*,
      Nodo<char>*, Nodo<string>*,
      Nodo<void>*
  > NodoFundamental;

  template<>
  class Nodo<void> : public NodoAbstrato<void>{
      public:
          virtual void executar(Contexto* contexto) { }

          template <typename U>
          static NodoFundamental* converter(U u){
              return apply_visitor(ConverterVisitor (), u);
          }

      protected:
          struct ConverterVisitor : public static_visitor<NodoFundamental*>{
              template <typename V>
              NodoFundamental* operator()(V& v) const {
                  return new NodoFundamental(v);
              }
          };
  };

}
