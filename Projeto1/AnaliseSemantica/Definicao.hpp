#pragma once

#include "Definicao.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T>
  class Definicao : public Nodo<T>{
      public:
          string identificador;

          Definicao(string identificador) : identificador(identificador){ }

          void executar(Contexto* contexto){
              VariavelFundamental* variavel = new VariavelFundamental(new Variavel<T>(identificador));
              contexto->put(identificador, variavel);
          }
  };

  class DefinicaoPolimorfo : public Polimorfo<Definicao>{
      public:
          static DefinicaoPolimorfo* instanciar(TipoFundamental tipo, string identificador){
              createVisitor create;
              create.identificador = identificador;
              return apply_visitor(create, tipo);
          }

      protected:
        struct createVisitor : public static_visitor<DefinicaoPolimorfo*>{
            string identificador;

            template <typename V>
            DefinicaoPolimorfo* operator()(Tipo<V>*& tipo) const {
                return new DefinicaoPolimorfo(new Definicao<V>(tipo, identificador));
            }
        };
  };
