#pragma once

#include "Variavel.hpp"

using namespace std;

namespace AnaliseSemantica {

    class Contexto {
        protected:
            map<string, VariavelFundamental*> _variavel;
        public:
            Contexto(Contexto* contexto) : _variavel(contexto->_variavel){}
            Contexto(){ }

            void put(string identificador, VariavelFundamental* variavel){
                map<string, VariavelFundamental*>::iterator it;
                it = _variavel.find(identificador);

                if(it != _variavel.end()){
                    throw new Erro("variavel " + identificador + " sofrendo redefinicao");
                }

                _variavel[identificador] = variavel;
            }

            VariavelFundamental* getVariavel(string identificador){
                map<string, VariavelFundamental*>::iterator it;
                it = _variavel.find(identificador);

                if(it == _variavel.end()){
                    Erro* erro = new Erro("variavel " + identificador + " sem declaracao");
                    erro->print();

                    return new VariavelFundamental(new Variavel<void>(identificador));
                }

                return _variavel[identificador];
            }

    };
}
