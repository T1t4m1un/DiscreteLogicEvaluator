%{
#include <iostream>

#include "ast.h"

int yylex();
void yyerror(const char*);

using namespace sem;
%}

%token NOT AND OR LPAREN RPAREN VARIABLE

%%

start:
    expr                        { parse_tree = $1; YYACCEPT; }
    ;

expr:
    term                        { $$ = $1; }
    | expr OR term              { $$ = new Node(Node::NodeType::OR, "", $1, $3); }
    ;

term:
    factor                      { $$ = $1; }
    | term AND factor           { $$ = new Node(Node::NodeType::AND, "", $1, $3); }
    ;

factor:
    VARIABLE                    { $$ = $1; }
    | NOT factor                { $$ = new Node(Node::NodeType::NOT, "", $2); }
    | LPAREN expr RPAREN        { $$ = $2; }
    ;

%%

void yyerror(const char* s) {
    std::cerr << "Error: " << s << std::endl;
}
