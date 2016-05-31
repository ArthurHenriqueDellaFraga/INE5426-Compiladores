%code requires{
    #include "AnaliseSemantica/Bloco.hpp"
    #include "AnaliseSemantica/Primitivo.hpp"
    #include "AnaliseSemantica/Definicao.hpp"
    #include "AnaliseSemantica/Atribuicao.hpp"

    #include "AnaliseSemantica/Operacoes/OperacaoBooleana.hpp"
    #include "AnaliseSemantica/Operacoes/Soma.hpp"
    #include "AnaliseSemantica/Operacoes/Subtracao.hpp"
    #include "AnaliseSemantica/Operacoes/Multiplicacao.hpp"
    #include "AnaliseSemantica/Operacoes/Divisao.hpp"
    #include "AnaliseSemantica/Operacoes/Parenteses.hpp"

    #include "AnaliseSemantica/Arranjo.hpp"

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
    AtribuicaoFundamental* atribuicao;

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
%type <nodo> atribuicao

%type <variavel> variavel

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 */

%left AND
%left OR

%right NEGACAO_BOOLEANA

%left IGUAL DIFERENTE MAIOR MENOR MAIOR_IGUAL MENOR_IGUAL

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
    : NOVA_LINHA { }

    | instrucao NOVA_LINHA {
            $$ = new Bloco(contexto);
            $$->addInstrucao(*$1);
    }

    | bloco instrucao NOVA_LINHA{
            if($2 != NULL)
                $1->addInstrucao(*$2);
    }

    | bloco NOVA_LINHA { }

instrucao
    : ABRE_PARENTESES instrucao FECHA_PARENTESES {
            $$ = $2;
    }

    | inteiro {
            $$ = Nodo<>::converter($1);
    }

    | racional {
            $$ = Nodo<>::converter($1);
    }

    | booleano {
            $$ = Nodo<>::converter($1);
    }

    | caracter {
            $$ = Nodo<>::converter($1);
    }

    | sentenca {
            $$ = Nodo<>::converter($1);
    }

    | definicao {
            $$ = Nodo<>::converter(*$1);
    }

    | atribuicao {
            $$ = Nodo<>::converter(*$1);
    }

    | variavel {
            $$ = Nodo<>::converter(*$1);
    }

    | instrucao SOMA instrucao {
            NodoFundamental nF;

            try{
                nF = Soma<>::instanciar(*$1, *$3);
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
            $$ = &nF;
    }

    | instrucao SUBTRACAO instrucao {
            NodoFundamental nF;

            try{
                nF = Subtracao<>::instanciar(*$1, *$3);
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
            $$ = &nF;
    }

    | instrucao MULTIPLICACAO instrucao {
            NodoFundamental nF;

            try{
                nF = Multiplicacao<>::instanciar(*$1, *$3);
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
            $$ = &nF;
    }

    | instrucao DIVISAO instrucao {
            NodoFundamental nF;

            try{
                nF = Divisao<>::instanciar(*$1, *$3);
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
            $$ = &nF;
    }

inteiro
    : INTEIRO { $$ = new Inteiro($1); }

    | SUBTRACAO inteiro {
            $$ = new Subtracao_unaria<int>($2);
    }

    | ABRE_PARENTESES inteiro FECHA_PARENTESES {
            $$ = new Parenteses<int>($2);
    }

racional
    : RACIONAL { $$ = new Racional($1); }

    | SUBTRACAO racional {
            $$ = new Subtracao_unaria<double>($2);
    }

    | ABRE_PARENTESES racional FECHA_PARENTESES {
            $$ = new Parenteses<double>($2);
    }

booleano
    : BOOLEANO {
        $$ = new Booleano($1); }

    | NEGACAO_BOOLEANA instrucao {
        try{
            $$ = Negacao_booleana<>::instanciar(*$2);
        }
        catch(Erro* erro){
            erro->print();
            exit(1);
        }
    }

    | instrucao IGUAL instrucao {
        $$ = Igual<>::instanciar(*$1, *$3);
    }

    | instrucao DIFERENTE instrucao {
        $$ = Diferente<>::instanciar(*$1, *$3);
    }

    | instrucao MAIOR instrucao {
        $$ = Maior<>::instanciar(*$1, *$3);
    }

    | instrucao MENOR instrucao {
        $$ = Menor<>::instanciar(*$1, *$3);
    }

    | instrucao MAIOR_IGUAL instrucao {
        $$ = MaiorIgual<>::instanciar(*$1, *$3);
    }

    | instrucao MENOR_IGUAL instrucao {
        $$ = MenorIgual<>::instanciar(*$1, *$3);
    }

    | instrucao AND instrucao {
        try{
            $$ = And::instanciar(*$1, *$3);
        }
        catch(Erro* erro){
            erro->print();
            exit(1);
        }
    }

    | instrucao OR instrucao {
        try{
            $$ = Or<>::instanciar(*$1, *$3);
        }
        catch(Erro* erro){
            erro->print();
            exit(1);
        }
    }

caracter
    : CARACTER { $$ = new Caracter($1); }

sentenca
    : SENTENCA { $$ = new Sentenca(*$1); }

definicao
    : IDENTIFICADOR DEFINICAO IDENTIFICADOR {
            TipoFundamental tF;
            tF = Tipo<>::instanciar(*$1);

            try{
                $$ = Definicao<>::instanciar(tF, *$3);
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
    }

    | definicao VIRGULA IDENTIFICADOR {
            $$->add(*$3);
    }

    | IDENTIFICADOR ABRE_COLCHETE instrucao FECHA_COLCHETE DEFINICAO IDENTIFICADOR {
            TipoFundamental tF;
            tF = Tipo<>::instanciar(*$1);

            try{
                $$ = DefinicaoArranjo<>::instanciarArranjo(tF, *$3, *$6);
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
    }

atribuicao
    : variavel ATRIBUICAO instrucao {
            try{
                $$ = Atribuicao<int>::instanciar(*$1, *$3);
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
    }

    | IDENTIFICADOR ABRE_COLCHETE instrucao FECHA_COLCHETE ATRIBUICAO instrucao {
            try{
                ArranjoFundamental arranjo = contexto->getArranjo(*$1);

                $$ = AtribuicaoArranjo<int>::instanciarArranjo(arranjo, *$3, *$6);
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
    }

variavel
    : IDENTIFICADOR {
            try{
                VariavelFundamental vF;
                vF = contexto->getVariavel(*$1);
                $$ = &vF;
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }
    }

%%
