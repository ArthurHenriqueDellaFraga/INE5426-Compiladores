#pragma once

#include "Contexto.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T>
  class Definicao;

  template <typename... Types>
  class DefinicaoPolimorfo : public Polimorfo<Types...>{
      public:
          template<typename T>
          DefinicaoPolimorfo(Definicao<T>* definicao){
              *this = definicao;
          };

          void add(string identificador){
              AddVisitor visitor;
              visitor.identificador = identificador;
              apply_visitor(visitor, *this);
          }

          template<typename T>
          DefinicaoPolimorfo<Types...>& operator=(const T& t){
              Polimorfo<Types...>::operator=(t);
              return *this;
          }

      protected:
          struct AddVisitor : public static_visitor<void>{
              string identificador;

              template <typename V>
              void operator()(Definicao<V>*& definicao) const {
                  definicao->add(identificador);
              }
          };
  };

  typedef DefinicaoPolimorfo<
      Definicao<int>*, Definicao<double>*,
      Definicao<bool>*,
      Definicao<char>*, Definicao<string>*,
      Definicao<void>*
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
              cout << "Declaracao de variavel " << tipo->getIdentificadorFeminino() << ": " << listaDeIdentificadores[0];

              for(int i = 1; i < listaDeIdentificadores.size(); i++){
                  cout << ", " << listaDeIdentificadores[i];
              }
          }
          void executar(Contexto* contexto){
              for(int i = 0; i < listaDeIdentificadores.size(); i++){
                  try{
                      contexto->put(listaDeIdentificadores[i], new VariavelFundamental(new Variavel<T>(listaDeIdentificadores[i])));
                  }
                  catch(Erro* erro){
                      erro->print();
                  }
              }
          }

          void add(string identificador){
              listaDeIdentificadores.push_back(identificador);
          }

          static DefinicaoFundamental* instanciar(TipoFundamental tipo, string identificador){
              createVisitor visitor;
              visitor.identificador = identificador;
              return apply_visitor(visitor, tipo);
          }

      protected:
        struct createVisitor : public static_visitor<DefinicaoFundamental*>{
            string identificador;

            template <typename V>
            DefinicaoFundamental* operator()(Tipo<V>*& tipo) const {
                return new DefinicaoFundamental(new Definicao<V>(tipo, identificador));
            }
        };
  };
}
