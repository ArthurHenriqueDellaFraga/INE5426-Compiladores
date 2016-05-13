#include "AnaliseSemantica/Contexto.hpp"

#include <iostream>

using namespace AnaliseSemantica;

Bloco* raizDoPrograma; //set on Bison file
Contexto* contexto;
bool debug = true;

extern int yyparse();

int main(int argc, char **argv){

    contexto = new Contexto();

    yyparse();                  //parses whole data
    raizDoPrograma->print();
    raizDoPrograma->executar(contexto);

    return 0;
}

template<typename T>
DefinicaoFundamental getDefinicao(string tipo, string identificador) {
    DefinicaoFundamental definicao;
    definicao = new Definicao<T>(tipo, identificador);

    return definicao;
};

DefinicaoFundamental definir(string tipo, string identificador){
    map<string, DefinicaoFundamental(*)(string, string)> _definicao;
        _definicao["int"] = &getDefinicao<int>;
        _definicao["double"] = &getDefinicao<double>;
        _definicao["bool"] = &getDefinicao<bool>;
        _definicao["char"] = &getDefinicao<char>;
        _definicao["string"] = &getDefinicao<string>;


    return _definicao[tipo](tipo, identificador);
}
