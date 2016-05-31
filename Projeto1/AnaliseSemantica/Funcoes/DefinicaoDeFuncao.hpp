#pragma once

#include "../Definicao.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  template <template <typename U> class T>
  class Definicao : public Nodo<T<U>>{
      public:
          Definicao(){ }

          void print(){

          }

  }

}
