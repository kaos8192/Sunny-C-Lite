%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include <map>
#include <vector>
#include <string>
#include "symtab.h"
#include "gAll.h"
#include "opcodes.h"
#include "helper.h"

//map<string,int> symTabEnt;
//vector<Symbol> symTabEnt;
SymbolTable slap;
//Code_Vect chonk;
LabelTable lit;

extern std::vector<int> bytes;


extern int yylex();
extern int yyparse();
void yyerror(const char* msg);
%}

%union
{
    int value;
    char* id;
    struct Node *node;
    struct Constant *constant;
    struct Identifier * identifier;
}

%type<node> start starta stmt /*expr*/ iter /*jump*/ /*jumpstart*/ /*jumpend*/ select shape assignment /*return*/ value /*coord*/ bool compa arith id;


%token  <id> IDENTIFIER
%token  <value> POSNUMBER
//%token  <value> NEGNUMBER
%token  COMMA
%token  SEMICOL
%token  QUE
%token  VERT
%token  COL
%token  LB
%token  RB
%token  LP
%token  RP
%token  EQ
%token  LT
%token  GT
%token  AND
%token  OR
%token  NOT
%token  START
%token  END
%token  IF
%token  IFEND
%token  ELSE
%token  ELSEND
%token  ADD
%token  SUBTRACT
%token  MOD
%token  MULTIPLY
%token  DIVIDE
%token  POINT
%token  RECTANGLE
%token  ASSIGN
//%token  TRALSE 

%define parse.error verbose

%%
prog        :   start       {/*$1->visit(0);*/$1->generate_code(); print_program();}     
            ;

start       :   starta      {Node * n = new Node("start"); n->add_child($1);$$=n;}
            ;

starta      :   stmt starta  {Node* n = new Node("starta"); n->add_child($1); n->add_child($2); $$ = n;}
            |   VERT stmt          {Node* n = new Node("starta"); n->add_child($2); $$ = n;}
            |   COL VERT SEMICOL {Node* n = new Node("starta");$$=n;}
            ;

stmt        :   bool        {Node* n = new Node("stmt"); n->add_child($1);$$ = n;}
            |   shape       {Node* n = new Node("stmt"); n->add_child($1);$$ = n;}
            |   select      {Node* n = new Node("stmt"); n->add_child($1);$$ = n;}
            |   iter        {Node* n = new Node("stmt"); n->add_child($1);$$ = n;}
            |   assignment  {Node* n = new Node("stmt"); n->add_child($1);$$ = n;}
            ;

iter        :   LB START LP bool RP RB starta LB END RB {Node* n = new Node("iter"); n->add_child($4);n->add_child($7);$$ = n;}
            ;

id          :   IDENTIFIER      {/*sta_abs($1);*/Identifier* i = new Identifier("identifier");i->set_value($1);/*printf("%s\n",$1)*/;$$ = i;}       ;

            
select      :   QUE LB IF LP bool RP RB starta LB IFEND RB {Node* n = new Node("select");n->add_child($5);n->add_child($8);$$ = n;}
            |   SEMICOL LB IF LP bool RP RB starta LB IFEND RB LB ELSE RB starta LB ELSEND RB {Node* n = new Node("select");n->add_child($5);n->add_child($8);n->add_child($15);$$ = n;}
            ;

shape       :   LB POINT LP LP value COMMA value RP RP RB {Node* n = new Node("shape");n->add_child($5);n->add_child($7);$$ = n;}
            |   LB RECTANGLE LP LP value COMMA value RP COMMA value COMMA value RP RB {Node* n = new Node("shape");n->add_child($5);n->add_child($7);n->add_child($10);n->add_child($12);$$ = n;}
            ;

assignment  :   COL LB id ASSIGN arith RB    {/*slap.add($2);*/Node* n = new Node("assignment");n->add_child($3);n->add_child($5);$$ = n;}
            ;

value       :   POSNUMBER               {/*sta_abs($1);*/Constant* c = new Constant("postant"); c->set_value($1);/*printf("%d\n",$1);*/ $$ = c;}
//            |   NEGNUMBER               {/*sta_abs($1);*/Node* n = new Node("negatant");$$ = n;}
            |   id                      {/*sta_abs($1);*/Node* n = new Node("value");n->add_child($1);$$ = n;}
//            |   TRALSE                  {Node* n = new Node("boolant");$$ = n;}
            ;

bool        :   compa                   {Node* n = new Node("bool");n->add_child($1);$$ = n;}
            |   NOT bool                {Node* n = new Node("not");n->add_child($2);$$ = n;}
            |   bool  OR  compa         {Node* n = new Node("or");n->add_child($1);n->add_child($3);$$ = n;}
            |   bool  AND  compa        {Node* n = new Node("and");n->add_child($1);n->add_child($3);$$ = n;}
            ;

compa       :   arith                   {Node* n = new Node("compa");n->add_child($1);$$ = n;}
            |   compa  EQ  arith        {Node* n = new Node("eq");n->add_child($1);n->add_child($3);$$ = n;}
            |   compa  LT  arith        {Node* n = new Node("lt");n->add_child($1);n->add_child($3);$$ = n;}
            |   compa  GT  arith        {Node* n = new Node("gt");n->add_child($1);n->add_child($3);$$ = n;}
            ;

arith       :   value                   {Node* n = new Node("arith");n->add_child($1);$$ = n;}
            |    value  MULTIPLY  value {Node* n = new Node("mult");n->add_child($1);n->add_child($3);$$ = n;}
            |    value  DIVIDE  value    {Node* n = new Node("div");n->add_child($1);n->add_child($3);$$ = n;}
            |    value  MOD  value       {Node* n = new Node("mod");n->add_child($1);n->add_child($3);$$ = n;}
            |    value  ADD  value       {/*add(slap.id_of($1),slap.id_of($3));*/Node* n = new Node("add");n->add_child($1);n->add_child($3);$$ = n;}
            |    value  SUBTRACT  value  {Node* n = new Node("sub");n->add_child($1);n->add_child($3);$$ = n;}
            ;



%%

int main(int argc, char* argv[])
{
    yyparse();
    slap.print();
    //lit.print();
    //printf("\n");
    //printf("%d\n",bytes.size());
    //lit.print();
}

void yyerror(const char* msg)
{
    std::string str(msg);
    abort(str);
}
