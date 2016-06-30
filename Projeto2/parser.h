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

    #include "AnaliseSemantica/Operacoes/Parenteses.hpp"
    #include "AnaliseSemantica/Operacoes/Soma.hpp"
    #include "AnaliseSemantica/Operacoes/Subtracao.hpp"
    #include "AnaliseSemantica/Operacoes/Multiplicacao.hpp"
    #include "AnaliseSemantica/Operacoes/Divisao.hpp"

    #include "AnaliseSemantica/Operacoes/Igual.hpp"
    #include "AnaliseSemantica/Operacoes/Diferente.hpp"
    #include "AnaliseSemantica/Operacoes/Maior.hpp"
    #include "AnaliseSemantica/Operacoes/Menor.hpp"
    #include "AnaliseSemantica/Operacoes/MaiorIgual.hpp"
    #include "AnaliseSemantica/Operacoes/MenorIgual.hpp"

    #include "AnaliseSemantica/Operacoes/And.hpp"
    #include "AnaliseSemantica/Operacoes/Or.hpp"
    #include "AnaliseSemantica/Operacoes/NegacaoBooleana.hpp"


    #include <stdio.h>
    #include <stdlib.h>

    using namespace boost;
    using namespace AnaliseSemantica;
    using namespace std;

    extern Bloco* raizDoPrograma; /* the root node of our program */
    extern Contexto* contexto;

    extern int yylex();
    extern void yyerror(const char* s, ...);

#line 83 "parser.h" /* yacc.c:1909  */

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
    VIRGULA = 274,
    PONTO = 275,
    ABRE_PARENTESES = 276,
    FECHA_PARENTESES = 277,
    ABRE_CHAVES = 278,
    FECHA_CHAVES = 279,
    ABRE_COLCHETE = 280,
    FECHA_COLCHETE = 281,
    INTEIRO = 282,
    RACIONAL = 283,
    BOOLEANO = 284,
    CARACTER = 285,
    SENTENCA = 286,
    IDENTIFICADOR = 287,
    errord = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 43 "parser.y" /* yacc.c:1909  */

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

#line 145 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
