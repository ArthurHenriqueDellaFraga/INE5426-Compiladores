#include "AnaliseSemantica/Bloco.hpp"

#include <iostream>
#include <vector>

using namespace AnaliseSemantica;

Bloco* raizDoPrograma; //set on Bison file
vector<Contexto*> contexto;

extern int yyparse();

int main(int argc, char **argv){

    contexto.push_back(new Contexto());

    try{
        yyparse();
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
