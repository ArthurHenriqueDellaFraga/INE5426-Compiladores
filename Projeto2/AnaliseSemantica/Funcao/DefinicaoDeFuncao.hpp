#pragma once

#include "../Definicao.hpp"
#include "Funcao.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T>
  class DefinicaoDeFuncao : public Nodo<void>{
      protected:
          string identificador;
          vector<DefinicaoFundamental*> argumentos;
          Bloco* bloco;
      public:
          DefinicaoDeFuncao(string identificador, vector<DefinicaoFundamental*> argumentos, Bloco* bloco)
          : identificador(identificador), argumentos(argumentos), bloco(bloco){ }

          DefinicaoDeFuncao(string identificador, vector<DefinicaoFundamental*> argumentos)
          : identificador(identificador), argumentos(argumentos), bloco(new Bloco()){ }

          void print(){
              cout << "Declaracao de funcao ";
              (new Tipo<T>())->print();
              cout << ": ";
              cout << identificador << endl;
              cout << "+argumentos:" << endl;
              for(int i = 0; i < argumentos.size(); i++){
                  argumentos[i]->print();
                  cout << endl;
              }

              cout << "+faz:" << endl;
              bloco->print();
              cout << "fim da declaracao de funcao" << endl;
          }

          void executar(Contexto* contexto){
              TipoFundamental* tipo = new TipoFundamental(new Tipo<T>());
              FuncaoFundamental* funcao = FuncaoFundamental::instanciar(tipo, identificador, argumentos, bloco);
              contexto->put(identificador, funcao);
          }

          void add(Bloco* bloco){
                this->bloco = bloco;
          }
  };

  // POLIMORFISMO

  class DefinicaoDeFuncaoPolimorfo : public NodoPolimorfo<DefinicaoDeFuncao>{
      public:
          template <typename U>
          DefinicaoDeFuncaoPolimorfo(DefinicaoDeFuncao<U>* definicao) : NodoPolimorfo<DefinicaoDeFuncao>(definicao){ }

          void add(Bloco* bloco){
              add_visitor add;
              add.bloco = bloco;
              boost::apply_visitor(add, *this);
          }

          static DefinicaoDeFuncaoPolimorfo* instanciar(TipoPolimorfo* tipo, string identificador, vector<DefinicaoFundamental*> argumentos){
              create_visitor create;
              create.identificador = identificador;
              create.argumentos = argumentos;
              return boost::apply_visitor(create, *tipo);
          }

      protected:
        struct create_visitor : public static_visitor<DefinicaoDeFuncaoPolimorfo*>{
            string identificador;
            vector<DefinicaoFundamental*> argumentos;

            template <typename V>
            DefinicaoDeFuncaoPolimorfo* operator()(Tipo<V>*& tipo) const {
                return new DefinicaoDeFuncaoPolimorfo(new DefinicaoDeFuncao<V>(identificador, argumentos, NULL));
            }
        };

        struct add_visitor : public static_visitor<void>{
            Bloco* bloco;

            template <typename V>
            void operator()(DefinicaoDeFuncao<V>* definicao) const {
                definicao->add(bloco);
            }
        };
  };

  typedef DefinicaoDeFuncaoPolimorfo DefinicaoDeFuncaoFundamental;

}
