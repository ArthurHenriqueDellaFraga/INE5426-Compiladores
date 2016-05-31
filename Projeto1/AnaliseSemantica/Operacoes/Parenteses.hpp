#pragma once

#include "../Contexto.hpp"

using namespace std;

namespace AnaliseSemantica {

	template<typename T = int>
    class Parenteses : public OperacaoUnaria<T> {
		    public:
		        Parenteses(Nodo<T>* nodo) : OperacaoUnaria<T>(nodo) { }

		        void print(){
		        	cout << "((abre parenteses) ";
		        	this->nodo->print();
		        	cout<< " (fecha parenteses))";
		        }

		        T executar(Contexto* contexto){
		            return this->nodo->executar(contexto);
		        }

						static NodoFundamental* instanciar(NodoFundamental nodo){
								return apply_visitor(createVisitor (), nodo);
						}

				protected:
						struct createVisitor : public static_visitor<NodoFundamental*>{
								template <typename U>
								NodoFundamental* operator()(Nodo<U>*& nodo) const {
										return new NodoFundamental(new Parenteses<U>(nodo));
								}
						};
    };

		template<>
		class Parenteses<void> : public OperacaoUnaria<void> {
				public:
						Parenteses(Nodo<void>* nodo) : OperacaoUnaria<void>(nodo) { }

						void print(){
							cout << "((abre parenteses) ";
							this->nodo->print();
							cout<< " (fecha parenteses))";
						}

						void executar(Contexto* contexto){ }
		};
}
