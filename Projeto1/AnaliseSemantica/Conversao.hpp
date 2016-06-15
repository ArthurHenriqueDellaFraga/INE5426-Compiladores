#pragma once

#include "Contexto.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // INSTANCIACAO

  template <typename T = void, typename U = T>
  class Conversao : public Nodo<T>{
      public:
          Tipo<T>* tipo;
          Nodo<U>* valor;

          Conversao(Tipo<T>* tipo, Nodo<U>* valor) : tipo(tipo), valor(valor){
              //static_assert(std::is_convertible<T, U>::value, "Conversao :: construtor");
          }

          Conversao(Nodo<U>* valor) : valor(valor){
              tipo = new Tipo<T>();
          }

          void print(){
              cout << "(";
              tipo->print();
              cout << ") ";
              valor->print();
          }

          T executar(Contexto* contexto){
              return *(new T(valor->executar(contexto)));
          }

          static NodoFundamental* instanciar(TipoFundamental tipo, NodoFundamental valor){
              return apply_visitor(ConversaoVisitor(), tipo, valor);
          }

      protected:
        struct ConversaoVisitor : public static_visitor<NodoFundamental*>{
            template <typename V, typename W>
            NodoFundamental* operator()(Tipo<V>*& tipo, Nodo<W>* valor) const {
                throw new Erro("Conversao invalida");
            }

            template <typename V>
            NodoFundamental* operator()(Tipo<V>*& tipo, Nodo<V>* valor) const {
                return new NodoFundamental(new Conversao<V>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<void>*& tipo, Nodo<void>*& valor) const {
                throw new Erro("Conversao invalida");
            }

            NodoFundamental* operator()(Tipo<int>*& tipo, Nodo<double>*& valor) const {
                return new NodoFundamental(new Conversao<int, double>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<int>*& tipo, Nodo<bool>*& valor) const {
                return new NodoFundamental(new Conversao<int, bool>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<int>*& tipo, Nodo<char>*& valor) const {
                return new NodoFundamental(new Conversao<int, char>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<double>*& tipo, Nodo<int>*& valor) const {
                return new NodoFundamental(new Conversao<double, int>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<double>*& tipo, Nodo<bool>*& valor) const {
                return new NodoFundamental(new Conversao<double, bool>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<double>*& tipo, Nodo<char>*& valor) const {
                return new NodoFundamental(new Conversao<double, char>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<bool>*& tipo, Nodo<int>*& valor) const {
                return new NodoFundamental(new Conversao<bool, int>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<bool>*& tipo, Nodo<double>*& valor) const {
                return new NodoFundamental(new Conversao<bool, double>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<char>*& tipo, Nodo<int>*& valor) const {
                return new NodoFundamental(new Conversao<char, int>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<char>*& tipo, Nodo<double>*& valor) const {
                return new NodoFundamental(new Conversao<char, double>(tipo, valor));
            }

            NodoFundamental* operator()(Tipo<char>*& tipo, Nodo<bool>*& valor) const {
                return new NodoFundamental(new Conversao<char, bool>(tipo, valor));
            }
        };
  };

}
