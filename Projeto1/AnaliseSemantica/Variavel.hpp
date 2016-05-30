#pragma once

#include "Nodo.hpp"

using namespace std;

namespace AnaliseSemantica {

  template <typename T = void>
  class Variavel : public Nodo<T> {
      private:
          string identificador;
          T* referencia;
      public:
          Variavel(string identificador) : identificador(identificador), referencia(new T()){ }

          void print(){
              cout << "variavel " << this->getTipo()->getIdentificadorFeminino() << " "<< identificador;
          }

          T executar(Contexto* contexto){
              return *referencia;
          }

          void setReferencia(T* referencia){
              this->referencia = referencia;
          }
  };

  template <>
  class Variavel<void> : public Nodo<void> {
      private:
          string identificador;
      public:
          Variavel(string identificador) : identificador(identificador){ }

          void print(){
              cout << "variavel " << this->getTipo()->getIdentificadorFeminino() << " "<< identificador;
          }

          void executar(Contexto* contexto){ }

          // void setReferencia(T* referencia){ }
  };

  typedef Polimorfo<
      Variavel<int>*, Variavel<double>*,
      Variavel<bool>*,
      Variavel<char>*, Variavel<string>*,
      Variavel<void>*
  > VariavelFundamental;

}
