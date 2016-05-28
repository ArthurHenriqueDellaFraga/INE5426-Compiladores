#pragma once

#include "AnaliseSemantica.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T>
  class Variavel : public Nodo<T> {
      private:
          string identificador;
          T* referencia;
      public:
          Variavel(string identificador) : identificador(identificador), referencia(new T()){ }

          void print(){
              cout << "variavel";
              cout << this->getTipo().getIdentificadorFeminino();
              cout << identificador;
          }
          T executar(Contexto* contexto){
              return *referencia;
          }

          void setReferencia(T* referencia){
              this->referencia = referencia;
          }
  };

  typedef Polimorfo<
      Variavel<int>*, Variavel<double>*,
      Variavel<bool>*,
      Variavel<char>*, Variavel<string>*
  > VariavelFundamental;

}
