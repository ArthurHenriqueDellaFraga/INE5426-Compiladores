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
              cout << "arranjo " << this->getTipo()->getIdentificadorMasculino();
          }

          T executar(Contexto* contexto){
              return *(new T);
          }

          string getIdentificador(){
            return identificador;
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
              cout << "variavel " << this->getTipo()->getIdentificadorFeminino() << " "<< identificador;
          }

          void executar(Contexto* contexto){ }

          string getIdentificador(){
            return identificador;
          }
  };

  typedef Polimorfo<
      Arranjo<int>*, Arranjo<double>*,
      Arranjo<bool>*,
      Arranjo<char>*, Arranjo<string>*,
      Arranjo<void>*
  > ArranjoFundamental;

  struct ArranjoDto {
      public:
          string identificador;
          NodoFundamental tamanho;
  };

}
