#pragma once

#include "../Bloco.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  //ABSTRAÇÃO

  template <typename T>
  class FuncaoAbstrata : public Nodo<T>{
      protected:
          string identificador;
          vector<DefinicaoFundamental*> argumentos;
          Bloco* bloco;

          FuncaoAbstrata(string identificador, vector<DefinicaoFundamental*> argumentos, Bloco* bloco)
          : identificador(identificador), argumentos(argumentos), bloco(bloco){ }

      public:
          void print(){
              cout << "Funcao ";
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
              cout << "fim da funcao" << endl;
          }

          string getIdentificador(){
              return identificador;
          }

          vector<DefinicaoFundamental*> getArgumentos(){
              return argumentos;
          }
  };

  //INSTANCIAÇÃO

  template <typename T>
  class Funcao : public FuncaoAbstrata<T>{
      public:
        Funcao(string identificador, vector<DefinicaoFundamental*> argumentos, Bloco* bloco)
        : FuncaoAbstrata<T>(identificador, argumentos, bloco){ }

        T executar(Contexto* contexto){
            try{
                this->bloco->executar(contexto);
            }
            catch(T retorno){
                return retorno;
            }

            return T();
        }
  };

  template <>
  class Funcao<void> : public FuncaoAbstrata<void>{
      public:
        Funcao(string identificador, vector<DefinicaoFundamental*> argumentos, Bloco* bloco)
        : FuncaoAbstrata<void>(identificador, argumentos, bloco){ }

        void executar(Contexto* contexto){
            this->bloco->executar(contexto);
        }
  };

  // POLIMORFISMO

  class FuncaoPolimorfo : public NodoPolimorfo<Funcao>{
      public:
          template <typename U>
          FuncaoPolimorfo(Funcao<U>* funcao) : NodoPolimorfo<Funcao>(funcao){ }

          static FuncaoPolimorfo* instanciar(TipoFundamental* tipo, string identificador, vector<DefinicaoFundamental*> argumentos, Bloco* bloco){
              create_visitor create;
              create.identificador = identificador;
              create.argumentos = argumentos;
              create.bloco = bloco;
              return boost::apply_visitor(create, *tipo);
          }

      protected:
        struct create_visitor : public static_visitor<FuncaoPolimorfo*>{
            string identificador;
            vector<DefinicaoFundamental*> argumentos;
            Bloco* bloco;

            template <typename V>
            FuncaoPolimorfo* operator()(Tipo<V>*& tipo) const {
                return new FuncaoPolimorfo(new Funcao<V>(identificador, argumentos, bloco));
            }
        };
  };

  typedef FuncaoPolimorfo FuncaoFundamental;

}
