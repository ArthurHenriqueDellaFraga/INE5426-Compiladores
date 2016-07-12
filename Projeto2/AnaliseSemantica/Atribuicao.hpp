#pragma once

#include "Conversao.hpp"
#include <boost/variant/multivisitors.hpp>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // INSTANCIAÇÃO

  template <typename T>
  class Atribuicao : public Nodo<void>{
      public:
          Variavel<T>* variavel;
          Nodo<T>* valor;

          Atribuicao() {}

          Atribuicao(Variavel<T>* variavel, Nodo<T>* valor) : variavel(variavel), valor(valor){ }

          void print(){
              cout << "Atribuicao de valor para ";
              variavel->print();
              cout << ": ";
              valor->print();
          }

          void executar(Contexto* contexto){
              *variavel = (valor->executar(contexto));
          }
  };

  // POLIMORFISMO

  class AtribuicaoPolimorfo : public Polimorfo<Atribuicao>{
      public:
          template <typename U>
          AtribuicaoPolimorfo(Atribuicao<U>* atribuicao) : Polimorfo<Atribuicao>(atribuicao){ }

          static AtribuicaoPolimorfo* instanciar(VariavelFundamental* variavel, NodoFundamental* valor){
              return boost::apply_visitor(create_visitor(), *variavel, *valor);
          }

      protected:
          struct create_visitor : public static_visitor<AtribuicaoPolimorfo*>{
              template <typename V, typename W>
              AtribuicaoPolimorfo* operator()(Variavel<V>*& variavel, Nodo<W>*& valor) const {
                    VariavelFundamental* vF = new VariavelFundamental(variavel);
                    NodoFundamental* nF = new NodoFundamental(valor);

                    NodoFundamental* conversao = Conversao<>::instanciar(vF->getTipo(), *nF);
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
