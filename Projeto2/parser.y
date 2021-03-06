%code requires{
    #include "AnaliseSemantica/Bloco.hpp"

    #include "AnaliseSemantica/Primitivo.hpp"
    #include "AnaliseSemantica/Atribuicao.hpp"
    #include "AnaliseSemantica/Definicao.hpp"

    #include "AnaliseSemantica/Geral/Comentario.hpp"

    #include "AnaliseSemantica/Operacao/Parenteses.hpp"
    #include "AnaliseSemantica/Operacao/Imprimir.hpp"

    #include "AnaliseSemantica/Operacao/Matematica/Soma.hpp"
    #include "AnaliseSemantica/Operacao/Matematica/Subtracao.hpp"
    #include "AnaliseSemantica/Operacao/Matematica/Multiplicacao.hpp"
    #include "AnaliseSemantica/Operacao/Matematica/Divisao.hpp"

    #include "AnaliseSemantica/Operacao/Comparacao/Igual.hpp"
    #include "AnaliseSemantica/Operacao/Comparacao/Diferente.hpp"
    #include "AnaliseSemantica/Operacao/Comparacao/Maior.hpp"
    #include "AnaliseSemantica/Operacao/Comparacao/Menor.hpp"
    #include "AnaliseSemantica/Operacao/Comparacao/MaiorIgual.hpp"
    #include "AnaliseSemantica/Operacao/Comparacao/MenorIgual.hpp"

    #include "AnaliseSemantica/Operacao/Logica/And.hpp"
    #include "AnaliseSemantica/Operacao/Logica/Or.hpp"
    #include "AnaliseSemantica/Operacao/Logica/NegacaoBooleana.hpp"

    #include "AnaliseSemantica/Condicao/If.hpp"
    #include "AnaliseSemantica/Condicao/While.hpp"
    #include "AnaliseSemantica/Condicao/For.hpp"
    #include "AnaliseSemantica/Condicao/Repeat.hpp"

    #include "AnaliseSemantica/Funcao/DefinicaoDeFuncao.hpp"
    #include "AnaliseSemantica/Funcao/ChamadaDeFuncao.hpp"
    #include "AnaliseSemantica/Funcao/Retorno.hpp"


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

    DefinicaoDeFuncaoFundamental* definicao_funcao;
    vector<DefinicaoFundamental*>* argumentos_funcao;

    ChamadaDeFuncaoFundamental* chamada_funcao;
    vector<NodoFundamental*>* argumentos;
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

%token PRINT

%token VIRGULA
%token PONTO

%token ABRE_PARENTESES FECHA_PARENTESES
%token ABRE_CHAVES FECHA_CHAVES
%token ABRE_COLCHETE FECHA_COLCHETE

%token IF ELSE WHILE FOR REPEAT

%token RETORNO

%token <_int> INTEIRO
%token <_double> RACIONAL
%token <_bool> BOOLEANO
%token <_char> CARACTER
%token <_string> SENTENCA

%token <_string> IDENTIFICADOR
%token <_string> COMENTARIO

// type defines the type of our nonterminal symbols.

%type <bloco> program
%type <bloco> bloco
%type <bloco> bloco_fechado
%type <nodo> instrucao

%type <primitivo> primitivo
%type <variavel> variavel
%type <definicao> definicao
%type <atribuicao> atribuicao

%type <nodo> operacao
%type <nodo> conversao
%type <nodo> condicao

%type<definicao_funcao> definicao_funcao
%type<definicao_funcao> assinatura_funcao
%type<argumentos_funcao> argumentos_funcao

%type<chamada_funcao> chamada_funcao
%type<argumentos> argumentos

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
    : bloco {
            contexto = contexto->getAntecessor();
            raizDoPrograma = $1;
    }

bloco_fechado
    : ABRE_CHAVES bloco FECHA_CHAVES {
            $$ = $2;
            contexto = contexto->getAntecessor();
    }

bloco
    : NOVA_LINHA { }

    | instrucao NOVA_LINHA {
            $$ = new Bloco();
            contexto = new Contexto(contexto);

            $$->addInstrucao($1);
    }

    | bloco instrucao NOVA_LINHA{
            if($2 != NULL){
                $1->addInstrucao($2);
            }
            $$ = $1;
    }

    | definicao NOVA_LINHA {
            $$ = new Bloco();
            contexto = new Contexto(contexto);

            try{
                $1->executar(contexto);
                //$2->print();
                // cout << endl;
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }

            $$->addInstrucao(NodoPolimorfo<>::converter(*$1));
    }

    | bloco definicao NOVA_LINHA{
            if($2 != NULL){
                try{
                    $2->executar(contexto);
                    //$2->print();
                    // cout << endl;
                }
                catch(Erro* erro){
                    erro->print();
                    exit(1);
                }

                $1->addInstrucao(NodoPolimorfo<>::converter(*$2));
            }
            $$ = $1;
    }

    | definicao_funcao NOVA_LINHA {
            $$ = new Bloco();
            contexto = new Contexto(contexto);

            try{
                $1->executar(contexto);
                //$2->print();
                // cout << endl;
            }
            catch(Erro* erro){
                erro->print();
                exit(1);
            }

            $$->addInstrucao(NodoPolimorfo<>::converter(*$1));
    }

    | bloco definicao_funcao NOVA_LINHA{
            if($2 != NULL){
                try{
                    $2->executar(contexto);
                    //$2->print();
                    // cout << endl;
                }
                catch(Erro* erro){
                    erro->print();
                    exit(1);
                }

                $1->addInstrucao(NodoPolimorfo<>::converter(*$2));
            }
            $$ = $1;
    }

    | bloco NOVA_LINHA { }

    | bloco COMENTARIO {
            $1->addInstrucao(new NodoFundamental(new Comentario(*$2)));
    }

instrucao
    : primitivo {
            $$ = NodoPolimorfo<>::converter(*$1);
    }

    | variavel {
            $$ = NodoPolimorfo<>::converter(*$1);
    }

    | atribuicao {
            $$ = NodoPolimorfo<>::converter(*$1);
    }

    | conversao {
            $$ = $1;
    }

    | operacao {
            $$ = $1;
    }

    | condicao {
            $$ = $1;
    }

    | chamada_funcao {
            $$ = NodoPolimorfo<>::converter(*$1);
    }

    | RETORNO instrucao {
            $$ = Retorno<int>::instanciar($2);
    }

primitivo
    : INTEIRO { $$ = new PrimitivoFundamental(new Primitivo<int>($1)); }

    | RACIONAL { $$ = new PrimitivoFundamental(new Primitivo<double>($1)); }

    | BOOLEANO { $$ = new PrimitivoFundamental(new Primitivo<bool>($1)); }

    | CARACTER { $$ = new PrimitivoFundamental(new Primitivo<char>($1)); }

    | SENTENCA { $$ = new PrimitivoFundamental(new Primitivo<string>(*$1)); }

definicao
    : DEFINICAO IDENTIFICADOR IDENTIFICADOR {
            try{
                TipoFundamental* tF = TipoFundamental::instanciar(*$2);

                $$ = DefinicaoFundamental::instanciar(tF, *$3);
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

    | variavel SOMA ATRIBUICAO instrucao {
            NodoFundamental* nodo = NodoPolimorfo<>::converter(*$1);
            nodo = Soma<int, int, int>::instanciar(nodo, $4);

            $$ = AtribuicaoFundamental::instanciar($1, nodo);
    }

    | variavel SUBTRACAO ATRIBUICAO instrucao {
            NodoFundamental* nodo = NodoPolimorfo<>::converter(*$1);
            nodo = Subtracao<int, int, int>::instanciar(nodo, $4);

            $$ = AtribuicaoFundamental::instanciar($1, nodo);
    }

    | variavel MULTIPLICACAO ATRIBUICAO instrucao {
            NodoFundamental* nodo = NodoPolimorfo<>::converter(*$1);
            nodo = Multiplicacao<int, int, int>::instanciar(nodo, $4);

            $$ = AtribuicaoFundamental::instanciar($1, nodo);
    }

    | variavel DIVISAO ATRIBUICAO instrucao {
            NodoFundamental* nodo = NodoPolimorfo<>::converter(*$1);
            nodo = Divisao<int, int, int>::instanciar(nodo, $4);

            $$ = AtribuicaoFundamental::instanciar($1, nodo);
    }

variavel
    : IDENTIFICADOR {
            $$ = contexto->getVariavel(*$1);
    }

conversao
    : ABRE_PARENTESES IDENTIFICADOR FECHA_PARENTESES instrucao {
            TipoFundamental* tF = TipoFundamental::instanciar(*$2);

            $$ = Conversao<>::instanciar(tF, $4);
    }

operacao
    : ABRE_PARENTESES instrucao FECHA_PARENTESES {
            $$ = Parenteses<int>::instanciar($2);
    }

    | instrucao SOMA instrucao {
            $$ = Soma<int, int, int>::instanciar($1, $3);
    }

    | SOMA instrucao {
            $$ = Soma<int>::instanciar($2);
    }

    | instrucao SUBTRACAO instrucao {
            $$ = Subtracao<int, int, int>::instanciar($1, $3);
    }

    | SUBTRACAO instrucao {
            $$ = Subtracao<int>::instanciar($2);
    }

    | instrucao MULTIPLICACAO instrucao {
            $$ = Multiplicacao<int, int, int>::instanciar($1, $3);
    }

    | instrucao DIVISAO instrucao {
            $$ = Divisao<int, int, int>::instanciar($1, $3);
    }



    | instrucao IGUAL instrucao {
            $$ = Igual<bool>::instanciar($1, $3);
    }

    | instrucao DIFERENTE instrucao {
            $$ = Diferente<bool>::instanciar($1, $3);
    }

    | instrucao MAIOR instrucao {
            $$ = Maior<bool>::instanciar($1, $3);
    }

    | instrucao MENOR instrucao {
            $$ = Menor<bool>::instanciar($1, $3);
    }

    | instrucao MAIOR_IGUAL instrucao {
            $$ = MaiorIgual<bool>::instanciar($1, $3);
    }

    | instrucao MENOR_IGUAL instrucao {
            $$ = MenorIgual<bool>::instanciar($1, $3);
    }



    | instrucao AND instrucao {
            $$ = And::instanciar($1, $3);
    }

    | instrucao OR instrucao {
            $$ = Or::instanciar($1, $3);
    }

    | NEGACAO_BOOLEANA instrucao {
            $$ = NegacaoBooleana::instanciar($2);
    }



    | PRINT instrucao {
            $$ = Imprimir<char>::instanciar($2);
    }

condicao
    : IF ABRE_PARENTESES instrucao FECHA_PARENTESES bloco_fechado {
            $$ = If::instanciar($3, $5, NULL);
    }

    | IF ABRE_PARENTESES instrucao FECHA_PARENTESES bloco_fechado ELSE bloco_fechado {
            $$ = If::instanciar($3, $5, $7);
    }

    | WHILE ABRE_PARENTESES instrucao FECHA_PARENTESES bloco_fechado {
            $$ = While::instanciar($3, $5);
    }

    | FOR ABRE_PARENTESES variavel NOVA_LINHA instrucao NOVA_LINHA atribuicao FECHA_PARENTESES bloco_fechado {
            $$ = For::instanciar($3, $5, $7, $9);
    }

    | REPEAT ABRE_PARENTESES instrucao FECHA_PARENTESES bloco_fechado {
            $$ = Repeat::instanciar($3, $5);
    }

definicao_funcao
    : assinatura_funcao bloco_fechado {
            $1->add($2);
            $$ = $1;
            contexto = contexto->getAntecessor();
    }

assinatura_funcao
    : DEFINICAO IDENTIFICADOR IDENTIFICADOR ABRE_PARENTESES argumentos_funcao FECHA_PARENTESES{
            TipoFundamental* tF = TipoFundamental::instanciar(*$2);
            $$ = DefinicaoDeFuncaoFundamental::instanciar(tF, *$3, *$5);

            contexto = new Contexto(contexto);
            for(int i = 0; i < $5->size(); i++){
                $5->at(i)->executar(contexto);
            }
    }

argumentos_funcao
    : definicao {
            $$ = new vector<DefinicaoFundamental*>();
            $$->push_back($1);
    }

    | definicao VIRGULA argumentos_funcao {
            $3->insert($3->begin(), $1);
            $$ = $3;
    }

chamada_funcao
    : IDENTIFICADOR ABRE_PARENTESES argumentos FECHA_PARENTESES {
            FuncaoFundamental* funcao = contexto->getFuncao(*$1);
            $$ = ChamadaDeFuncaoFundamental::instanciar(funcao, *$3);
    }

argumentos
    : instrucao {
            $$ = new vector<NodoFundamental*>();
            $$->push_back($1);
      }

      | instrucao VIRGULA argumentos {
            $3->insert($3->begin(), $1);
            $$ = $3;
      }


%%
