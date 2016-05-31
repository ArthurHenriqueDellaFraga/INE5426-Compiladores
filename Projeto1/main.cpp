#include "AnaliseSemantica/Bloco.hpp"

#include <iostream>

using namespace AnaliseSemantica;

Bloco<>* raizDoPrograma; //set on Bison file
Contexto* contexto;
bool debug = true;

extern int yyparse();

int main(int argc, char **argv){

    contexto = new Contexto();

    try{
        yyparse();    //parses whole data
    }
    catch(Erro* erro){
        erro->print();
        exit(1);
    }

    cout << endl << endl;
    raizDoPrograma->print();
    //raizDoPrograma->executar(contexto);

    return 0;
}
