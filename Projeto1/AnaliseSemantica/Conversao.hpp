#pragma once

#include "AnaliseSemantica.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T, typename U = T>
  class Conversao : public Nodo<T>{
      public:
          Tipo<T>* tipo;
          Nodo<U>* valor;

          Conversao(Tipo<T>* tipo, Nodo<U>* valor) : tipo(tipo), valor(valor){
              static_assert(std::is_convertible<T, U>::value, "Conversão inválida");
          }

          void print(){
              valor->print();
          }
          T executar(Contexto* contexto){
              return *(new T(valor->executar(contexto)));
          }

          static NodoFundamental instanciar(TipoFundamental tipo, NodoFundamental valor){
              return apply_visitor(ConversaoVisitor(), tipo, valor);
          }

      protected:
        struct ConversaoVisitor : public static_visitor<NodoFundamental>{
            template <typename V, typename W>
            NodoFundamental operator()(Tipo<V>*& tipo, Nodo<W>* valor) const {
                throw new string("Tipos Incompativeis");
            }

            template <typename V>
            NodoFundamental operator()(Tipo<V>*& tipo, Nodo<V>* valor) const {
                NodoFundamental nodo;
                nodo = new Conversao<V>(tipo, valor);
                return nodo;
            }
        };
  };

}
