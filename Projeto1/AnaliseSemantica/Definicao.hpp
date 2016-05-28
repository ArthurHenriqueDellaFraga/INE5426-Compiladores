#pragma once

#include "Contexto.hpp"
#include "Tipo.hpp"

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

  template <typename T = void>
  class Definicao : public Nodo<void>{
      public:
          Tipo<T>* tipo;
          string identificador;

          Definicao(Tipo<T>* tipo, string identificador) : tipo(tipo), identificador(identificador){ }

          void print(){
              tipo->print();
              cout << " " << identificador;
          }
          void executar(Contexto* contexto){
              VariavelFundamental variavel;
              variavel = new Variavel<T>(identificador);

              contexto->_variavel[identificador] = variavel;
          }

          static DefinicaoFundamental instanciar(TipoFundamental tipo, string identificador){
              createVisitor visitor;
              visitor.identificador = identificador;
              return apply_visitor(visitor, tipo);
          }

      protected:
        struct createVisitor : public static_visitor<DefinicaoFundamental>{
            string identificador;

            template <typename U>
            DefinicaoFundamental operator()(Tipo<U>*& tipo) const {

                DefinicaoFundamental definicao;
                definicao = new Definicao<U>(tipo, identificador);
                return definicao;
            }
        };
  };
}
