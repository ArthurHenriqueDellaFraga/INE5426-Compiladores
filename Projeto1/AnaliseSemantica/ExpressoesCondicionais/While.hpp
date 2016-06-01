#pragma once

#include "../Bloco.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T = void>
  class While : public Nodo<void> {
      public:
          Nodo<T>* condicao;
          Bloco* listaDeInstrucoes;

          While(Nodo<T>* condicao, Bloco* _do) : condicao(condicao), listaDeInstrucoes(_do){}

          void print(){
              cout << "Laco" << endl;
              cout << "+enquanto: ";
              condicao->print();
              cout << "+faca:" << endl;
              listaDeInstrucoes->print();
              cout << "Fim laco";
          }

          static Nodo<void>* instanciar(NodoFundamental condicao, Bloco* _do){
              createVisitor create;
              create._do = _do;
              return apply_visitor(create, condicao);
          }

      protected:
          struct createVisitor : public static_visitor<Nodo<void>*>{
              Bloco* _do;

              Nodo<void>* operator()(Nodo<bool>* condicao) const {
                  return new While<bool>(condicao, _do);
              }

              template <typename V>
              Nodo<void>* operator()(Nodo<V>* condicao) const {
                  Erro* erro = new Erro("operacao teste espera booleano mas recebeu " + condicao->getTipo()->getIdentificadorMasculino() + "." );
                  erro->print();
                  return new While<V>(condicao, _do);
              }
          };
  };

}
