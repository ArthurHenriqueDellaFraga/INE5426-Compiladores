#pragma once

#include "Contexto.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T>
  class Definicao;

  typedef Polimorfo<
      Definicao<int>*, Definicao<double>*,
      Definicao<bool>*,
      Definicao<char>*, Definicao<string>*
  > DefinicaoFundamental;

  template <typename T>
  class Definicao : public Nodo<void>{
      public:
          string tipo;
          string identificador;

          Definicao(string tipo, string identificador) : tipo(tipo), identificador(identificador){ }

          void print(){
              cout << tipo << ": " << identificador;
          }
          void executar(Contexto* contexto){
              VariavelFundamental variavel;
              variavel = new Variavel<T>(identificador);

              contexto->_variavel[identificador] = variavel;
          }

          static DefinicaoFundamental definir(string tipo, string identificador){
              map<string, DefinicaoFundamental(*)(string, string)> _definicao;
                _definicao["int"] = &getDefinicao<int>;
                _definicao["double"] = &getDefinicao<double>;
                _definicao["bool"] = &getDefinicao<bool>;
                _definicao["char"] = &getDefinicao<char>;
                _definicao["string"] = &getDefinicao<string>;

              return _definicao[tipo](tipo, identificador);
          }

      protected:
          template<typename U>
          static DefinicaoFundamental getDefinicao(string tipo, string identificador){
              DefinicaoFundamental definicao;
              definicao = new Definicao<U>(tipo, identificador);

              return definicao;
          };
  };
}
