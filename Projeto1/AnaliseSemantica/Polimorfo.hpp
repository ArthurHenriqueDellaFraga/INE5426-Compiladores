#pragma once

#include "Tipo.hpp"

#include "boost/variant/apply_visitor.hpp"
#include "boost/variant/static_visitor.hpp"

#include <iostream>

using namespace boost;

namespace AnaliseSemantica {

    class Contexto;

    template <typename... Types>
    class Polimorfo : public variant<Types...>{
        public:
            template<typename T>
            Polimorfo(const T& t){
                *this = t;
            };

            bool inicializado;
            Polimorfo() : variant<Types...>(){}

            void print(){
                apply_visitor(PrintVisitor(), *this);
            }

            void executar(Contexto* contexto){
                ExecutarVisitor visitor;
                visitor.contexto = contexto;
                apply_visitor(visitor, *this);
            }

            template<typename T>
            Polimorfo<Types...>& operator=(const T& t){
                variant<Types...>::operator=(t);
                inicializado = true;
                return *this;
            }

            TipoFundamental getTipo(){
                return apply_visitor(GetTipoVisitor(), *this);
            }

        protected:
            struct PrintVisitor : public static_visitor<void> {
                template <typename T>
                void operator()(T t) const {
                    t->print();
                }
            };

            struct ExecutarVisitor : public static_visitor<void> {
                Contexto* contexto;

                template <typename T>
                void operator()(T t) const {
                    t->executar(contexto);
                }
            };

            struct GetTipoVisitor : public static_visitor<TipoFundamental> {
                template <typename T>
                TipoFundamental operator()(T t) const {
                    TipoFundamental tipo;
                    tipo = t->getTipo();
                    return tipo;
                }
            };
      };

}
