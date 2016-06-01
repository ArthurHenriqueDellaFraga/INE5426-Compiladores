#pragma once

#include "Nodo.hpp"

using namespace std;

namespace AnaliseSemantica {

  template <typename T = void>
  class IndiceArranjo ;

  template <typename T = void>
  class Arranjo;

  template <typename... Types>
  class ArranjoPolimorfo : public Polimorfo<Types...>{
      public:
          template<typename T>
          ArranjoPolimorfo(Arranjo<T>* arranjo){
              *this = arranjo;
          };

          VariavelFundamental* getIndiceArranjo(NodoFundamental indice){
              return apply_visitor(getIndiceArranjoVisitor (), *this, indice);
          }

          template<typename T>
          ArranjoPolimorfo<Types...>& operator=(const T& t){
              Polimorfo<Types...>::operator=(t);
              return *this;
          }

      protected:
          struct getIndiceArranjoVisitor : public static_visitor<VariavelFundamental*> {
              string errorMessage = "indice de arranjo espera inteiro mas rececebeu ";

              template<typename V, typename U>
              VariavelFundamental* operator() (Arranjo<V>*& arranjo, Nodo<U>*& indice) const {
                  throw new Erro(errorMessage + indice->getTipo()->getIdentificadorMasculino() + ".");
              }

              template<typename V>
              VariavelFundamental* operator() (Arranjo<V>*& arranjo, Nodo<int>*& indice) const {
                Variavel<V>* variavel = arranjo->getIndiceArranjo(indice);
                return new VariavelFundamental(variavel);
              }
          };
    };

    typedef ArranjoPolimorfo<
        Arranjo<int>*, Arranjo<double>*,
        Arranjo<bool>*,
        Arranjo<char>*, Arranjo<string>*,
        Arranjo<void>*
    > ArranjoFundamental;

    template <typename T>
    class IndiceArranjo : public Variavel<T> {
        private:
            Nodo<int>* indice;
            T* valor;

        public:
            IndiceArranjo(string identificador, Nodo<int>* indice) : Variavel<T>(identificador){
                this->indice = indice;
                this->valor = new T();
                this->inicializacao = true;
            }

            void print(){
                cout << "arranjo " << this->getTipo()->getIdentificadorMasculino() << " "<< this->identificador;
                cout << " {+indice: ";
                indice->print();
                cout << "}";
            }

            T executar(Contexto* contexto){
                return *valor;
            }

            void setReferencia(){
                this->inicializacao = true;
            }

            string getIdentificador(){
                return this->identificador;
            }

            void checkInicializacao(){
                if(!this->inicializacao){
                    throw new Erro("arranjo " + this->identificador + " nao inicializada.");
                }
            }
    };

    template <>
    class IndiceArranjo<void> : public Variavel<void> {
        private:
            Nodo<int>* indice;

        public:
          IndiceArranjo(string identificador, Nodo<int>* indice) : Variavel<void>(identificador){
            this->indice = indice;
          }

            void print(){
                cout << "arranjo " << this->getTipo()->getIdentificadorMasculino() << " "<< this->identificador;
            }

            void executar(Contexto* contexto){ }

            void setReferencia(){ }

            string getIdentificador(){
                return this->identificador;
            }

            void checkInicializacao(){ }
    };

  template <typename T>
  class Arranjo : public Nodo<T> {
      private:
          string identificador;
          int tamanho;

      public:
          Arranjo(string identificador, int tamanho) : identificador(identificador), tamanho(tamanho){ }

          void print(){
              cout << "arranjo " << this->getTipo()->getIdentificadorMasculino();
          }

          T executar(Contexto* contexto){
              return *(new T);
          }

          string getIdentificador(){
            return identificador;
          }

          IndiceArranjo<T>* getIndiceArranjo(Nodo<int>* indice){
            return new IndiceArranjo<T>(identificador, indice);
          }
  };

  template <>
  class Arranjo<void> : public Nodo<void> {
      private:
          string identificador;
          int tamanho;

      public:
          Arranjo(string identificador, int tamanho) : identificador(identificador), tamanho(tamanho){ }

          void print(){
              cout << "arranjo " << this->getTipo()->getIdentificadorFeminino() << " "<< identificador;
          }

          void executar(Contexto* contexto){ }

          string getIdentificador(){
            return identificador;
          }

          IndiceArranjo<void>* getIndiceArranjo(Nodo<int>* indice){
            return new IndiceArranjo<void>(identificador, indice);
          }
  };


}
