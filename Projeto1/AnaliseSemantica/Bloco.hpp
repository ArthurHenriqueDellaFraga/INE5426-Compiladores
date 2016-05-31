#pragma once

#include "Contexto.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  class Bloco : public Nodo<void> {
      protected:
          vector<NodoFundamental> listaDeInstrucoes;
          Contexto* contexto;
      public:
          Bloco(Contexto* contexto) : contexto(contexto), Nodo() { }

          void print(){
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

          void addInstrucao(NodoFundamental instrucao){
              listaDeInstrucoes.push_back(instrucao);
              cout << endl;
              try{
                  instrucao.executar(contexto);
                  instrucao.print();
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
