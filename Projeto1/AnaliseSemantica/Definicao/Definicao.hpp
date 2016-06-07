#pragma once

#include "../Contexto.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T>
  class Definicao;

  template <typename... Types>
  class DefinicaoPolimorfo : public Polimorfo<Types...>{
      public:
          template<typename T>
          DefinicaoPolimorfo(Definicao<T>* definicao) : Polimorfo<Types...>(definicao){ };

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
              void operator() (Definicao<V>*& definicao) const {
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

  template <template <typename> class T, typename U>
  class DefinicaoAbstrata : public Nodo<void>{
      protected:
          vector<string> listaDeIdentificadores;

      public:
          DefinicaoAbstrata(string identificador){
              *this << identificador;
          }

          void print(){
              cout << "Definicao de ";
              (new Tipo<T>())->print();
              cout << " ";
              (new Tipo<U>())->print();
              cout << ": " << listaDeIdentificadores[0];

              for(int i = 1; i < listaDeIdentificadores.size(); i++){
                  cout << ", " << listaDeIdentificadores[i];
              }
          }

          void operator<< (string identificador){
              vetor.push_back(identificador);
          }
  };

  template <template <typename> class T, typename U>
  class Definicao : public DefinicaoAbstrata<T, U>{
      protected:
          Definicao(string identificador) : DefinicaoAbstrata<T, U>(identificador){ }

  };

  template <typename U>
  class Definicao<Variavel, U> : public DefinicaoAbstrata<Variavel, U>{
      public:
          Definicao(string identificador) : DefinicaoAbstrata<Variavel, U>(identificador){ }

          void executar(){
              VariavelFundamental* variavel = new VariavelFundamental(new Variavel<U>(identificador));
              contexto->put(identificador, variavel);
          }
  };

  class DefinicaoPolimorfo : public NodoPolimorfo<Definicao>{
      public:
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

  template <typename T = void>
  class DefinicaoArranjo : public Definicao<void>{
      protected:
          Tipo<T>* tipo;
          Nodo<int>* tamanho;
          string identificador;
          int tamanhoArranjo;

      public:
          DefinicaoArranjo(Tipo<T>* tipo, Nodo<int>* tamanho, string identificador) : tipo(tipo), tamanho(tamanho), identificador(identificador){ }

          void print(){
              cout << "Declaracao de arranjo "<< tipo->getIdentificadorMasculino() << " de tamanho " << tamanhoArranjo;
              cout << ": " << identificador;
          }

          void executar(Contexto* contexto){
              tamanhoArranjo = tamanho->executar(contexto);
              ArranjoFundamental* arranjo = new ArranjoFundamental(new Arranjo<T>(identificador, tamanhoArranjo));
              contexto->putArranjo(identificador, arranjo);
          }

          static DefinicaoFundamental* instanciarArranjo(TipoFundamental tipo, NodoFundamental tamanho, string identificador){
              createArranjoVisitor visitor;
              visitor.identificador = identificador;
              return apply_visitor(visitor, tipo, tamanho);
          }

      protected:
        struct createArranjoVisitor : public static_visitor<DefinicaoFundamental*>{
            string errorMessage = "indice de arranjo espera inteiro mas rececebeu ";
            string identificador;

            template <typename U>
            DefinicaoFundamental* operator()(Tipo<U>*& tipo, Nodo<int>*& tamanho) const {
                return new DefinicaoFundamental(new DefinicaoArranjo<U>(tipo, tamanho, identificador));
            }

            template <typename U, typename V>
            DefinicaoFundamental* operator()(Tipo<U>*& tipo, Nodo<V>*& tamanho) const {
                throw new Erro(errorMessage + tamanho->getTipo()->getIdentificadorMasculino() + ".");
            }
        };
  };
}
