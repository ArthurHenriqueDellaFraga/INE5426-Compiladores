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
              //this->inicializado = true;
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
      Definicao<char>*, Definicao<string>*,
      Definicao<void>*
  > DefinicaoFundamental;

  template <typename T = void>
  class Definicao : public Nodo<void>{
      protected:
          Tipo<T>* tipo;
          vector<string> listaDeIdentificadores;

      public:
          Definicao() {}

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
                  VariavelFundamental variavel;
                  variavel = new Variavel<T>(listaDeIdentificadores[i]);
                  contexto->put(listaDeIdentificadores[i], variavel);
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

            template <typename U>
            DefinicaoFundamental* operator()(Tipo<U>*& tipo) const {
                return new DefinicaoFundamental(new Definicao<U>(tipo, identificador));
            }
        };
  };

  template <typename T = void>
  class DefinicaoArranjo : public Definicao<void>{
      protected:
          Tipo<T>* tipo;
          NodoFundamental tamanho;
          string identificador;
          int tamanhoArranjo;

      public:
          DefinicaoArranjo(Tipo<T>* tipo, NodoFundamental tamanho, string identificador) : tipo(tipo), tamanho(tamanho), identificador(identificador){ }

          void print(){
              cout << "Declaracao de arranjo "<< tipo->getIdentificadorMasculino() << " de tamanho " << tamanhoArranjo;
              cout << ": " << identificador;
          }

          void executar(Contexto* contexto){
              createTamanhoVisitor tamanhoVisitor;
              tamanhoVisitor.contexto = contexto;
              tamanhoArranjo = apply_visitor(tamanhoVisitor, tamanho);
              cout << "tmanaho kakaskas: " << tamanhoArranjo;
              ArranjoFundamental arranjo = new Arranjo<T>(identificador, tamanhoArranjo);
              contexto->putArranjo(identificador, arranjo);
          }

          static DefinicaoFundamental* instanciarArranjo(TipoFundamental tipo, NodoFundamental tamanho, string identificador){
              createArranjoVisitor visitor;
              visitor.tamanho = tamanho;
              visitor.identificador = identificador;
              return apply_visitor(visitor, tipo);
          }

      protected:
        struct createArranjoVisitor : public static_visitor<DefinicaoFundamental*>{
            NodoFundamental tamanho;
            string identificador;

            template <typename U>
            DefinicaoFundamental* operator()(Tipo<U>*& tipo) const {
                return new DefinicaoFundamental(new DefinicaoArranjo<U>(tipo, tamanho, identificador));
            }
        };

        struct createTamanhoVisitor : public static_visitor<int>{
            string errorMessage = "indice de arranjo espera inteiro mas rececebeu ";
            Contexto* contexto;

            template <typename U>
            int operator()(Nodo<U>*& tamanho) const {
                throw new Erro(errorMessage + tamanho->getTipo().getIdentificadorMasculino() + ".");
            }

            int operator()(Nodo<int>*& tamanho) const {
                return tamanho->executar(contexto);
            }
        };
  };
}
