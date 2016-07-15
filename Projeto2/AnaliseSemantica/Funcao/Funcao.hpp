#pragma once

#include "../Bloco.hpp"

namespace AnaliseSemantica {

  template <typename T = void>
  class Funcao;

  typedef Polimorfo<
      Nodo<int>*, Nodo<double>*,
      Nodo<bool>*,
      Nodo<char>*, Nodo<string>*,
      Nodo<void>*
  > FuncaoFundamental;

  template <typename T>
  class Funcao : public Bloco<T>{
      public:
          vector<VariavelFundamental> listaDeArgumentos;

          Funcao(vector<VariavelFundamental> listaDeArgumentos, Contexto* contexto)
          : Bloco<T>(contexto), listaDeArgumentos(listaDeArgumentos){

          }

          Funcao(){}

  };

}
