#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "pretty.h"
#include "codegen.h"

void yyparse();
int yylex();

int tokens;

PROG *program;

char *replaceExtension(char* mini) {
	char* c = malloc(strlen(mini)*8+10*sizeof(char));
	int i = 0;
	for (i = 0; i < strlen(mini); i++) {
		if (mini[i] == '.')
			break;
		c[i] = mini[i];
	}
	c[i+1] = 'c';
	c[i+2] = '\0';
	return c;
}

int main(int argc, char* argv[])
{
	if (strcmp(argv[1], "tokens") == 0) 
	{
	  tokens = 1;
	  while (yylex()) {}
	}
	else if (strcmp(argv[1], "scan") == 0)
	{
    while (yylex()) {}
	  printf("OK\n");
	}
	else if (strcmp(argv[1], "parse") == 0)
	{
	  yyparse();
	  printf("OK\n");
	}
	else if (strcmp(argv[1], "pretty") == 0) {
		yyparse();
		prettyPROG(program);
	}
	else if (strcmp(argv[1], "symbol") == 0) {
		yyparse();
		if (program == NULL) {
			printf("An unexpected error occured\n");
			return 1;
		}
		if (buildTable(program->val.prog.decls) != -1)
			printTable();
		else {
			return 1;
		}
	}
	else {
		yyparse();
		if (program == NULL) {
			printf("An unexpected error occured\n");
			return 1;
		}

		if (buildTable(program->val.prog.decls) == -1) { //if there's any error here, type checker will catch it anyway
			return 1;
		}

		if (typeCheckPROG(program) != -1)
			printf("OK\n");
		else 
			return 1;

		if (strcmp(argv[1], "codegen") == 0) {
			codegenPROG(program, replaceExtension(argv[2]));
		}
	}
	return 0;
}
