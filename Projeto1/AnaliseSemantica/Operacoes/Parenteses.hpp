#pragma once

#include "../Contexto.hpp"

using namespace std;

namespace AnaliseSemantica {

	template<typename T = int>
    class Parenteses : public Operacao<T, T> {
		    public:
		        Parenteses(Nodo<T>* nodo) : Operacao<T, T>(nodo, "parenteses") { }

		        void print(){
			        	cout << "<abre " << this->simbolo << "> ";
			        	this->nodo->print();
			        	cout << " <fecha " << this->simbolo << "> ";
		        }

						static NodoFundamental* instanciar(NodoFundamental nodo){
								return apply_visitor(create_visitor (), nodo);
						}

				protected:
						struct create_visitor : public static_visitor<NodoFundamental*>{
								template <typename V>
								NodoFundamental* operator()(Nodo<V>*& nodo) const {
										return new NodoFundamental(new Parenteses<V>(nodo));
								}
						};
    };
}
