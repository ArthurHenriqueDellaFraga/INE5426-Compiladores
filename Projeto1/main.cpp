#include "AnaliseSemantica/Contexto.hpp"

#include <iostream>

using namespace AnaliseSemantica;

Bloco* raizDoPrograma; //set on Bison file
bool debug = true;

extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();                  //parses whole data
    raizDoPrograma->print();
    raizDoPrograma->executar();

    return 0;
}
