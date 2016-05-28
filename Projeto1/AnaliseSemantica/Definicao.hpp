#pragma once

#include "Contexto.hpp"
#include "Tipo.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T>
  class Definicao;

  template <typename... Types>
  class DefinicaoPolimorfo : public Polimorfo<Types...>{
      public:
          void add(string identificador){
              AddVisitor visitor;
              visitor.identificador = identificador;
              apply_visitor(visitor, *this);
          }

          template<typename T>
          DefinicaoPolimorfo<Types...>& operator=(const T& t){
              variant<Types...>::operator=(t);
              return *this;
          }

      protected:
          struct AddVisitor : public static_visitor<void>{
              string identificador;

              template <typename U>
              void operator()(Definicao<U>*& definicao) const {
                  definicao->add(identificador);
              }
          };
  };

  typedef DefinicaoPolimorfo<
      Definicao<int>*, Definicao<double>*,
      Definicao<bool>*,
      Definicao<char>*, Definicao<string>*
  > DefinicaoFundamental;

  template <typename T = void>
  class Definicao : public Nodo<void>{
      protected:
          Tipo<T>* tipo;
          vector<string> listaDeIdentificadores;

      public:
          Definicao(Tipo<T>* tipo, string identificador) : tipo(tipo){
              add(identificador);
          }

          void print(){
              tipo->print();
              cout << " " << listaDeIdentificadores[0];

              for(int i = 1; i < listaDeIdentificadores.size(); i++){
                  cout << ", " << listaDeIdentificadores[i];
              }
          }
          void executar(Contexto* contexto){
              for(int i = 0; i < listaDeIdentificadores.size(); i++){
                  VariavelFundamental variavel;
                  variavel = new Variavel<T>(listaDeIdentificadores[i]);
                  contexto->_variavel[listaDeIdentificadores[i]] = variavel;
              }
          }

          void add(string identificador){
              listaDeIdentificadores.push_back(identificador);
          }

          static DefinicaoFundamental instanciar(TipoFundamental tipo, string identificador){
              createVisitor visitor;
              visitor.identificador = identificador;
              return apply_visitor(visitor, tipo);
          }


      protected:
        struct createVisitor : public static_visitor<DefinicaoFundamental>{
            string identificador;

            template <typename U>
            DefinicaoFundamental operator()(Tipo<U>*& tipo) const {

                DefinicaoFundamental definicao;
                definicao = new Definicao<U>(tipo, identificador);
                return definicao;
            }
        };
  };
}
