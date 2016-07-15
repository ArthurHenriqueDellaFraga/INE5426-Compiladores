#pragma once

#include "../Bloco.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // INSTANCIAÇÃO

  class While : public Nodo<void> {
      public:
          Nodo<bool>* condicao;
          Bloco* bloco;

          While(Nodo<bool>* condicao, Bloco* bloco)
          : condicao(condicao), bloco(bloco){ }

          void print(){
              cout << "Expressao condicional" << endl;
              cout << "+enquanto: ";
              condicao->print();
              cout << endl;

              cout << "+faz:" << endl;
              bloco->print();

              cout << "Fim expressao condicional";
          }

          void executar(Contexto* contexto){
              while(this->condicao->executar(contexto)){
                  bloco->executar(contexto);
              }
          }

          static NodoFundamental* instanciar(NodoFundamental* condicao, Bloco* bloco){
              create_visitor create;
              create.bloco = bloco;
              return apply_visitor(create, *condicao);
          }

      protected:
          struct create_visitor : public static_visitor<NodoFundamental*>{
              Bloco* bloco;

              NodoFundamental* operator()(Nodo<bool>* condicao) const {
                  return new NodoFundamental(new While(condicao, bloco));
              }

              template <typename V>
              NodoFundamental* operator()(Nodo<V>* condicao) const {
                  throw new Erro("operacao While espera booleano mas recebeu outro");
              }
          };
  };

}
