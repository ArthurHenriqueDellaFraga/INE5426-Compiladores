#pragma once

#include "Operacao.hpp"

using namespace std;

namespace AnaliseSemantica {

  // INSTANCIACAO

  class NegacaoBooleana : public Operacao<bool, bool> {
	    public:
	        NegacaoBooleana(Nodo<bool>* nodo) : Operacao<bool, bool>(nodo, "negacao") { }

					bool executar(Contexto* contexto){
							return !(this->nodo->executar(contexto));
					}

					static NodoFundamental* instanciar(NodoFundamental* nodo){
							return apply_visitor(create_visitor (), *nodo);
					}

			protected:
					struct create_visitor : public static_visitor<NodoFundamental*>{
              NodoFundamental* operator()(Nodo<bool>*& nodo) const {
                  return new NodoFundamental(new NegacaoBooleana(nodo));
              }

							template <typename V>
							NodoFundamental* operator()(Nodo<V>*& nodo) const {
									throw new Erro("Negação inválida");
							}
					};
  };
}
