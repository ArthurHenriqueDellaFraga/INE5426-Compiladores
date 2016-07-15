#include "AnaliseSemantica/Bloco.hpp"

#include <iostream>
#include <vector>

using namespace AnaliseSemantica;

Bloco* raizDoPrograma; //set on Bison file
Contexto* contexto;

extern int yyparse();

int main(int argc, char **argv){

    contexto = new Contexto();

    try{
        yyparse();
    }
    catch(Erro* erro){
        erro->print();
        exit(1);
    }

    cout << endl << ":: Compilação ::" << endl;
    raizDoPrograma->print();
    cout << endl << ":: Execução ::" << endl;
    raizDoPrograma->executar(contexto);
    cout << endl;

    return 0;
}
