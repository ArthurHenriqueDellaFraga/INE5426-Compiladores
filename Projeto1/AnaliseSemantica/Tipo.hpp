#pragma once

#include "AnaliseSemantica.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T>
  class Tipo;

  typedef Polimorfo<
      Tipo<int>*, Tipo<double>*,
      Tipo<bool>*,
      Tipo<char>*, Tipo<string>*
  > TipoFundamental;

  template <typename T = void>
  class Tipo : public Nodo<void>{
      public:
          string identificador;

          Tipo(string identificador) : identificador(identificador){}

          void print(){
              cout << identificador << ":";
          }
          void executar(Contexto* contexto){
              // return new T()
          };

          static TipoFundamental instanciar(string identificador){
              map<string, TipoFundamental(*)(string)> _tipo;
                _tipo["int"] = &createTipo<int>;
                _tipo["double"] = &createTipo<double>;
                _tipo["bool"] = &createTipo<bool>;
                _tipo["char"] = &createTipo<char>;
                _tipo["string"] = &createTipo<string>;

                return _tipo[identificador](identificador);
          }

      protected:
          template <typename U>
          static TipoFundamental createTipo(string identificador){
              TipoFundamental tipo;
              tipo = new Tipo<U>(identificador);
              return tipo;
          }
  };

}
