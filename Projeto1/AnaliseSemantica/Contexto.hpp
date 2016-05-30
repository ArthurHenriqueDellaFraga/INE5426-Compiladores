#pragma once

#include "Variavel.hpp"
#include "Arranjo.hpp"

using namespace std;

namespace AnaliseSemantica {

    class Contexto {
        protected:
            map<string, VariavelFundamental> _variavel;
            map<string, ArranjoFundamental> _arranjo;
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

            void putArranjo(string identificador, ArranjoFundamental arranjo){
                map<string, ArranjoFundamental>::iterator it;
                it = _arranjo.find(identificador);

                if(it != _arranjo.end()){
                    throw new Erro("arranjo sofrendo redefinicao");
                }

                _arranjo[identificador] = arranjo;
            }

            ArranjoFundamental getArranjo(string identificador){
                map<string, ArranjoFundamental>::iterator it;
                it = _arranjo.find(identificador);

                if(it != _arranjo.end()){
                    // char* mensagem = "";
                    // throw new Erro(mensagem);
                }

                return _arranjo[identificador];
            }

    };
}
