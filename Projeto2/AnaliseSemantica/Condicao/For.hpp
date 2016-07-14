#pragma once

#include "../Bloco.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // INSTANCIAÇÃO

  class For : public Nodo<void> {
      public:
          Variavel<int>* variavel;
          Nodo<bool>* condicao;
          Atribuicao<int>* atribuicao;
          Bloco* bloco;

          For(Variavel<int>* variavel, Nodo<bool>* condicao, Atribuicao<int>* atribuicao, Bloco* bloco)
          : variavel(variavel), condicao(condicao), atribuicao(atribuicao), bloco(bloco){ }

          void print(){
              cout << "Expressao condicional" << endl;
              cout << "+para: ";
              variavel->print();
              cout << ";" << endl;
              condicao->print();
              cout << ";" << endl;
              atribuicao->print();
              cout << endl;

              cout << "+faz: " << endl;
              bloco->print();

              cout << "Fim expressao condicional";
          }

          void executar(Contexto* contexto){
              bloco->addInstrucao(new NodoFundamental(atribuicao));

              while(this->condicao->executar(contexto)){
                  bloco->executar(contexto);
              }
          }

          static NodoFundamental* instanciar(VariavelFundamental* variavel, NodoFundamental* condicao, AtribuicaoFundamental* atribuicao, Bloco* bloco){
              create_visitor create;
              create.bloco = bloco;
              return apply_visitor(create, *variavel, *condicao, *atribuicao);
          }

      protected:
          struct create_visitor : public static_visitor<NodoFundamental*>{
              Bloco* bloco;

              NodoFundamental* operator()(Variavel<int>* variavel, Nodo<bool>* condicao, Atribuicao<int>* atribuicao) const {
                  return new NodoFundamental(new For(variavel, condicao, atribuicao, bloco));
              }

              template <typename V, typename W, typename X>
              NodoFundamental* operator()(Variavel<V>* variavel, Nodo<W>* condicao, Atribuicao<X>* atribuicao) const {
                  throw new Erro("operacao For espera inteiro, booleano e inteiro mas recebeu outros");
              }
          };
  };

}
