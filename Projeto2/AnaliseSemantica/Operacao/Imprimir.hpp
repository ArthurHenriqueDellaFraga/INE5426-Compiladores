#pragma once

#include "Operacao.hpp"

using namespace std;

namespace AnaliseSemantica {

	// INSTANCIAÇÃO

	template<typename T>
    class Imprimir : public Operacao<void, T> {
		    public:
		        Imprimir(Nodo<T>* nodo) : Operacao<void, T>(nodo, "print") { }

            void print(){
                cout << "<" << this->simbolo << "> ";
                this->nodo->print();
            }

						void executar(Contexto* contexto){
                this->print();
                cout << ": " << this->nodo->executar(contexto);
						}

						static NodoFundamental* instanciar(NodoFundamental* nodo){
								return apply_visitor(create_visitor(), *nodo);
						}

				protected:
						struct create_visitor : public static_visitor<NodoFundamental*>{
								template <typename V>
								NodoFundamental* operator()(Nodo<V>*& nodo) const {
										return new NodoFundamental(new Imprimir<V>(nodo));
								}
						};
    };
}
