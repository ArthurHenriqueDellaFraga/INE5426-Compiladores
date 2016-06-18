#pragma once

#include "Definicao.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T>
  class Definicao : public Nodo<void>{
      public:
          vector<string> listaDeIdentificador;

          Definicao(string identificador) {
              add(identificador);
          }

          void print(){
              cout << "Declaracao de variavel ";
              (new Tipo<T>())->print();
              cout << ": ";
              cout << listaDeIdentificador[0];
              for(int i = 1; i < listaDeIdentificador.size(); i++){
                  cout << ", " << listaDeIdentificador[i];
              }
          }

          void executar(Contexto* contexto){
              for(int i = 0; i < listaDeIdentificador.size(); i++){
                  string identificador = listaDeIdentificador[i];
                  VariavelFundamental* variavel = new VariavelFundamental(new Variavel<T>(identificador));
                  contexto->put(identificador, variavel);
              }
          }

          void add(string identificador){
              listaDeIdentificador.push_back(identificador);
          }
  };

  class DefinicaoPolimorfo : public NodoPolimorfo<Definicao>{
      public:
          template <typename U>
          DefinicaoPolimorfo(Definicao<U>* definicao) : NodoPolimorfo<Definicao>(definicao){ }

          void add(string identificador){
              add_visitor add;
              add.identificador = identificador;
              boost::apply_visitor(add, *this);

          }

          static DefinicaoPolimorfo* instanciar(TipoPolimorfo tipo, string identificador){
              create_visitor create;
              create.identificador = identificador;
              return boost::apply_visitor(create, tipo);
          }

      protected:
        struct create_visitor : public static_visitor<DefinicaoPolimorfo*>{
            string identificador;

            template <typename V>
            DefinicaoPolimorfo* operator()(Tipo<V>*& tipo) const {
                return new DefinicaoPolimorfo(new Definicao<V>(identificador));
            }
        };

        struct add_visitor : public static_visitor<DefinicaoPolimorfo*>{
            string identificador;

            template <typename V>
            DefinicaoPolimorfo* operator()(Definicao<V>*& definicao) const {
                definicao->add(identificador);
            }
        };
  };

  typedef DefinicaoPolimorfo DefinicaoFundamental;

}
