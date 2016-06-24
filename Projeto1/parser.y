%code requires{
    #include "AnaliseSemantica/Bloco.hpp"

    #include "AnaliseSemantica/Primitivo.hpp"
    #include "AnaliseSemantica/Atribuicao.hpp"
    #include "AnaliseSemantica/Definicao.hpp"

    #include "AnaliseSemantica/Operacoes/OperacaoBooleana.hpp"
    #include "AnaliseSemantica/Operacoes/Soma.hpp"
    #include "AnaliseSemantica/Operacoes/Subtracao.hpp"
    #include "AnaliseSemantica/Operacoes/Multiplicacao.hpp"
    #include "AnaliseSemantica/Operacoes/Divisao.hpp"
    #include "AnaliseSemantica/Operacoes/Parenteses.hpp"

    #include <stdio.h>
    #include <stdlib.h>

    using namespace boost;
    using namespace AnaliseSemantica;
    using namespace std;

    extern Bloco* raizDoPrograma; /* the root node of our program */
    extern Contexto* contexto;

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

    PrimitivoFundamental* primitivo;
    VariavelFundamental* variavel;
    DefinicaoFundamental* definicao;
    AtribuicaoFundamental* atribuicao;
}

// token defines our terminal symbols (tokens).

%token NOVA_LINHA

%token ATRIBUICAO
%token DEFINICAO

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
%token ABRE_COLCHETE FECHA_COLCHETE

%token <_int> INTEIRO
%token <_double> RACIONAL
%token <_bool> BOOLEANO
%token <_char> CARACTER
%token <_string> SENTENCA

%token <_string> IDENTIFICADOR

// type defines the type of our nonterminal symbols.

%type <bloco> program
%type <bloco> bloco
%type <nodo> instrucao

%type <primitivo> primitivo
%type <variavel> variavel
%type <definicao> definicao
%type <atribuicao> atribuicao
%type <nodo> conversao

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 */

%left AND OR

%right NEGACAO_BOOLEANA

%left IGUAL DIFERENTE MAIOR MENOR MAIOR_IGUAL MENOR_IGUAL

%left SOMA SUBTRACAO
%left MULTIPLICACAO DIVISAO
%nonassoc errord

/* Gramatica Sintática */

%start program

%%

program
    : bloco { raizDoPrograma = $1; }

bloco
    : NOVA_LINHA { }

    | instrucao NOVA_LINHA {
            $$ = new Bloco(contexto);
            $$->addInstrucao($1);
    }

    | bloco instrucao NOVA_LINHA{
            if($2 != NULL)
                $1->addInstrucao($2);
            $$ = $1;
    }

    | bloco NOVA_LINHA { }

instrucao
    : primitivo {
            $$ = NodoPolimorfo<>::converter(*$1);
    }

    | variavel {
            $$ = NodoPolimorfo<>::converter(*$1);
    }

    | definicao {
            $$ = NodoPolimorfo<>::converter(*$1);
    }

    | atribuicao {
            $$ = NodoPolimorfo<>::converter(*$1);
    }

    | conversao {
            $$ = $1;
    }



    | ABRE_PARENTESES instrucao FECHA_PARENTESES {
            $$ = Parenteses<>::instanciar(*$2);
    }

    | instrucao SOMA instrucao {
            $$ = Soma<>::instanciar(*$1, *$3);
    }

    | instrucao SUBTRACAO instrucao {
            $$ = Subtracao<>::instanciar(*$1, *$3);
    }

    | SUBTRACAO instrucao {
            $$ = SubtracaoUnaria<>::instanciar(*$2);
    }

    | instrucao MULTIPLICACAO instrucao {
            $$ = Multiplicacao<>::instanciar(*$1, *$3);
    }

    | instrucao DIVISAO instrucao {
            $$ = Divisao<>::instanciar(*$1, *$3);
    }

primitivo
    : INTEIRO { $$ = new PrimitivoFundamental(new Primitivo<int>($1)); }

    | RACIONAL { $$ = new PrimitivoFundamental(new Primitivo<double>($1)); }

    | BOOLEANO { $$ = new PrimitivoFundamental(new Primitivo<bool>($1)); }

    | CARACTER { $$ = new PrimitivoFundamental(new Primitivo<char>($1)); }

    | SENTENCA { $$ = new PrimitivoFundamental(new Primitivo<string>(*$1)); }


definicao
    : IDENTIFICADOR DEFINICAO IDENTIFICADOR {
            try{
                TipoFundamental* tF = TipoFundamental::instanciar(*$1);

                $$ = DefinicaoFundamental::instanciar(*tF, *$3);
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
    }

    | definicao VIRGULA IDENTIFICADOR {
            $$->add(*$3);
    }

atribuicao
    : variavel ATRIBUICAO instrucao {
            try{
              $$ = AtribuicaoFundamental::instanciar($1, $3);
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
    }

variavel
    : IDENTIFICADOR {
            $$ = contexto->getVariavel(*$1);
    }

conversao
    : ABRE_PARENTESES IDENTIFICADOR FECHA_PARENTESES instrucao {
            TipoFundamental* tF = TipoFundamental::instanciar(*$2);

            $$ = Conversao<>::instanciar(*tF, *$4);
    }

%%
