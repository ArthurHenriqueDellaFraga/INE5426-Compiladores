#pragma once

#include "../Nodo.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

  // INSTANCIAÇÃO

  class Comentario : public Nodo<void>{
      protected:
          string texto;
      public:
          Comentario(string texto) : texto(texto){ }

          void print(){
              cout << texto;
          }

          void executar(Contexto* contexto){
              cout << texto << endl;
          }
  };

}
