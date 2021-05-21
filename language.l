%{
//#include "node.h"
#include <string>
#include "language.tab.h"
%}

WS          [ \t\n]+
LETTER      [a-z]
DIGIT       [0-9]
IDENTIFIER  {LETTER}({LETTER}|{DIGIT})*
NUMBER      {DIGIT}+
%option NOYYWRAP

%%

if                  {return IF;}
ifend               {return IFEND;}
else                {return ELSE;}
elsend              {return ELSEND;}
start               {return START;}
end                 {return END;}
point               {return POINT;}
rectangle           {return RECTANGLE;}
"["                 {return LB;}
"]"                 {return RB;}
"("                 {return LP;}
")"                 {return RP;}
"+"                 {return ADD;}
"-"                 {return SUBTRACT;}
"*"                 {return MULTIPLY;}
"%"                 {return MOD;}
"/"                 {return DIVIDE;}
","                 {return COMMA;}
";"                 {return SEMICOL;}
":"                 {return COL;}
"?"                 {return QUE;}
"^"                 {return VERT;}
">"                 {return GT;}
"<"                 {return LT;}
"="                 {return ASSIGN;}
"=="                {return EQ;}
"&&"                {return AND;}
"##"                {return OR;}
"!"                 {return NOT;}
{WS}                {;}
{IDENTIFIER}        {yylval.id = yytext; return IDENTIFIER;}
{NUMBER}            {yylval.value = atoi(/*&*/yytext/*[2]*/);return POSNUMBER;}
.                   {printf("\tSyntax Error!\n");}

%%

/*
TRALSE      [01]
"-@"{NUMBER}        {return NEGNUMBER;}
{TRALSE}            {return TRALSE;}
yeet                {return YEET;}
goto                {return YEET;}
*/
