#pragma once

#include "../Bloco.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // INSTANCIAÇÃO

  class Repeat : public Nodo<void> {
      public:
          Nodo<int>* quantidade;
          Bloco* bloco;

          Repeat(Nodo<int>* quantidade, Bloco* bloco)
          : quantidade(quantidade), bloco(bloco){ }

          void print(){
              cout << "Expressao condicional" << endl;
              cout << "+repetir: ";
              quantidade->print();
              cout << " vezes:" << endl;

              bloco->print();

              cout << "Fim expressao condicional";
          }

          void executar(Contexto* contexto){
              for(int i = 0; i < this->quantidade->executar(contexto); i++){
                  bloco->executar(contexto);
              }
          }

          static NodoFundamental* instanciar(NodoFundamental* quantidade, Bloco* bloco){
              create_visitor create;
              create.bloco = bloco;
              return apply_visitor(create, *quantidade);
          }

      protected:
          struct create_visitor : public static_visitor<NodoFundamental*>{
              Bloco* bloco;

              NodoFundamental* operator()(Nodo<int>* quantidade) const {
                  return new NodoFundamental(new Repeat(quantidade, bloco));
              }

              template <typename V>
              NodoFundamental* operator()(Nodo<V>* condicao) const {
                  throw new Erro("operacao Repeat espera int mas recebeu outro");
              }
          };
  };

}
