#pragma once

#include <map>
#include "Variavel.hpp"

using namespace std;

namespace AnaliseSemantica {

    class FuncaoPolimorfo;

    class Contexto {
        protected:
            map<string, VariavelFundamental*> _variavel;
            map<string, FuncaoPolimorfo*> _funcao;
            Contexto* antecessor;
        public:
            Contexto(Contexto* contexto) : antecessor(contexto){}
            Contexto(){ }

            void put(string identificador, VariavelFundamental* variavel){
                map<string, VariavelFundamental*>::iterator it;
                it = _variavel.find(identificador);

                if(it != _variavel.end()){
                    throw new Erro("variavel " + identificador + " sofrendo redefinicao");
                }

                _variavel[identificador] = variavel;
            }

            void put(string identificador, FuncaoPolimorfo* funcao){
                map<string, FuncaoPolimorfo*>::iterator it;
                it = _funcao.find(identificador);

                if(it != _funcao.end()){
                    Erro* erro = new Erro("funcao " + identificador + " sofrendo redefinicao");
                    erro->print();
                    throw erro;
                }

                _funcao[identificador] = funcao;
            }

            VariavelFundamental* getVariavel(string identificador){
                map<string, VariavelFundamental*>::iterator it;
                it = _variavel.find(identificador);

                if(it == _variavel.end()){
                    if(antecessor != NULL){
                        return antecessor->getVariavel(identificador);
                    }
                    else{
                        Erro* erro = new Erro("variavel " + identificador + " sem declaracao");
                        erro->print();
                        return new VariavelFundamental(new Variavel<void>(identificador));
                    }
                }

                return _variavel[identificador];
            }

            FuncaoPolimorfo* getFuncao(string identificador){
                map<string, FuncaoPolimorfo*>::iterator it;
                it = _funcao.find(identificador);

                if(it == _funcao.end()){
                    if(antecessor != NULL){
                        return antecessor->getFuncao(identificador);
                    }
                    else{
                        throw new Erro("funcao " + identificador + " sem declaracao");
                    }
                }

                return _funcao[identificador];
            }

            Contexto* getAntecessor(){
                if(antecessor != NULL){
                    return antecessor;
                }

                return this;
            }

            void print(){
                if(antecessor != NULL){
                    antecessor->print();
                }

                cout << this << "->";
            }

    };
}
