#pragma once

#include "Nodo.hpp"

using namespace std;

namespace AnaliseSemantica {

  template <typename T = void>
  class VariavelAbstrata : public Nodo<T> {
      protected:
          bool inicializacao;
          string identificador;
      public:
          VariavelAbstrata(string identificador) : identificador(identificador){ }

          void print(){
              cout << "variavel " << this->getTipo()->getIdentificadorFeminino() << " "<< identificador;
          }

          string getIdentificador(){
              return identificador;
          }

          virtual void setReferencia(){
              inicializacao = true;
          }

          virtual void checkInicializacao(){
              if(!inicializacao){
                  throw new Erro("variavel " + identificador + " nao inicializada.");
              }
          }
  };

  template <typename T = void>
  class Variavel : public VariavelAbstrata<T> {
      protected:
          T valor;
      public:
          Variavel(string identificador) : VariavelAbstrata<T>(identificador){ }

          T executar(Contexto* contexto){
              return this->valor;
          }
  };

  template <typename... Types>
  class VariavelPolimorfo : public Polimorfo<Types...>{
      public:
          template<typename T>
          VariavelPolimorfo(Variavel<T>* variavel) : Polimorfo<Types...>(variavel){ }

          string getIdentificador(){
              return apply_visitor(getIdentificadorVisitor (), *this);
          }

          void checkInicializacao(){
              apply_visitor(checkInicializacaoVisitor (), *this);
          }

          template<typename T>
          VariavelPolimorfo<Types...>& operator=(const T& t){
              Polimorfo<Types...>::operator=(t);
              return *this;
          }

      protected:
          struct getIdentificadorVisitor : public static_visitor<string>{
              template <typename V>
              string operator()(Variavel<V>*& variavel) const {
                  return variavel->getIdentificador();
              }
          };

          struct checkInicializacaoVisitor : public static_visitor<void>{
              template <typename V>
              void operator()(Variavel<V>*& variavel) const {
                  variavel->checkInicializacao();
              }
          };
  };

  typedef VariavelPolimorfo<
      Variavel<int>*, Variavel<double>*,
      Variavel<bool>*,
      Variavel<char>*, Variavel<string>*,
      Variavel<void>*
  > VariavelFundamental;

  template <>
  class Variavel<void> : public VariavelAbstrata<void> {
      public:
          Variavel(string identificador) : VariavelAbstrata<void>(identificador){ }

          void executar(Contexto* contexto){ }

          void setReferencia(){
              throw new Erro("variavel " + this->identificador + " nao declarada.");
          }

          void checkInicializacao(){ }
  };

}
