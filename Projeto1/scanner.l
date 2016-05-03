%{
    #include "parser.h"
    #include "AnaliseSemantica/AnaliseSemantica.hpp"

    #include <string>
    #include <boost/lexical_cast.hpp>

    using namespace std;

    extern int yylineno;
    void yyerror(const char* s, ...);


%}

%option noyywrap nodefault yylineno

digito [0-9]
letra [a-zA-Z]

%%

[ \t]                         ; //ignora espaços
\n                            {return NOVA_LINHA;}
";"                           {return NOVA_LINHA;}

"="                           {return ATRIBUICAO;}

"+"                           {return SOMA;}
"-"                           {return SUBTRACAO;}
"*"                           {return MULTIPLICACAO;}
":"                           {return DIVISAO;}

","                           {return VIRGULA;}
"."                           {return PONTO;}

"("                           {return ABRE_PARENTESES;}
")"                           {return FECHA_PARENTESES;}
"{"                           {return ABRE_CHAVES;}
"}"                           {return FECHA_CHAVES;}

{digito}+                     {yylval._int = atoi(yytext); return INTEIRO;}
{digito}+"."{digito}+         {yylval._double = atof(yytext); return RACIONAL;}
"TRUE"                        {yylval._bool = true; return BOOLEANO;}
"FALSE"                       {yylval._bool = false; return BOOLEANO;}
"\'"{letra}"\'"               {
                                  yylval._char = yytext[1];
                                  return CARACTER;
                              }
"\""{letra}+"\""              {
                                  yylval._string = new string(yytext);
                                  yylval._string = new string(yylval._string->substr(1, yylval._string->size() -2));
                                  return SENTENCA;
                              }
"int:"                        {return TIPO_INT;}

{letra}+                      {yylval._string = new string(yytext); return IDENTIFICADOR;}


.                             {yyerror("Caracter desconhecido: %c\n", *yytext);}

%%

void yyerror(const char *s, ...){
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "[Linha %d] Erro: ", yylineno);
    vfprintf(stderr, s, ap);
}
