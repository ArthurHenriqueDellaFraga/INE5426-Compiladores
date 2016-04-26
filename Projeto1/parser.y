%{
    #include "AnaliseSemantica/AnaliseSemantica.hpp"
    #include "AnaliseSemantica/Primitivo.hpp"
    #include "AnaliseSemantica/Operacao.hpp"

    #include <stdio.h>
    #include <stdlib.h>

    using namespace AnaliseSemantica;
    using namespace std;

    extern int yylex();
    extern void yyerror(const char* s, ...);

    Bloco *raizDoPrograma; /* the root node of our program */
    bool debug = true;
%}

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    int integer;
    string* string;

    Nodo<int>* nodo;
    Bloco* bloco;
}

// token defines our terminal symbols (tokens).

%token NOVA_LINHA

%token DEFINICAO
%token ATRIBUICAO

%token SOMA
%token SUBTRACAO
%token MULTIPLICACAO
%token DIVISAO

%token VIRGULA
%token PONTO

%token ABRE_PARENTESES FECHA_PARENTESES
%token ABRE_CHAVES FECHA_CHAVES

%token <integer> INTEIRO
%token <string> STRING

// type defines the type of our nonterminal symbols.

%type <bloco> program
%type <bloco> bloco
%type <nodo> instrucao

//%type <nodo> definicao
//%type <nodo> definicao_multipla
//%type <nodo> atribuicao

%type <nodo> inteiro


/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 */

%left ATRIBUICAO
%left DEFINICAO
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
;


bloco
    : instrucao {
            $$ = new Bloco();
            $$->listaDeInstrucoes.push_back($1);
    }

    | bloco instrucao {
            if($2 != NULL)
                $1->listaDeInstrucoes.push_back($2);
     }
;

instrucao
    : NOVA_LINHA { $$ = NULL; } /*nothing here to be used */
    | inteiro NOVA_LINHA
//    | definicao NOVA_LINHA
//    | definicao_multipla NOVA_LINHA
//    | atribuicao NOVA_LINHA
;

/*
definicao
    : DEFINICAO STRING {
            $$ = new Identificador(*$2);
            tabelaDeVariaveis[*$2] = VARIAVEL_INDEFINIDA;
            cout << "DEFINICAO" << endl;
    }
;

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

inteiro
    : INTEIRO { $$ = new Inteiro($1); }

    | inteiro SOMA inteiro {
            $$ = new Soma_int_int($1, $3);
            if(debug) cout << "SOMA" << endl;
    }

    | inteiro MULTIPLICACAO inteiro {
            $$ = new Multiplicacao_int_int($1, $3);
            if(debug) cout << "MULTIPLICACAO" << endl;
    }
;

/*
racional
    : RACIONAL { $$ = new Racional($1); }

    | racional SOMA inteiro {
            $$ = new Soma_double_int($1, $3);
            if(debug) cout << "SOMA" << endl;
    }

    | racional SOMA racional {
            $$ = new Soma_double_double($1, $3);
            if(debug) cout << "SOMA" << endl;
    }
;
*/
%%
