#pragma once

#include "Contexto.hpp"

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

            Atribuicao(Variavel<T>* variavel, Nodo<U>* valor) : variavel(variavel), valor(valor){
                static_assert(std::is_convertible<T, U>::value, "Atribuicao incompatível");
            }

            void print(){
                cout << "Atribuicao de valor para ";
                variavel->print();
                cout << ": ";
                valor-> print();
            }
            void executar(Contexto* contexto){
                variavel->setReferencia(new T(valor->executar(contexto)));
            }

            static NodoFundamental* instanciar(VariavelFundamental variavel, NodoFundamental valor){
                return apply_visitor(createVisitor (), variavel, valor);
            }

        protected:
            struct createVisitor : public static_visitor<NodoFundamental*>{
                template <typename V, typename W>
                NodoFundamental* operator()(Variavel<V>*& variavel, Nodo<W>*& valor) const {
                    throw new string("erro");

                }

                template <typename V>
                NodoFundamental* operator()(Variavel<V>*& variavel, Nodo<V>*& valor) const {
                    return new NodoFundamental(new Atribuicao<V>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<void>*& variavel, Nodo<void>*& valor) const {
                    throw new string("erro");
                }

                NodoFundamental* operator()(Variavel<int>*& variavel, Nodo<double>*& valor) const {
                    return new NodoFundamental(new Atribuicao<int, double>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<int>*& variavel, Nodo<bool>*& valor) const {
                    return new NodoFundamental(new Atribuicao<int, bool>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<int>*& variavel, Nodo<char>*& valor) const {
                    return new NodoFundamental(new Atribuicao<int, char>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<double>*& variavel, Nodo<int>*& valor) const {
                    return new NodoFundamental(new Atribuicao<double, int>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<double>*& variavel, Nodo<bool>*& valor) const {
                    return new NodoFundamental(new Atribuicao<double, bool>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<double>*& variavel, Nodo<char>*& valor) const {
                    return new NodoFundamental(new Atribuicao<double, char>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<bool>*& variavel, Nodo<int>*& valor) const {
                    return new NodoFundamental(new Atribuicao<bool, int>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<bool>*& variavel, Nodo<double>*& valor) const {
                    return new NodoFundamental(new Atribuicao<bool, double>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<char>*& variavel, Nodo<int>*& valor) const {
                    return new NodoFundamental(new Atribuicao<char, int>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<char>*& variavel, Nodo<double>*& valor) const {
                    return new NodoFundamental(new Atribuicao<char, double>(variavel, valor));
                }

                NodoFundamental* operator()(Variavel<char>*& variavel, Nodo<bool>*& valor) const {
                    return new NodoFundamental(new Atribuicao<char, bool>(variavel, valor));
                }
            };
    };
}
