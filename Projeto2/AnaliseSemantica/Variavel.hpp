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
              cout << " " << identificador;
          }

          string getIdentificador(){
              return identificador;
          }
  };

  // INSTANCIAÇÃO

  template <typename T>
  class Variavel : public VariavelAbstrata<T> {
      protected:
          T valor;
      public:
          Variavel(string identificador) : VariavelAbstrata<T>(identificador){ }

          void print(){
              cout << "variavel ";
              this->getTipo()->print();
              cout << " " << this->identificador << " -> " << this->valor;
          }

          T executar(Contexto* contexto){
              return this->valor;
          }

          Variavel& operator=(const T& valor){
              this->valor = valor;
              return *this;
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
              return boost::apply_visitor(getIdentificador_visitor(), *this);
          }

          template<typename U>
          VariavelPolimorfo& operator=(const Variavel<U>*& variavel){
              NodoPolimorfo<Variavel>::operator=(variavel);
              return *this;
          }

      protected:
          struct getIdentificador_visitor : public static_visitor<string>{
              template <typename V>
              string operator()(Variavel<V>*& variavel) const {
                  return variavel->getIdentificador();
              }
          };
  };

  typedef VariavelPolimorfo VariavelFundamental;

}
