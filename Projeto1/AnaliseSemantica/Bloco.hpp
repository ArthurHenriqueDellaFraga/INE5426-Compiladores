#pragma once

#include "Contexto.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T = void>
  class Bloco : public Nodo<T> {
      protected:
          vector<NodoFundamental> listaDeInstrucoes;
          Contexto* contexto;
      public:
          Bloco(Contexto* contexto) : contexto(contexto) { }

          virtual void print(){
              for(int i=0; i < listaDeInstrucoes.size(); i++){
                  listaDeInstrucoes[i].print();
                  cout << endl;
              }
          }
          void executar(Contexto* contexto){
              for(int i=0; i < listaDeInstrucoes.size(); i++){
                  listaDeInstrucoes[i].executar(contexto);
              }
          }

          virtual void addInstrucao(NodoFundamental instrucao){
              listaDeInstrucoes.push_back(instrucao);
              
              try{
                  instrucao.executar(contexto);
                  instrucao.print();
                  cout << endl;
              }
              catch(Erro* erro){
                  erro->print();
                  exit(1);
              }
          }

          Contexto* getContexto(){
              return contexto;
          }
  };

}
