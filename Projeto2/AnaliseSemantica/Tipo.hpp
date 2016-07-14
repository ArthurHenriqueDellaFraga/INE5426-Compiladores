#pragma once

#include "Geral/Polimorfo.hpp"

#include <map>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // ABSTRAÇÃO

  template <typename T = void>
  class TipoAbstrato{
      protected:
          string identificador;

          TipoAbstrato(string identificador) : identificador(identificador){ }

      public:
          void print(){
              cout << identificador;
          }

          string getIdentificador(){
              return identificador;
          }

          string getIdentificadorMasculino(){
              return identificador;
          }

          string getIdentificadorFeminino(){
              return identificador;
          };
  };

  //INSTANCIAÇÃO

  template <typename T = void>
  class Tipo : public TipoAbstrato<T>{
      public:
          Tipo() : TipoAbstrato<T>("desconhecido"){ }
  };

  template<>
  class Tipo<int> : public TipoAbstrato<int>{
      public:
          Tipo() : TipoAbstrato<int>("int"){ }
  };

  template<>
  class Tipo<double> : public TipoAbstrato<double>{
    public:
        Tipo() : TipoAbstrato<double>("double"){ }
  };

  template<>
  class Tipo<bool> : public TipoAbstrato<bool>{
      public:
          Tipo() : TipoAbstrato<bool>("bool"){ }
  };

  template<>
  class Tipo<char> : public TipoAbstrato<char>{
      public:
          Tipo() : TipoAbstrato<char>("char"){ }
  };

  template<>
  class Tipo<string> : public TipoAbstrato<string>{
      public:
          Tipo() : TipoAbstrato<string>("string"){ }
  };

  // POLIMORFISMO

  class TipoPolimorfo : public Polimorfo<Tipo>{
      public:
          template <typename U>
          TipoPolimorfo(Tipo<U>* tipo) : Polimorfo<Tipo>(tipo){ }

          static TipoPolimorfo* instanciar(string identificador){
              map<string, TipoPolimorfo*(*)()> _tipo;
                _tipo["int"] = &createTipo<int>;
                _tipo["double"] = &createTipo<double>;
                _tipo["bool"] = &createTipo<bool>;
                _tipo["char"] = &createTipo<char>;
                _tipo["string"] = &createTipo<string>;

                // map<string, TipoFundamental(*)()>::iterator it;
                // it = _tipo.find(identificador);
                //
                // if(it != _tipo.end()){
                //     throw new Erro("Tipo " + identificador + " não declarado");
                // }

                return _tipo[identificador]();
          }

          // template<typename U>
          // TipoPolimorfo& operator=(const Tipo<U>*& tipo){
          //     variant<Tipo<int>*, Tipo<double>*, Tipo<bool>*, Tipo<char>*, Tipo<string>*, Tipo<void>*>::operator=(tipo);
          //     return *this;
          // }

      protected:
          template <typename V>
          static TipoPolimorfo* createTipo(){
              return new TipoPolimorfo(new Tipo<V>());
          }
  };

  typedef TipoPolimorfo TipoFundamental;

}
