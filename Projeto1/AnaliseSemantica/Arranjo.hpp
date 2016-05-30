#pragma once

#include "Nodo.hpp"

using namespace std;

namespace AnaliseSemantica {

  template <typename T = void>
  class Arranjo : public Nodo<T> {
      private:
          string identificador;
          int tamanho;

      public:
          Arranjo(string identificador, int tamanho) : identificador(identificador), tamanho(tamanho){ }

          void print(){
              cout << "arranjo " << this->getTipo().getIdentificadorMasculino();
          }

          T executar(Contexto* contexto){
              return *(new T);
          }
  };

  template <>
  class Arranjo<void> : public Nodo<void> {
      private:
          string identificador;
          int tamanho;

      public:
          Arranjo(string identificador, int tamanho) : identificador(identificador), tamanho(tamanho){ }

          void print(){
              cout << "variavel " << this->getTipo().getIdentificadorFeminino() << " "<< identificador;
          }

          void executar(Contexto* contexto){ }
  };

  typedef Polimorfo<
      Arranjo<int>*, Arranjo<double>*,
      Arranjo<bool>*,
      Arranjo<char>*, Arranjo<string>*,
      Arranjo<void>*
  > ArranjoFundamental;

}
