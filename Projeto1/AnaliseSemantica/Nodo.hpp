#pragma once

#include "Geral/Erro.hpp"
#include "Tipo.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  class Contexto;

  // ABSTRAÇÃO

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

  // INSTANCIAÇÃO

  template <typename T = void>
  class Nodo : public NodoAbstrato<T>{
      public:
          virtual T executar(Contexto* contexto) {
              return *(new T());
          }
  };

  template<>
  class Nodo<void> : public NodoAbstrato<void>{
      public:
          virtual void executar(Contexto* contexto) { }
  };

  // POLIMORFISMO

  template <template <typename> class T = Nodo>
  class NodoPolimorfo : public Polimorfo<T>{
      public:
          template <typename U>
          NodoPolimorfo(T<U>* nodo) : Polimorfo<T>(nodo){
              //static_assert(is_base_of<Nodo, T>::value, "NodoPolimorfo :: construtor")
          }

          void print(){
              apply_visitor(print_visitor (), *this);
          }

          void executar(Contexto* contexto){
              executar_visitor executar;
              executar.contexto = contexto;
              apply_visitor(executar, *this);
          }

          TipoFundamental getTipo(){
              return apply_visitor(getTipo_visitor (), *this);
          }

          template<typename U>
          NodoPolimorfo<T>& operator=(const T<U>*& nodo){
              Polimorfo<T>::operator=(nodo);
              return *this;
          }

          template <typename U>
          static NodoPolimorfo<T>* converter(U u){
              //static_assert(is_base_of<T, U>::value, "NodoPolimorfo :: converter")
              return apply_visitor(converter_visitor (), u);
          }

      protected:
          struct converter_visitor : public static_visitor<NodoPolimorfo<T>*>{
              template <typename V>
              NodoPolimorfo<T>* operator()(V& v) const {
                  return new NodoPolimorfo<T>(v);
              }
          };

          struct print_visitor : public static_visitor<void> {
              template <typename V>
              void operator()(V v) const {
                  v->print();
              }
          };

          struct executar_visitor : public static_visitor<void> {
              Contexto* contexto;

              template <typename V>
              void operator()(V v) const {
                  v->executar(contexto);
              }
          };

          struct getTipo_visitor : public static_visitor<TipoFundamental> {
              template <typename V>
              TipoFundamental operator()(V v) const {
                  TipoFundamental* tipo= new TipoFundamental(v->getTipo());
                  return *tipo;
              }
          };
  };

  typedef NodoPolimorfo<Nodo> NodoFundamental;
}
