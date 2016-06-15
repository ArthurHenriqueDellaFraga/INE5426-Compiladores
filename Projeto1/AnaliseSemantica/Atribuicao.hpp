#pragma once

#include "Conversao.hpp"
#include <boost/variant/multivisitors.hpp>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // INSTANCIACAO

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
              valor-> print();
          }

          void executar(Contexto* contexto){
              variavel->setReferencia(*(new T(valor->executar(contexto))));
          }

          static NodoFundamental* instanciar(VariavelFundamental variavel, NodoFundamental valor){
              return apply_visitor(createVisitor (), variavel, valor);
          }

      protected:
          struct createVisitor : public static_visitor<NodoFundamental*>{
              template <typename V, typename W>
              NodoFundamental* operator()(Variavel<V>*& variavel, Nodo<W>*& valor) const {
                    VariavelFundamental* vF = new VariavelFundamental(variavel);
                    NodoFundamental* nF = new NodoFundamental(valor);

                    NodoFundamental* conversao = Conversao<>::instanciar(vF->getTipo(), *nF);
                    return Atribuicao<int>::instanciar(*vF, *conversao);
              }

              template <typename V>
              NodoFundamental* operator()(Variavel<V>*& variavel, Nodo<V>*& valor) const {
                  return new NodoFundamental(new Atribuicao<V>(variavel, valor));
              }

              template <typename V>
              NodoFundamental* operator()(Variavel<void>*& variavel, Nodo<V>*& valor) const {
                  throw new Erro("Atribuição inválida")
                  // return new NodoFundamental(new Atribuicao<void, V>(variavel, valor));
              }

              NodoFundamental* operator()(Variavel<void>*& variavel, Nodo<void>*& valor) const {
                  return new NodoFundamental(new Atribuicao<void>(variavel, valor));
              }
          };
  };

}
