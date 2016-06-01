#pragma once

#include "Nodo.hpp"

using namespace std;

namespace AnaliseSemantica {

  template <typename T = void>
  class Variavel;

  template <typename... Types>
  class VariavelPolimorfo : public Polimorfo<Types...>{
      public:
          template<typename T>
          VariavelPolimorfo(Variavel<T>* variavel){
              *this = variavel;
          };

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

  template <typename T>
  class Variavel : public Nodo<T> {
      protected:
          bool inicializacao;
          string identificador;
          T* valor;
      public:
          Variavel(string identificador) : identificador(identificador), valor(new T()){ }

          Variavel() { }

          void print(){
              cout << "variavel " << this->getTipo()->getIdentificadorFeminino() << " "<< identificador;
          }

          T executar(Contexto* contexto){
              return *valor;
          }

          void setReferencia(){
              inicializacao = true;
          }

          string getIdentificador(){
              return identificador;
          }

          void checkInicializacao(){
              if(!inicializacao){
                  throw new Erro("variavel " + identificador + " nao inicializada.");
              }
          }
  };

  template <>
  class Variavel<void> : public Nodo<void> {
      protected:
          string identificador;

      public:
          Variavel(string identificador) : identificador(identificador){ }

          Variavel() { }

          void print(){
              cout << "variavel " << this->getTipo()->getIdentificadorFeminino() << " "<< identificador;
          }

          void executar(Contexto* contexto){ }

          void setReferencia(){ }

          string getIdentificador(){
              return identificador;
          }

          void checkInicializacao(){ }
  };

}
