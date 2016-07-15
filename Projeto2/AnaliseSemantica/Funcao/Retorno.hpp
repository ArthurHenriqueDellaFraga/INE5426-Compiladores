#pragma once

#include "../Nodo.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  //INSTANCIAÇÃO

  template <typename T>
  class Retorno : public Nodo<T>{
      protected:
          Nodo<T>* nodo;

      public:
          Retorno(Nodo<T>* nodo) : nodo(nodo) {}

          void print(){
              cout << "return ";
              nodo->print();
          }

          T executar(Contexto* contexto){
              throw (this->nodo->executar(contexto));
          }

          static NodoFundamental* instanciar(NodoFundamental* nodo){
              return boost::apply_visitor(create_visitor(), *nodo);
          }

      protected:
          struct create_visitor : public static_visitor<NodoFundamental*>{
              template <typename V>
              NodoFundamental* operator()(Nodo<V>*& nodo) const {
                  return new NodoFundamental(new Retorno<V>(nodo));
              }

              NodoFundamental* operator()(Nodo<void>*& nodo) const {
                  throw new Erro("Retorno inválido");
              }
          };

  };

  template <>
  class Retorno<void> : public Nodo<void>{
      protected:
          Nodo<void>* nodo;

      public:
          Retorno(Nodo<void>* nodo) : nodo(nodo) {}

          void print(){
              cout << "return ";
              nodo->print();
          }

          void executar(Contexto* contexto){
              throw new Erro("Retorno inválido");
          }
  };

}
