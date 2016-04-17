%{
  #include "ast.h"

  #include <stdio.h>
  #include <stdlib.h>

  using namespace AST;
  using namespace std;

  extern int yylex();
  extern void yyerror(const char* s, ...);

  #define VARIAVEL_INDEFINIDA -666;

  AST::Block *raizDoPrograma; /* the root node of our program */
  bool debug = true;
%}

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    int integer;
    std::string *string;

    AST::Node *node;
    AST::Block *block;
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

%token ABRE_PARENTESES FECHA_PARENTESES
%token ABRE_CHAVES FECHA_CHAVES

%token <integer> INTEIRO
%token <string> STRING

// type defines the type of our nonterminal symbols.

%type <block> programa
%type <block> bloco
%type <node> linha

%type <node> definicao
%type <node> definicao_multipla
%type <node> atribuicao

%type <node> inteiro


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

programa
    : bloco { raizDoPrograma = $1; }
;


bloco
    : instrucao {
            $$ = new Block();
            $$->linhas.push_back($1);
    }

    | bloco instrucao {
            if($2 != NULL)
              $1->linhas.push_back($2);
     }
;

instrucao
    : NOVA_LINHA { $$ = NULL; } /*nothing here to be used */
    | inteiro NOVA_LINHA
    | definicao NOVA_LINHA
    | definicao_multipla NOVA_LINHA
    | atribuicao NOVA_LINHA
;

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

inteiro
    : INTEIRO { $$ = new Integer($1); }

    | inteiro SOMA inteiro {
            $$ = new BinOp($1, AST::plus,$3);
            if(debug) cout << "SOMA" << endl;
    }

    | inteiro MULTIPLICACAO inteiro {
            $$ = new BinOp($1, AST::mult, $3);
            if(debug) cout << "MULTIPLICACAO" << endl;
    }
;

%%