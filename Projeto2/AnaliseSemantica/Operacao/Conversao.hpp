#pragma once

#include "Operacao.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // INSTANCIACAO

  template <typename T = void, typename U = T>
  class Conversao : public Operacao<T, U>{
      public:
          Conversao(Tipo<T>* tipo, Nodo<U>* nodo) : Operacao<T, U>(nodo, "conversao para " + tipo->getIdentificador()){ }

          T executar(Contexto* contexto){
              return *(new T(this->nodo->executar(contexto)));
          }

          static NodoFundamental* instanciar(TipoFundamental* tipo, NodoFundamental* nodo){
              return apply_visitor(create_visitor(), *tipo, *nodo);
          }

      protected:
        struct create_visitor : public static_visitor<NodoFundamental*>{
            template <typename V, typename W>
            NodoFundamental* operator()(Tipo<V>*& tipo, Nodo<W>* nodo) const {
                throw new Erro("Conversao invalida");
            }

            template <typename V>
            NodoFundamental* operator()(Tipo<V>*& tipo, Nodo<V>* nodo) const {
                return new NodoFundamental(new Conversao<V>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<void>*& tipo, Nodo<void>*& nodo) const {
                throw new Erro("Conversao invalida");
            }

            NodoFundamental* operator()(Tipo<int>*& tipo, Nodo<double>*& nodo) const {
                return new NodoFundamental(new Conversao<int, double>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<int>*& tipo, Nodo<bool>*& nodo) const {
                return new NodoFundamental(new Conversao<int, bool>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<int>*& tipo, Nodo<char>*& nodo) const {
                return new NodoFundamental(new Conversao<int, char>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<double>*& tipo, Nodo<int>*& nodo) const {
                return new NodoFundamental(new Conversao<double, int>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<double>*& tipo, Nodo<bool>*& nodo) const {
                return new NodoFundamental(new Conversao<double, bool>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<double>*& tipo, Nodo<char>*& nodo) const {
                return new NodoFundamental(new Conversao<double, char>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<bool>*& tipo, Nodo<int>*& nodo) const {
                return new NodoFundamental(new Conversao<bool, int>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<bool>*& tipo, Nodo<double>*& nodo) const {
                return new NodoFundamental(new Conversao<bool, double>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<char>*& tipo, Nodo<int>*& nodo) const {
                return new NodoFundamental(new Conversao<char, int>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<char>*& tipo, Nodo<double>*& nodo) const {
                return new NodoFundamental(new Conversao<char, double>(tipo, nodo));
            }

            NodoFundamental* operator()(Tipo<char>*& tipo, Nodo<bool>*& nodo) const {
                return new NodoFundamental(new Conversao<char, bool>(tipo, nodo));
            }
        };
  };

}
