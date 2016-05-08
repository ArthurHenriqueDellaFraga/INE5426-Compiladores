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

#line 66 "parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NOVA_LINHA = 258,
    ATRIBUICAO = 259,
    SOMA = 260,
    SUBTRACAO = 261,
    MULTIPLICACAO = 262,
    DIVISAO = 263,
    VIRGULA = 264,
    PONTO = 265,
    ABRE_PARENTESES = 266,
    FECHA_PARENTESES = 267,
    ABRE_CHAVES = 268,
    FECHA_CHAVES = 269,
    INTEIRO = 270,
    RACIONAL = 271,
    BOOLEANO = 272,
    CARACTER = 273,
    SENTENCA = 274,
    TIPO = 275,
    IDENTIFICADOR = 276,
    errord = 277
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 26 "parser.y" /* yacc.c:1909  */

    int _int;
    double _double;
    bool _bool;
    char _char;
    string* _string;

    Bloco* bloco;
    TipoFundamental* fundamental;

    Nodo<int>* inteiro;
    Nodo<double>* racional;
    Nodo<bool>* booleano;
    Nodo<char>* caracter;
    Nodo<string>* sentenca;
    Nodo<void>* vazio;

#line 119 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
