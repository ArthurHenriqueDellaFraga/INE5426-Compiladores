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

          Tipo() : identificador("void"){}

          void print(){
              cout << identificador << ":";
          }
          void executar(Contexto* contexto){
              // return new T();
          };

          static TipoFundamental instanciar(string identificador){
              map<string, TipoFundamental(*)()> _tipo;
                _tipo["int"] = &createTipo<int>;
                _tipo["double"] = &createTipo<double>;
                _tipo["bool"] = &createTipo<bool>;
                _tipo["char"] = &createTipo<char>;
                _tipo["string"] = &createTipo<string>;

                return _tipo[identificador]();
          }

      protected:
          template <typename U>
          static TipoFundamental createTipo(){
              TipoFundamental tipo;
              tipo = new Tipo<U>();
              return tipo;
          }
  };

  template<>
  class Tipo<int> : public Nodo<int>{
      public:
          string identificador = "inteiro";

          Tipo() {}

          void print(){
              cout << "valor " << identificador << " ";
          }
          int executar(Contexto* contexto){
              return *(new int());
          };
  };

  template<>
  class Tipo<double> : public Nodo<double>{
      public:
          string identificador = "real";

          Tipo() {}

          void print(){
              cout << "valor " << identificador << " ";
          }
          double executar(Contexto* contexto){
              return *(new double());
          };
  };

  template<>
  class Tipo<bool> : public Nodo<bool>{
      public:
          string identificador = "boolean";

          Tipo() {}

          void print(){
              cout << "valor " << identificador << " ";
          }
          bool executar(Contexto* contexto){
              return *(new bool());
          };
  };

  template<>
  class Tipo<char> : public Nodo<char>{
      public:
          string identificador = "char";

          Tipo() {}

          void print(){
              cout << identificador << " ";
          }
          char executar(Contexto* contexto){
              return *(new char());
          };
  };

  template<>
  class Tipo<string> : public Nodo<string>{
      public:
          string identificador = "string";

          Tipo() {}

          void print(){
              cout << identificador << " ";
          }
          string executar(Contexto* contexto){
              return *(new string());
          };
  };

}
