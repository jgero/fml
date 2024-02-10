#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

// prototypes for the lex and yacc generated functions
int yyparse();
int yylex();
int yyerror(const char *s);

// include the parser first
#include "parser/parser.tab.c"
// include the scanner second
#include "scanner/lex.yy.c"

int main(int argc, char* arcv[]) {
  if (argc != 2) {
    // there have to be exactly 2 arguments
	printf("2 args are required\n");
    return 1;
  }

  // the first argument is the name of the executeable, so number 1 is the name of the file
  string filename = arcv[1];
  // build the name of the input file
  string inp = filename;
  inp.append(".fml");
  char input_file[inp.size() + 1];
  strcpy(input_file, inp.c_str());

  // build the name of the output file
  string out = filename;
  out.append(".out");
  char output_file[out.size() + 1];
  strcpy(output_file, out.c_str());

  // set the in and output files of the lexer to the right files
  extern FILE *yyin, *yyout;
  yyin = fopen(input_file, "r");
  if (yyin == NULL) {
    // if the input file does not exist return an error
	printf("input file %s does not exist\n", input_file);
    return 1;
  }
  yyout = fopen(output_file, "w");
  if (yyparse() != 0) {
	printf("error while parsing\n");
    // not zero is returned when an error was found while parsing
    // the parser could return more than just one, but the prject requirements are, that the compiler returns 1 if something went wrong
    fclose(yyin);
    fclose(yyout);
    return 1;
  }
  fclose(yyin);
  fclose(yyout);
  return 0;
}

int yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

int yywrap() {
    printf("ending now");
    return 1;
}
