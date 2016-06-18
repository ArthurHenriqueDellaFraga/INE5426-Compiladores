#include "AnaliseSemantica/Bloco.hpp"

#include <iostream>

using namespace AnaliseSemantica;

Bloco<>* raizDoPrograma; //set on Bison file
Contexto* contexto;

extern int yyparse();

int main(int argc, char **argv){

    contexto = new Contexto();

    try{
        cout << "Entre com o codigo" << endl;
        yyparse();
    }
    catch(Erro* erro){
        erro->print();
        cout << "main" << endl;
        exit(1);
    }

    cout << endl << endl;
    raizDoPrograma->print();
    //raizDoPrograma->executar(contexto);

    return 0;
}
