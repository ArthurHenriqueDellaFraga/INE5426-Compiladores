#pragma once

#include "../Bloco.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T = void>
  class If : public Nodo<void> {
      public:
          Nodo<T>* condicao;
          map<bool, Bloco*> listaDeInstrucoes;
          Contexto* contexto;


          If(Contexto* contexto, Nodo<T>* condicao, Bloco* _then, Bloco* _else) : condicao(condicao), contexto(contexto){
              listaDeInstrucoes.insert(pair<bool, Bloco*>(true, _then));
              if(_else != NULL)
                  listaDeInstrucoes.insert(pair<bool, Bloco*>(false, _else));
          }

          void print(){
              cout << "Expressao condicional" << endl;
              cout << "+se: ";
              condicao->print();
              cout << endl;

              for(map<bool, Bloco*>::reverse_iterator it = listaDeInstrucoes.rbegin(); it != listaDeInstrucoes.rend(); ++it){
                  if(it->first)
                      cout << "+entao: " << endl;
                  else
                      cout << "+senao: " << endl;

                  it->second->print();
              }
              cout << "Fim expressao condicional";
          }

          static Nodo<void>* instanciar(Contexto* contexto, NodoFundamental condicao, Bloco* _then, Bloco* _else){
              createVisitor create;
              create.contexto = contexto;
              create._then = _then;
              create._else = _else;
              return apply_visitor(create, condicao);
          }

      protected:
          struct createVisitor : public static_visitor<Nodo<void>*>{
              Contexto* contexto;
              Bloco* _then;
              Bloco* _else;

              Nodo<void>* operator()(Nodo<bool>* condicao) const {
                  return new If<bool>(contexto, condicao, _then, _else);
              }

              template <typename V>
              Nodo<void>* operator()(Nodo<V>* condicao) const {
                  Erro* erro = new Erro("operacao teste espera booleano mas recebeu " + condicao->getTipo()->getIdentificadorMasculino() + "." );
                  erro->print();
                  return new If<V>(contexto, condicao, _then, _else);
              }
          };
  };

}
