%code requires{
    #include "AnaliseSemantica/Primitivo.hpp"
    #include "AnaliseSemantica/Operacao.hpp"
    #include "AnaliseSemantica/Contexto.hpp"

    #include <stdio.h>
    #include <stdlib.h>

    #include "boost/variant.hpp"

    using namespace boost;
    using namespace AnaliseSemantica;
    using namespace std;

    extern Bloco* raizDoPrograma; /* the root node of our program */
    extern Contexto* contexto;
    extern bool debug;

    extern int yylex();
    extern void yyerror(const char* s, ...);
}

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    int _int;
    double _double;
    bool _bool;
    char _char;
    string* _string;

    Bloco* bloco;
    NodoFundamental* nodo;

    VariavelFundamental* variavel;
    DefinicaoFundamental* definicao;
    // AtribuicaoFundamental* atribuicao;

    Nodo<int>* inteiro;
    Nodo<double>* racional;
    Nodo<bool>* booleano;
    Nodo<char>* caracter;
    Nodo<string>* sentenca;
    Nodo<void>* vazio;
}

// token defines our terminal symbols (tokens).

%token NOVA_LINHA

%token ATRIBUICAO

%token SOMA
%token SUBTRACAO
%token MULTIPLICACAO
%token DIVISAO

%token IGUAL
%token DIFERENTE
%token MAIOR
%token MENOR
%token MAIOR_IGUAL
%token MENOR_IGUAL

%token AND
%token OR
%token NEGACAO_BOOLEANA

%token VIRGULA
%token PONTO

%token ABRE_PARENTESES FECHA_PARENTESES
%token ABRE_CHAVES FECHA_CHAVES

%token <_int> INTEIRO
%token <_double> RACIONAL
%token <_bool> BOOLEANO
%token <_char> CARACTER
%token <_string> SENTENCA

%token <_string> TIPO
%token <_string> IDENTIFICADOR

// type defines the type of our nonterminal symbols.

%type <bloco> program
%type <bloco> bloco
%type <nodo> instrucao

%type <inteiro> inteiro
%type <racional> racional
%type <booleano> booleano
%type <caracter> caracter
%type <sentenca> sentenca

%type <definicao> definicao
// %type <atribuicao> atribuicao

%type <variavel> variavel

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 */

%left SOMA
%left SUBTRACAO
%left MULTIPLICACAO
%left DIVISAO
%nonassoc errord

/* Gramatica Sintática */

%start program

%%

program
    : bloco { raizDoPrograma = $1; }


bloco
    : instrucao {
            $$ = new Bloco(contexto);
            $$->addInstrucao(*$1);
    }

    | bloco instrucao {
            if($2 != NULL)
                $1->addInstrucao(*$2);
    }

instrucao
    : NOVA_LINHA { $$ = NULL; }

    | inteiro NOVA_LINHA{
            NodoFundamental nF;
            nF = $1;
            $$ = &nF;
    }

    | racional NOVA_LINHA {
            NodoFundamental nF;
            nF = $1;
            $$ = &nF;
    }

    | booleano NOVA_LINHA {
            NodoFundamental nF;
            nF = $1;
            $$ = &nF;
    }

    | caracter NOVA_LINHA {
            NodoFundamental nF;
            nF = $1;
            $$ = &nF;
    }

    | sentenca NOVA_LINHA {
            NodoFundamental nF;
            nF = $1;
            $$ = &nF;
    }

    | definicao NOVA_LINHA {
            NodoFundamental nF;
            nF = apply_visitor(NodoConversorVisitor(), *$1);
            $$ = &nF;
    }

    // | atribuicao NOVA_LINHA {
    //         NodoFundamental nF;
    //         nF = new Primitivo<void>();
    //         $$ = &nF;
    // }

    | variavel NOVA_LINHA {
            NodoFundamental nF;
            nF = apply_visitor(NodoConversorVisitor(), *$1);
            $$ = &nF;
    }

inteiro
    : INTEIRO { $$ = new Inteiro($1); }

    | inteiro SOMA inteiro {
            $$ = new Soma_int_int($1, $3);
            if(debug) cout << "inteiro: SOMA" << endl;
    }

    | inteiro MULTIPLICACAO inteiro {
            $$ = new Multiplicacao_int_int($1, $3);
            if(debug) cout << "inteiro: MULTIPLICACAO" << endl;
    }

racional
    : RACIONAL { $$ = new Racional($1); }

    | racional SOMA inteiro {
            $$ = new Soma_double_int($1, $3);
            if(debug) cout << "racional: SOMA" << endl;
    }

    | inteiro SOMA racional {
            $$ = new Soma_double_int($3, $1);
            if(debug) cout << "racional: SOMA" << endl;
    }

    | racional SOMA racional {
            $$ = new Soma_double_double($1, $3);
            if(debug) cout << "racional: SOMA" << endl;
    }

booleano
    : BOOLEANO { $$ = new Booleano($1); }

caracter
    : CARACTER { $$ = new Caracter($1); }

sentenca
    : SENTENCA { $$ = new Sentenca(*$1); }

definicao
    : TIPO IDENTIFICADOR {
            DefinicaoFundamental dF;
            dF = Definicao<void>::definir(*$1, *$2);
            $$ = &dF;
    }
;

// atribuicao
//     : variavel ATRIBUICAO instrucao {
//         if(*$1.which() == *$3.which()){
//             AtribuicaoVisitor visitor;
//             visitor.valor = instrucao;
//
//             $$ = & apply_visitor(AtribuicaoVisitor (), variavel);
//         }
//         else{
//             cout << "Tipos incompativeis" << endl;
//         }
//     }

variavel
    : IDENTIFICADOR {
            if(contexto->_variavel.find(*$1) != contexto->_variavel.end()){
                $$ = &(contexto->_variavel[*$1]);
            }
            else{
                cout << "Variavel não definida: " << *$1 << endl;
                VariavelFundamental vF;
                vF = new Variavel<int>("null");
                $$ = &vF;
            }
    }
;
/*
definicao_multipla
    : definicao VIRGULA STRING {
            $$ = new Identificador(*$3);
            tabelaDeVariaveis[*$3] = VARIAVEL_INDEFINIDA;
            cout << "DEFINICAO" << endl;
    }
;

atribuicao
    : STRING ATRIBUICAO inteiro {
            if(tabelaDeVariaveis[*$1]){
              tabelaDeVariaveis[*$1] = $3->computeTree();
              cout << "ATRIBUICAO" << endl;
            } else{
              cout << "Variável '" << *$1 << "' não definida." << endl;
            }
    }

    | definicao ATRIBUICAO inteiro {

    }
;

*/
%%
