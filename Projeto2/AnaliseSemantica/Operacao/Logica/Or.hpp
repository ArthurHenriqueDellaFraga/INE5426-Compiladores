#pragma once

#include "../Operacao.hpp"

using namespace std;

namespace AnaliseSemantica {

  // INSTANCIAÇÃO

  class Or : public Operacao<bool, bool, bool>{
      public:
          Or(Nodo<bool>* left, Nodo<bool>* right) : Operacao<bool, bool, bool>(left, "or", right){ }

          bool executar(Contexto* contexto){
              return (this->left->executar(contexto)) || (this->right->executar(contexto));
          }

          static NodoFundamental* instanciar(NodoFundamental* left, NodoFundamental* right){
              return apply_visitor(create_visitor (), *left, *right);
          }

      protected:
          struct create_visitor : public static_visitor<NodoFundamental*>{
              string mensagemDeErro = "operacao Or espera booleano mas recebeu outro";

              NodoFundamental* operator()(Nodo<bool>*& left, Nodo<bool>*& right) const {
                  return new NodoFundamental(new Or(left, right));
              }


              template <typename V, typename W>
              NodoFundamental* operator()(Nodo<V>*& left, Nodo<W>*& right) const {
                  throw new Erro(mensagemDeErro);
              }
          };
  };

}
