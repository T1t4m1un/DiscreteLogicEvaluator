%{
#include "ast.h"
#include "yacc.tab.hpp"

using namespace sem;
%}

%option noyywrap

%%

[ ]+   ; // skip whitespace
[!~]   { return NOT; }
"&"    { return AND; }
"|"    { return OR; }
"("    { return LPAREN; }
")"    { return RPAREN; }
[a-zA-Z_][a-zA-Z_0-9]*  {
    yylval = new Node(Node::NodeType::VARIABLE, yytext);
    return VARIABLE;
}
. { return yytext[0]; }

%%
