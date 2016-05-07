#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "boost/variant.hpp"

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    //class Contexto;

    template <typename T>
    class Nodo {
        public:
            // virtual ~Nodo();
            virtual void print() = 0;
            virtual T executar() = 0;
    };

    typedef variant<
        Nodo<int>*, Nodo<double>*,
        Nodo<bool>*,
        Nodo<char>*, Nodo<string>*,
        Nodo<void>*
    > TipoFundamental;
}
