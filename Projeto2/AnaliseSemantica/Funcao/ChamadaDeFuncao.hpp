#pragma once

#include "Funcao.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T>
  class ChamadaDeFuncao : public Nodo<T>{
      protected:
          Funcao<T>* funcao;
          vector<NodoFundamental*> argumentos;
      public:
          ChamadaDeFuncao(Funcao<T>* funcao, vector<NodoFundamental*> argumentos)
          : funcao(funcao), argumentos(argumentos){ }

          void print(){
              cout << "Chamada de funcao ";
              (new Tipo<T>())->print();
              cout << ": ";
              cout << funcao->getIdentificador() << endl;
              cout << "+argumentos:" << endl;
              for(int i = 0; i < argumentos.size(); i++){
                  argumentos[i]->print();
                  cout << endl;
              }
              cout << "fim da chamada de funcao" << endl;
          }

          T executar(Contexto* contexto){
              contexto = new Contexto(contexto);
              if(funcao->getArgumentos().size() == argumentos.size()){
                  try{
                      for(int i = 0; i < funcao->getArgumentos().size(); i++){
                          funcao->getArgumentos()[i]->executar(contexto);
                          AtribuicaoFundamental* atribuicao = AtribuicaoFundamental::instanciar(
                              contexto->getVariavel(funcao->getArgumentos()[i]->getListaDeIdentificador()[0]),
                              argumentos[i]
                          );
                          atribuicao->executar(contexto);
                      }
                  }
                  catch(Erro* e){
                      Erro* erro = new Erro("Tipos de argumentos incorretos");
                      erro->print();
                      throw erro;
                  }
              }
              else{
                  Erro* erro = new Erro("Número de argumentos incorreto");
                  erro->print();
                  throw erro;
              }
              return funcao->executar(contexto);
          }
  };

  // POLIMORFISMO

  class ChamadaDeFuncaoPolimorfo : public NodoPolimorfo<ChamadaDeFuncao>{
      public:
          template <typename U>
          ChamadaDeFuncaoPolimorfo(ChamadaDeFuncao<U>* chamada) : NodoPolimorfo<ChamadaDeFuncao>(chamada){ }

          static ChamadaDeFuncaoPolimorfo* instanciar(FuncaoFundamental* funcao, vector<NodoFundamental*> argumentos){
              create_visitor create;
              create.argumentos = argumentos;
              return boost::apply_visitor(create, *funcao);
          }

      protected:
        struct create_visitor : public static_visitor<ChamadaDeFuncaoPolimorfo*>{
            vector<NodoFundamental*> argumentos;

            template <typename V>
            ChamadaDeFuncaoPolimorfo* operator()(Funcao<V>*& funcao) const {
                return new ChamadaDeFuncaoPolimorfo(new ChamadaDeFuncao<V>(funcao, argumentos));
            }
        };
  };

  typedef ChamadaDeFuncaoPolimorfo ChamadaDeFuncaoFundamental;
}
