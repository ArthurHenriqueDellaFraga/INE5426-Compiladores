#pragma once

#include "boost/variant.hpp"

#include <map>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <typename T = void>
  class TipoAbstrato {
      protected:
          string identificadorMasculino;
          string identificadorFeminino;

          TipoAbstrato(string identificadorMasculino, string identificadorFeminino)
          : identificadorMasculino(identificadorMasculino), identificadorFeminino(identificadorFeminino){ }

      public:
          string getIdentificadorMasculino(){
              return identificadorMasculino;
          }

          string getIdentificadorFeminino(){
              return identificadorFeminino;
          };
  };

  template <typename T>
  class Tipo;

  typedef variant<
      Tipo<int>*, Tipo<double>*,
      Tipo<bool>*,
      Tipo<char>*, Tipo<string>*,
      Tipo<void>*
  > TipoFundamental;

  template <typename T = void>
  class Tipo : public TipoAbstrato<T>{
      public:
          Tipo() : TipoAbstrato<T>("desconhecido", "desconhecida"){ }

          static TipoFundamental instanciar(string identificador){
              map<string, TipoFundamental(*)()> _tipo;
                _tipo["int"] = &createTipo<int>;
                _tipo["double"] = &createTipo<double>;
                    _tipo["real"] = &createTipo<double>;
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

      protected:
          template <typename V>
          static TipoFundamental createTipo(){
              TipoFundamental tipo;
              tipo = new Tipo<V>();
              return tipo;
          }
  };

  template<>
  class Tipo<int> : public TipoAbstrato<int>{
      public:
          Tipo() : TipoAbstrato<int>("inteiro", "inteira"){ }
  };

  template<>
  class Tipo<double> : public TipoAbstrato<double>{
    public:
        Tipo() : TipoAbstrato<double>("real", "real"){ }
  };

  template<>
  class Tipo<bool> : public TipoAbstrato<bool>{
      public:
          Tipo() : TipoAbstrato<bool>("boleano", "boleana"){ }
  };

  template<>
  class Tipo<char> : public TipoAbstrato<char>{
      public:
          Tipo() : TipoAbstrato<char>("char", "char"){ }
  };

  template<>
  class Tipo<string> : public TipoAbstrato<string>{
      public:
          Tipo() : TipoAbstrato<string>("string", "string"){ }
  };

}
