#pragma once

#include "Variavel.hpp"

using namespace std;

namespace AnaliseSemantica {

    class Contexto {
        protected:
            map<string, VariavelFundamental> _variavel;
        public:
            Contexto(){ }

            void put(string identificador, VariavelFundamental variavel){
                map<string, VariavelFundamental>::iterator it;
                it = _variavel.find(identificador);

                if(it != _variavel.end()){
                    throw new Erro("variavel sofrendo redefinicao");
                }

                _variavel[identificador] = variavel;
            }

            VariavelFundamental getVariavel(string identificador){
                map<string, VariavelFundamental>::iterator it;
                it = _variavel.find(identificador);

                if(it != _variavel.end()){
                    // char* mensagem = "";
                    // throw new Erro(mensagem);
                }

                return _variavel[identificador];
            }
    };
}
