#pragma once

#include "Nodo.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // ABSTRAÇÃO

  template <typename T>
  class VariavelAbstrata : public Nodo<T> {
      protected:
          string identificador;
      public:
          VariavelAbstrata(string identificador) : identificador(identificador){ }

          void print(){
              cout << "variavel ";
              this->getTipo()->print();
              cout << " "<< identificador;
          }

          string getIdentificador(){
              return identificador;
          }

          virtual void setReferencia(){

          }
  };

  // INSTANCIAÇÃO

  template <typename T>
  class Variavel : public VariavelAbstrata<T> {
      protected:
          T valor;
      public:
          Variavel(string identificador) : VariavelAbstrata<T>(identificador){ }

          T executar(Contexto* contexto){
              return this->valor;
          }
  };

  template <>
  class Variavel<void> : public VariavelAbstrata<void> {
      public:
          Variavel(string identificador) : VariavelAbstrata<void>(identificador){ }

          void executar(Contexto* contexto){
              //ERROR ?
          }
  };

  // POLIMORFISMO

  class VariavelPolimorfo : public NodoPolimorfo<Variavel>{
      public:
          template<typename U>
          VariavelPolimorfo(Variavel<U>* variavel) : NodoPolimorfo<Variavel>(variavel){ }

          string getIdentificador(){
              return apply_visitor(getIdentificadorVisitor (), *this);
          }

          template<typename U>
          VariavelPolimorfo& operator=(const Variavel<U>*& variavel){
              NodoPolimorfo<Variavel>::operator=(variavel);
              return *this;
          }

      protected:
          struct getIdentificadorVisitor : public static_visitor<string>{
              template <typename V>
              string operator()(Variavel<V>*& variavel) const {
                  return variavel->getIdentificador();
              }
          };
  };

  typedef VariavelPolimorfo VariavelFundamental;

}
