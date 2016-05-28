#pragma once

#include <iostream>
#include <vector>

using namespace std;

extern int yylineno;

namespace AnaliseSemantica {

    struct Erro {
        //void (*yy) (const char* s, ...) = &yyerror;
        vector<string> listaDeMensagens;

        Erro(string mensagem){
            add(mensagem);
        }

        void print(){
            for(int i = 0; i < listaDeMensagens.size(); i++){
                printf("[Linha %d] Erro semantico: ", yylineno);
                cout << listaDeMensagens[i] << endl;
            }
        }

        void add(string mensagem){
            listaDeMensagens.push_back(mensagem);
        }
    };



}
