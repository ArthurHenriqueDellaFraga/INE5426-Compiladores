#pragma once

#include "../Bloco.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // INSTANCIAÇÃO

  class If : public Nodo<void> {
      public:
          Nodo<bool>* condicao;
          Bloco* _true;
          Bloco* _false;

          If(Nodo<bool>* condicao, Bloco* _true, Bloco* _false)
          : condicao(condicao), _true(_true), _false(_false){ }

          void print(){
              cout << "Expressao condicional" << endl;
              cout << "+se: ";
              condicao->print();
              cout << endl;

              cout << "+entao: " << endl;
              _true->print();

              if(_false != NULL){
                  cout << "+senao: " << endl;
                  _false->print();
              }

              cout << "Fim expressao condicional";
          }

          void executar(Contexto* contexto){
              if(this->condicao->executar(contexto)){
                  _true->executar(contexto);
              }
              else if(_false != NULL){
                  _false->executar(contexto);
              }
          }

          static NodoFundamental* instanciar(NodoFundamental* condicao, Bloco* _true, Bloco* _false){
              create_visitor create;
              create._true = _true;
              create._false = _false;
              return apply_visitor(create, *condicao);
          }

      protected:
          struct create_visitor : public static_visitor<NodoFundamental*>{
              Bloco* _true;
              Bloco* _false;

              NodoFundamental* operator()(Nodo<bool>* condicao) const {
                  return new NodoFundamental(new If(condicao, _true, _false));
              }

              template <typename V>
              NodoFundamental* operator()(Nodo<V>* condicao) const {
                  throw new Erro("operacao If espera booleano mas recebeu outro");
              }
          };
  };

}
