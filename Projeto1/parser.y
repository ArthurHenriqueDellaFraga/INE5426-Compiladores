%code requires{
    #include "AnaliseSemantica/Funcoes/Funcao.hpp"
    #include "AnaliseSemantica/Primitivo.hpp"
    #include "AnaliseSemantica/Funcoes/DefinicaoDeFuncao.hpp"
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

    extern Bloco<>* raizDoPrograma; /* the root node of our program */
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

    Bloco<>* bloco;
    NodoFundamental* nodo;

    VariavelFundamental* variavel;
    DefinicaoFundamental* definicao;
    AtribuicaoFundamental* atribuicao;

    FuncaoFundamental* funcao;
    vector<VariavelFundamental>* listaDeArgumentos;

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
%token DECLARACAO

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
%token <_string> RACIONAL
%token <_bool> BOOLEANO
%token <_char> CARACTER
%token <_string> SENTENCA

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

%type <variavel> variavel
%type <definicao> definicao
%type <nodo> atribuicao

%type <funcao> funcao
%type <listaDeArgumentos> listaDeArgumentos

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
            $$ = new Bloco<>(contexto);
            $$->addInstrucao(*$1);
    }

    | bloco instrucao NOVA_LINHA{
            if($2 != NULL)
                $1->addInstrucao(*$2);
    }

    | bloco NOVA_LINHA { }

    | bloco funcao NOVA_LINHA {
        $1->addInstrucao(*(new NodoFundamental(*$2)));
    }

instrucao
    : inteiro {
            $$ = new NodoFundamental($1);
    }

    | racional {
            $$ = new NodoFundamental($1);
    }

    | booleano {
            $$ = new NodoFundamental($1);
    }

    | caracter {
            $$ = new NodoFundamental($1);
    }

    | sentenca {
            $$ = new NodoFundamental($1);
    }

    | definicao {
            $$ = Nodo<>::converter(*$1);
    }

    | atribuicao {
            $$ = Nodo<>::converter(*$1);
    }

    | variavel {
            try{
                $1->checkInicializacao();
            }
            catch(Erro* erro){
                erro->print();
            }
            $$ = Nodo<>::converter(*$1);
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

inteiro
    : INTEIRO { $$ = new Inteiro($1); }

    | ABRE_PARENTESES inteiro FECHA_PARENTESES {
            $$ = new Parenteses<int>($2);
    }

racional
    : RACIONAL { $$ = new Racional(*$1); }

    | ABRE_PARENTESES racional FECHA_PARENTESES {
            $$ = new Parenteses<double>($2);
    }

booleano
    : BOOLEANO { $$ = new Booleano($1); }

    | ABRE_PARENTESES booleano FECHA_PARENTESES {
            $$ = new Parenteses<bool>($2);
    }

    | NEGACAO_BOOLEANA instrucao {
            $$ = NegacaoBooleana<>::instanciar(*$2);
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
            $$ = And<>::instanciar(*$1, *$3);
    }

    | instrucao OR instrucao {
            $$ = Or<>::instanciar(*$1, *$3);
    }

caracter
    : CARACTER { $$ = new Caracter($1); }

    | ABRE_PARENTESES caracter FECHA_PARENTESES {
            $$ = new Parenteses<char>($2);
    }

sentenca
    : SENTENCA { $$ = new Sentenca(*$1); }

    | ABRE_PARENTESES sentenca FECHA_PARENTESES {
            $$ = new Parenteses<string>($2);
    }

definicao
    : IDENTIFICADOR DEFINICAO IDENTIFICADOR {
            try{
                TipoFundamental tF;
                tF = Tipo<>::instanciar(*$1);

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
            $$ = contexto->getVariavel(*$1);
    }

funcao
    : DECLARACAO IDENTIFICADOR IDENTIFICADOR DEFINICAO IDENTIFICADOR listaDeArgumentos {
        $$ = new FuncaoFundamental();
    }

listaDeArgumentos
    : ABRE_PARENTESES definicao {
        $$ = new vector<VariavelFundamental>;
    }

%%
