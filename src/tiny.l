/* The first section of a flex file contains:
 *    1. A code section for includes and other arbitrary C code. Copied to the scanner verbatim
 *    2. Helper definitions for regexes
 *    3. Scanner options
 */

/* Code section */
%{
#include "parser.tab.h" // Token definitions from the parser
#include <string.h>
#include <stdlib.h>

extern int tokens;

// Stores the line number with each token sent to bison
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}

/* Scanner options, line number generation */
%option yylineno

/* Removes warnings about input/output functions */
%option noinput
%option nounput

/* The second section of a flex file contains the regular expressions, using helper definitions
 * where appropriate ({<helper name>}). Sections in flex are divided by %%.
 *
 * Each line contains the regex, followed by the scanner action. Actions are executed when
 * a token is matched. A missing action is treated as a NOP.
 *
 * When building a scanner+parser combo, the parser is responsible for fetching the next token
 * from the scanner, which returns scans and returns a single token at a time. As part of the
 * action, we thus return the next token. Tokens can either be (a) a character; or (b) a token
 * defined in bison (included in y.tab.h).
 */

/* Note the use of 3 keywords:
 *    - yytext: Matched text
 *    - yylineno: Convenience variable for the line number provided by %option yylineno
 *    - yylval: Scanners transform input text into tokens (internally stored as an int) and pass
 *              them to the parser. For some the tokens (identifiers, constants), the original
 *              text is required in later phases. bison provides a variable yylval for each token
 *              to store this extra data. The definition of the yylval struct is provided as
 *              part of the bison grammar file.
 */
%%
[ \t\r\n]+ //ignore whitespace, newline and CR


"var" 		{ if (tokens) printf("tVAR\n"); return tVAR; }	
"float"		{ if (tokens) printf("tFLOAT\n"); return tFLOAT; }
"int"		{ if (tokens) printf("tINT\n"); return tINT; }
"string"	{ if (tokens) printf("tSTRING\n"); return tSTRING; }
"while"		{ if (tokens) printf("tWHILE\n"); return tWHILE; }
"if"		{ if (tokens) printf("tIF\n"); return tIF; }
"else"		{ if (tokens) printf("tELSE\n"); return tELSE; }
"boolean"	{ if (tokens) printf("tBOOLEAN\n"); return tBOOLEAN; }
"read"		{ if (tokens) printf("tREAD\n"); return tREAD; }
"print"		{ if (tokens) printf("tPRINT\n"); return tPRINT; }

"+"     { if (tokens) printf("tPLUS\n"); return '+'; }
"-"     { if (tokens) printf("tMINUS\n"); return '-'; }
"*"     { if (tokens) printf("tMULTIPLY\n"); return '*'; }
"/"     { if (tokens) printf("tDIVIDE\n"); return '/'; }
"("     { if (tokens) printf("tLEFTP\n"); return '('; }
")"     { if (tokens) printf("tRIGHTP\n"); return ')'; }
"{"		{ if (tokens) printf("tLEFTB\n"); return '{'; }
"}"		{ if (tokens) printf("tRIGHTB\n"); return '}'; }
"="		{ if (tokens) printf("tASSIGNMENT\n"); return '='; }
"=="	{ if (tokens) printf("tEQUAL\n"); return tEQ; }	
"!="	{ if (tokens) printf("tNEQ\n"); return tNEQ; }	
"&&"	{ if (tokens) printf("tAND\n"); return tAND; }	
"||"	{ if (tokens) printf("tOR\n"); return tOR; }
"!"		{ if (tokens) printf("tBANG\n"); return '!'; }	
":"		{ if (tokens) printf("tCOLON\n"); return ':'; }
";"		{ if (tokens) printf("tSEMI\n"); return ';'; }

("FALSE"|"TRUE") {
	if (strcmp(yytext, "FALSE") == 0) 
		yylval.intval = 0;
	else
		yylval.intval = 1;
	if (tokens)
		printf("tBOOLVAL(%s)\n", yytext);
	return tBOOLVAL;
}	

"//".* 				{ /* Ignore comments */ }

\"([a-zA-Z0-9@ #%&~`!?/'=_<>;:,\+\$\^\*\.\|\-\{\}\(\)\[\]]|\\[abfnrtv\\\*])*\" {
	yylval.string = strdup(yytext);
	if (tokens)
		printf("tSTRINGVAL(%s)\n", yytext);
	return tSTRINGVAL;
}

(0|[1-9][0-9]*) {
	yylval.intval = atoi(yytext);
	if (tokens)
		printf("tINTVAL(%s)\n", yytext);
	return tINTVAL;
}

(0|[1-9]+)[.][0-9]+	{
	yylval.floatval = atof(yytext);
	if (tokens)
		printf("tFLOATVAL(%s)\n", yytext);
	return tFLOATVAL;
}	

[a-zA-Z_][a-zA-Z0-9_]* {
	yylval.string = strdup(yytext);
	if (tokens)
		printf("tIDENT(%s)\n", yytext);
	return tIDENTIFIER;
}

. 	{ fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%
