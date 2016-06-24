#pragma once

#include "../Contexto.hpp"

using namespace std;

namespace AnaliseSemantica {

	template<typename T = int>
    class Parenteses : public Operacao<T, T> {
		    public:
		        Parenteses(Nodo<T>* nodo) : Operacao<T, T>(nodo, "") { }

		        void print(){
			        	cout << "( ";
			        	this->nodo->print();
			        	cout<< " )";
		        }

						static NodoFundamental* instanciar(NodoFundamental nodo){
								return apply_visitor(createVisitor (), nodo);
						}

				protected:
						struct createVisitor : public static_visitor<NodoFundamental*>{
								template <typename V>
								NodoFundamental* operator()(Nodo<V>*& nodo) const {
										return new NodoFundamental(new Parenteses<V>(nodo));
								}
						};
    };
}
