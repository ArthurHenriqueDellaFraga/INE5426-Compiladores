%code requires{
    #include "AnaliseSemantica/Primitivo.hpp"
    #include "AnaliseSemantica/Operacao.hpp"
    #include "AnaliseSemantica/Definicao.hpp"
    #include "AnaliseSemantica/Atribuicao.hpp"

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
odoFundamental
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
%type <nodo> atribuicao

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
            NodoFundamental nF;
            nF = $1;
            $$ = &nF;
    }

    | racional {
            NodoFundamental nF;
            nF = $1;
            $$ = &nF;
    }

    | booleano {
            NodoFundamental nF;
            nF = $1;
            $$ = &nF;
    }

    | caracter {
            NodoFundamental nF;
            nF = $1;
            $$ = &nF;
    }

    | sentenca {
            NodoFundamental nF;
            nF = $1;
            $$ = &nF;
    }

    | definicao {
            NodoFundamental nF;
            nF = apply_visitor(NodoConversorVisitor(), *$1);
            $$ = &nF;
    }

    | atribuicao {
            NodoFundamental nF;
            nF = apply_visitor(NodoConversorVisitor(), *$1);
            $$ = &nF;
    }

    | variavel {
            NodoFundamental nF;
            nF = apply_visitor(NodoConversorVisitor(), *$1);
            $$ = &nF;
    }

inteiro
    : INTEIRO { $$ = new Inteiro($1); }

    | inteiro SOMA inteiro {
            $$ = new Soma_int_int($1, $3);
            if(debug) cout << "SOMA INTEIRA" << endl;
    }

    | inteiro SUBTRACAO inteiro {
            $$ = new Inteiro();
            if(debug) cout << "SUBTRACAO INTEIRA" << endl;
    }

    | inteiro MULTIPLICACAO inteiro {
            $$ = new Multiplicacao_int_int($1, $3);
            if(debug) cout << "MULTIPLICACAO INTEIRA" << endl;
    }

    | inteiro DIVISAO inteiro {
            $$ = new Inteiro();
            if(debug) cout << "DIVISAO INTEIRA" << endl;
    }

    | SUBTRACAO inteiro {
            $$ = new Inteiro();
            if(debug) cout << "SUBTRACAO UNARIA INTEIRA" << endl;
    }

    | ABRE_PARENTESES inteiro FECHA_PARENTESES {
            $$ = $2;
    }

racional
    : RACIONAL { $$ = new Racional($1); }

    | racional SOMA inteiro {
            $$ = new Soma_double_int($1, $3);
            if(debug) cout << "SOMA RACIONAL" << endl;
    }

    | inteiro SOMA racional {
            $$ = new Soma_double_int($3, $1);
            if(debug) cout << "SOMA RACIONAL" << endl;
    }

    | racional SOMA racional {
            $$ = new Soma_double_double($1, $3);
            if(debug) cout << "SOMA RACIONAL" << endl;
    }

    | racional SUBTRACAO inteiro {
            $$ = new Racional();
            if(debug) cout << "SUBTRACAO RACIONAL" << endl;
    }

    | inteiro SUBTRACAO racional {
            $$ = new Racional();
            if(debug) cout << "SUBTRACAO RACIONAL" << endl;
    }

    | racional SUBTRACAO racional {
            $$ = new Racional();
            if(debug) cout << "SUBTRACAO RACIONAL" << endl;
    }

    | racional MULTIPLICACAO inteiro {
            $$ = new Racional();
            if(debug) cout << "MULTIPLICACAO RACIONAL" << endl;
    }

    | inteiro MULTIPLICACAO racional {
            $$ = new Racional();
            if(debug) cout << "MULTIPLICACAO RACIONAL" << endl;
    }

    | racional MULTIPLICACAO racional {
            $$ = new Racional();
            if(debug) cout << "MULTIPLICACAO RACIONAL" << endl;
    }

    | racional DIVISAO inteiro {
            $$ = new Racional();
            if(debug) cout << "DIVISAO RACIONAL" << endl;
    }

    | inteiro DIVISAO racional {
            $$ = new Racional();
            if(debug) cout << "DIVISAO RACIONAL" << endl;
    }

    | racional DIVISAO racional {
            $$ = new Racional();
            if(debug) cout << "DIVISAO RACIONAL" << endl;
    }

    | SUBTRACAO racional {
            $$ = new Racional();
            if(debug) cout << "SUBTRACAO UNARIA RACIONAL" << endl;
    }

    | ABRE_PARENTESES racional FECHA_PARENTESES {
            $$ = $2;
    }

booleano
    : BOOLEANO { $$ = new Booleano($1); }

caracter
    : CARACTER { $$ = new Caracter($1); }

sentenca
    : SENTENCA { $$ = new Sentenca(*$1); }

definicao
    : TIPO IDENTIFICADOR {
            TipoFundamental tF;
            tF = Tipo<>::instanciar(*$1);

            // NodoFundamental cF;
            //     NodoFundamental nF;
            //       PrimitivoFundamental pF;
            //       pF = new Inteiro(5);
            //     nF = apply_visitor(NodoConversorVisitor(), pF);
            // cF = Conversao<int, int>::instanciar(tF, nF);
            // cF.print();

            DefinicaoFundamental dF;
            dF = Definicao<>::instanciar(tF, *$2);
            $$ = &dF;
    }
;

atribuicao
    : variavel ATRIBUICAO instrucao {
            NodoFundamental aF;
            try{
                aF = Atribuicao<>::instanciar(*$1, *$3);
            }
            catch(string* erro){
                cout << "Tipos incompativeis" << endl;
                exit(1);
            }
            $$ = &aF;
    }

variavel
    : IDENTIFICADOR {
            if(contexto->_variavel.find(*$1) != contexto->_variavel.end()){
                $$ = &(contexto->_variavel[*$1]);
            }
            else{
                cout << "Variavel não definida: " << *$1 << endl;
                exit(1);
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
