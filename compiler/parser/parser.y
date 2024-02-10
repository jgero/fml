%{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
%}

%token T_SQB_OPEN T_SQB_CLOSE
%token T_DOT
%token T_VALUE
%token T_NEWLINE
%token T_ERROR

%%

exp: start end T_NEWLINE;
start: T_SQB_OPEN { printf("test"); };
end: T_SQB_CLOSE;

%%
