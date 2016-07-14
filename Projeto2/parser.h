/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser.y" /* yacc.c:1909  */

    #include "AnaliseSemantica/Bloco.hpp"

    #include "AnaliseSemantica/Primitivo.hpp"
    #include "AnaliseSemantica/Atribuicao.hpp"
    #include "AnaliseSemantica/Definicao.hpp"

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


    #include <stdio.h>
    #include <stdlib.h>

    using namespace boost;
    using namespace AnaliseSemantica;
    using namespace std;

    extern Bloco* raizDoPrograma; /* the root node of our program */
    extern Contexto* contexto;

    extern int yylex();
    extern void yyerror(const char* s, ...);

#line 87 "parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NOVA_LINHA = 258,
    ATRIBUICAO = 259,
    DEFINICAO = 260,
    SOMA = 261,
    SUBTRACAO = 262,
    MULTIPLICACAO = 263,
    DIVISAO = 264,
    IGUAL = 265,
    DIFERENTE = 266,
    MAIOR = 267,
    MENOR = 268,
    MAIOR_IGUAL = 269,
    MENOR_IGUAL = 270,
    AND = 271,
    OR = 272,
    NEGACAO_BOOLEANA = 273,
    PRINT = 274,
    VIRGULA = 275,
    PONTO = 276,
    ABRE_PARENTESES = 277,
    FECHA_PARENTESES = 278,
    ABRE_CHAVES = 279,
    FECHA_CHAVES = 280,
    ABRE_COLCHETE = 281,
    FECHA_COLCHETE = 282,
    IF = 283,
    ELSE = 284,
    INTEIRO = 285,
    RACIONAL = 286,
    BOOLEANO = 287,
    CARACTER = 288,
    SENTENCA = 289,
    IDENTIFICADOR = 290,
    errord = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 47 "parser.y" /* yacc.c:1909  */

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

#line 152 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
