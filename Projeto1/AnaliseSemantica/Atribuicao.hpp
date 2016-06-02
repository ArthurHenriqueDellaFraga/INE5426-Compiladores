#pragma once

#include "Conversao.hpp"
#include <boost/variant/multivisitors.hpp>

using namespace boost;
using namespace std;

namespace AnaliseSemantica {

    template <typename T = void, typename U = T>
    class Atribuicao;

    typedef Polimorfo<
        Atribuicao<int>*, Atribuicao<double>*,
        Atribuicao<bool>*,
        Atribuicao<char>*, Atribuicao<string>*,
        Atribuicao<void>*
    > AtribuicaoFundamental;

    template <typename T, typename U>
    class Atribuicao : public Nodo<void>{
        public:
            Variavel<T>* variavel;
            Nodo<U>* valor;

            Atribuicao() {}

            Atribuicao(Variavel<T>* variavel, Nodo<U>* valor) : variavel(variavel), valor(valor){
                //static_assert(std::is_convertible<T, U>::value, "Atribuicao incompatível");
            }

            void print(){
                cout << "Atribuicao de valor para ";
                variavel->print();
                cout << ": ";
                valor-> print();
            }
            void executar(Contexto* contexto){
                variavel->setReferencia();
                //variavel->setReferencia(new T(valor->executar(contexto)));
            }

            static NodoFundamental* instanciar(VariavelFundamental variavel, NodoFundamental valor){
                return apply_visitor(createVisitor (), variavel, valor);
            }

        protected:
            struct createVisitor : public static_visitor<NodoFundamental*>{
                template <typename V, typename W>
                NodoFundamental* operator()(Variavel<V>*& variavel, Nodo<W>*& valor) const {
                      VariavelFundamental* vF = new VariavelFundamental(variavel);
                      NodoFundamental* nF = new NodoFundamental(valor);

                      NodoFundamental* conversao = Conversao<>::instanciar(vF->getTipo(), *nF);
                      return Atribuicao<int>::instanciar(*vF, *conversao);
                }

                template <typename V>
                NodoFundamental* operator()(Variavel<V>*& variavel, Nodo<V>*& valor) const {
                    return new NodoFundamental(new Atribuicao<V>(variavel, valor));
                }

                template <typename V>
                NodoFundamental* operator()(Variavel<void>*& variavel, Nodo<V>*& valor) const {
                    return new NodoFundamental(new Atribuicao<void, V>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<void>*& variavel, Nodo<void>*& valor) const {
                    return new NodoFundamental(new Atribuicao<void>(variavel, valor));
                }
            };
    };
    template <typename T>
    class AtribuicaoArranjo : public Atribuicao<T>{
        public:
            Arranjo<T>* arranjo;
            Nodo<int>* indice;
            Nodo<T>* valor;
            AtribuicaoArranjo(Arranjo<T>* arranjo, Nodo<int>* indice, Nodo<T>* valor) : arranjo(arranjo), indice(indice), valor(valor){
            }
            void print(){
                cout << "Atribuicao de valor para ";
                arranjo->print();
                cout<< " " << arranjo->getIdentificador() << " ";
                cout << "{+indice: ";
                indice->print();
                cout <<"}: ";
                valor-> print();
            }

            void executar(Contexto* contexto){}

            static NodoFundamental* instanciarArranjo(ArranjoFundamental arranjo, NodoFundamental indice, NodoFundamental valor){
                return apply_visitor(createTipoVisitor (), arranjo, indice, valor);
            }

        protected:
            struct createTipoVisitor : public static_visitor<NodoFundamental*>{
                string errorMessage = "indice de arranjo espera inteiro mas rececebeu ";

                template <typename V, typename W>
                NodoFundamental* operator()(Arranjo<V>*& arranjo, Nodo<int>*& indice, Nodo<W>*& valor) const {
                      ArranjoFundamental* aF = new ArranjoFundamental(arranjo);
                      NodoFundamental* nF = new NodoFundamental(valor);
                      NodoFundamental* iF = new NodoFundamental(indice);

                      NodoFundamental* conversao = Conversao<>::instanciar(aF->getTipo(), *nF);
                      return AtribuicaoArranjo<V>::instanciarArranjo(*aF, *iF, *conversao);
                }

                template <typename V>
                NodoFundamental* operator()(Arranjo<V>*& arranjo, Nodo<int>*& indice, Nodo<V>*& valor) const {
                    return new NodoFundamental(new AtribuicaoArranjo<V>(arranjo, indice, valor));
                }

                template <typename V,typename I, typename W>
                NodoFundamental* operator()(Arranjo<V>*& arranjo, Nodo<I>*& indice, Nodo<W>*& valor) const {
                    throw new Erro(errorMessage + indice->getTipo()->getIdentificadorMasculino() + ".");
                }

            };
    };
}
