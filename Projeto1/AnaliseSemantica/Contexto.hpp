#pragma once

#include "AnaliseSemantica.hpp"
#include "Variavel.hpp"

#include <iostream>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    class Contexto {
        protected:
            map<string, TipoFundamental(*)()> _tipo;
        public:
            map<string, VariavelFundamental> _variavel;

            Contexto(){ }
    };
}
