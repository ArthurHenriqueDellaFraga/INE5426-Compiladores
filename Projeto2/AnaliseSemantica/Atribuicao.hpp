#pragma once

#include "Operacao/Conversao.hpp"
#include <boost/variant/multivisitors.hpp>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  //ABSTRAÇÃO

  template <typename T>
  class AtribuicaoAbstrata : public Nodo<void>{
      public:
          Variavel<T>* variavel;
          Nodo<T>* valor;

          AtribuicaoAbstrata(Variavel<T>* variavel, Nodo<T>* valor) : variavel(variavel), valor(valor){ }

          void print(){
              cout << "Atribuicao de valor para ";
              variavel->print();
              cout << ": ";
              valor->print();
          }
  };

  // INSTANCIAÇÃO

  template <typename T>
  class Atribuicao : public AtribuicaoAbstrata<T>{
      public:

          Atribuicao(Variavel<T>* variavel, Nodo<T>* valor)
          : AtribuicaoAbstrata<T>(variavel, valor){ }

          void executar(Contexto* contexto){
              this->variavel->setValor(this->valor->executar(contexto));
          }
  };

  template <>
  class Atribuicao<void> : public AtribuicaoAbstrata<void>{
      public:

          Atribuicao(Variavel<void>* variavel, Nodo<void>* valor)
          : AtribuicaoAbstrata<void>(variavel, valor){ }

          void executar(Contexto* contexto){
              throw new Erro("Atribuicao inválida");
          }

  };

  // POLIMORFISMO

  class AtribuicaoPolimorfo : public NodoPolimorfo<Atribuicao>{
      public:
          template <typename U>
          AtribuicaoPolimorfo(Atribuicao<U>* atribuicao) : NodoPolimorfo<Atribuicao>(atribuicao){ }

          static AtribuicaoPolimorfo* instanciar(VariavelFundamental* variavel, NodoFundamental* valor){
              return boost::apply_visitor(create_visitor(), *variavel, *valor);
          }

      protected:
          struct create_visitor : public static_visitor<AtribuicaoPolimorfo*>{
              template <typename V, typename W>
              AtribuicaoPolimorfo* operator()(Variavel<V>*& variavel, Nodo<W>*& valor) const {
                    VariavelFundamental* vF = new VariavelFundamental(variavel);
                    NodoFundamental* nF = new NodoFundamental(valor);

                    NodoFundamental* conversao = Conversao<>::instanciar(vF->getTipo(), nF);
                    return AtribuicaoPolimorfo::instanciar(vF, conversao);
              }

              template <typename V>
              AtribuicaoPolimorfo* operator()(Variavel<V>*& variavel, Nodo<V>*& valor) const {
                  return new AtribuicaoPolimorfo(new Atribuicao<V>(variavel, valor));
              }


              // Verificar necessidade:
              template <typename V>
              AtribuicaoPolimorfo* operator()(Variavel<void>*& variavel, Nodo<V>*& valor) const {
                  throw new Erro("Atribuição inválida");
                  // return new NodoFundamental(new Atribuicao<void, V>(variavel, valor));
              }

              AtribuicaoPolimorfo* operator()(Variavel<void>*& variavel, Nodo<void>*& valor) const {
                  throw new Erro("Atribuição inválida");
                  //return new AtribuicaoPolimorfo(new Atribuicao<void>(variavel, valor));
              }
          };
  };

  typedef AtribuicaoPolimorfo AtribuicaoFundamental;

}
