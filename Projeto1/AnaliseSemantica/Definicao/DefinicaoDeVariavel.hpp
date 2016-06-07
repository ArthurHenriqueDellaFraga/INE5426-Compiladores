#pragma once

#include "Definicao.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename U>
  class DefinicaoDeVariavel : public DefinicaoAbstrata<Variavel, U>{
      public:
          Definicao(string identificador) : DefinicaoAbstrata<Variavel, U>(identificador){ }

          void executar(){
              VariavelFundamental* variavel = new VariavelFundamental(new Variavel<U>(identificador));
              contexto->put(identificador, variavel);
          }
  };

  class DefinicaoDeVariavelPolimorfo : public NodoPolimorfo<Definicao>{
      public:
          static DefinicaoFundamental* instanciar(TipoFundamental tipo, string identificador){
              createVisitor visitor;
              visitor.identificador = identificador;
              return apply_visitor(visitor, tipo);
          }

      protected:
        struct createVisitor : public static_visitor<DefinicaoFundamental*>{
            string identificador;

            template <typename V>
            DefinicaoFundamental* operator()(Tipo<V>*& tipo) const {
                return new DefinicaoFundamental(new Definicao<V>(tipo, identificador));
            }
        };
  };
