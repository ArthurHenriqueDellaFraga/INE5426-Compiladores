#pragma once

#include "Contexto.hpp"

using namespace std;

namespace AnaliseSemantica {

  // ABSTRAÇÃO

  template <typename T>
  class PrimitivoAbstrato : public Nodo<T> {
      protected:
          T valor;

          PrimitivoAbstrato(){ }
          PrimitivoAbstrato(T valor) : valor(valor){ }

          void print(){
              cout << "valor ";
              this->getTipo()->print();
              cout << " " << valor;
          };

          T executar(Contexto* contexto){
              return valor;
          }
  };

  // INSTANCIAÇÃO

  template<typename T>
  class Primitivo : public PrimitivoAbstrato<T>{
      public:
          Primitivo() : PrimitivoAbstrato<T>(){ };
          Primitivo(T valor) : PrimitivoAbstrato<T>(valor){ };
  };

  template<>
  class Primitivo<bool> : public PrimitivoAbstrato<bool>{
      public:
          Primitivo(bool valor) : PrimitivoAbstrato<bool>(valor){ };

          void print(){
              cout << "valor ";
              this->getTipo()->print();
              if(valor){
                  cout << " TRUE";
              }else{
                  cout << " FALSE";
              }
          };
  };

  typedef Primitivo<int> Inteiro;
  typedef Primitivo<double> Racional;
  typedef Primitivo<bool> Booleano;
  typedef Primitivo<char> Caracter;
  typedef Primitivo<string> Sentenca;

  // POLIMORFISMO

  class PrimitivoPolimorfo : public NodoPolimorfo<Primitivo>{
      public:
          template <typename U>
          NodoPolimorfo(Primitivo<U>* primitivo) : NodoPolimorfo<Primitivo>(primitivo){ }
  };

  typedef PrimitivoPolimorfo PrimitivoFundamental;

}
