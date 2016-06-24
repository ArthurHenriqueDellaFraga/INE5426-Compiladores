#pragma once

#include "../Nodo.hpp"

using namespace std;

namespace AnaliseSemantica {

  // ABSTRAÇÃO

  template <typename T>
  class OperacaoAbstrata : public Nodo<T>{
      protected:
          string simbolo;

          OperacaoAbstrata(string simbolo) : simbolo(simbolo){ }
  };

  // INSTANCIAÇÃO

  template <typename T, typename ... U>
  class Operacao : public OperacaoAbstrata<T>{
      protected:
          Operacao() : OperacaoAbstrata<T>(""){ }
  };

  template <typename T, typename U>
  class Operacao<T, U> : public OperacaoAbstrata<T>{
      protected:
          Nodo<U>* nodo;

          Operacao(Nodo<U>* nodo, string simbolo) : nodo(nodo), OperacaoAbstrata<T>(simbolo){ }

      public:
          void print(){
              cout << this->simbolo[0];
              nodo->print();
              cout << this->simbolo[1];
          }
  };

  template <typename T, typename L, typename R>
  class Operacao<T, L, R> : public OperacaoAbstrata<T>{
      protected:
          Nodo<L>* left;
          Nodo<R>* right;

          Operacao(Nodo<L>* left, string simbolo, Nodo<R>* right) : left(left), right(right), OperacaoAbstrata<T>(simbolo){ }

      public:
          void print(){
              cout << this->simbolo[0];
              nodo->print();
              cout << this->simbolo[1];
          }
  };

  // ------------------

    template <typename T, typename L, typename R>
    class OperacaoBinaria : public Nodo<T> {
        protected:
            Nodo<L>* left;
            string simbolo;
            Nodo<R>* right;
            OperacaoBinaria(Nodo<L>* left, string simbolo, Nodo<R>* right) : left(left), simbolo(simbolo), right(right) { }
        public:
            void print(){
                cout << "(";
                left->print();
                cout << " (" << simbolo << " " << this->getTipo()->getIdentificadorFeminino() << ") ";
                right->print();
                cout << ")";
            };
    };

    template <typename T = void, typename N = T>
    class OperacaoUnaria : public Nodo<T> {
        protected:
            Nodo<N>* nodo;

            OperacaoUnaria(Nodo<N>* nodo) : nodo(nodo) { }

            T executar(Contexto* contexto){
                return *(new T());
            }
    };

    template <typename N>
    class OperacaoUnaria<void, N> : public Nodo<void> {
        protected:
            Nodo<N>* nodo;

            OperacaoUnaria(Nodo<N>* nodo) : nodo(nodo) { }

            void executar(Contexto* contexto){ }
    };
}
