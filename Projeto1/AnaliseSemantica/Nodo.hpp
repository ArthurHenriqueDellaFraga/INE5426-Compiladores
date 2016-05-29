#pragma once

#include "Erro.hpp"
#include "Polimorfo.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename T>
    class Nodo;

    typedef Polimorfo<
        Nodo<int>*, Nodo<double>*,
        Nodo<bool>*,
        Nodo<char>*, Nodo<string>*,
        Nodo<void>*
    > NodoFundamental;

    template <typename T = void>
    class Nodo {
        public:
            // virtual ~Nodo();
            virtual void print() = 0;
            virtual T executar(Contexto* contexto) = 0;
            Tipo<T> getTipo(){
                return *(new Tipo<T>());
            }

            template <typename U>
            static NodoFundamental* converter(U* u){
                return apply_visitor(ConverterVisitor (), *u);
            }

            template <typename U>
            static NodoFundamental* converter(Nodo<U>* nodo){
                return new NodoFundamental(nodo);
            }

        protected:
            struct ConverterVisitor : public static_visitor<NodoFundamental*>{
                template <typename U>
                NodoFundamental* operator()(U& u) const {
                    return new NodoFundamental(u);
                }
            };
    };

}
