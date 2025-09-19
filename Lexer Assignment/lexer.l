%{
#include <stdio.h>

int line = 1;
int column = 1;
extern FILE *yyin;
%}

%%
[ \t]	{ column += yyleng; }
\n	{ line++; column = 1; }


float	{ printf("<KEYWORD, float> at line %d, Col %d\n", line, column); column +=yyleng; }
int	{ printf("<KEYWORD, int> at line %d, Col %d\n", line, column); column +=yyleng; }
return	{ printf("<KEYWORD, return> at line %d, Col %d\n", line, column); column +=yyleng; }
if	{ printf("<KEYWORD, if> at line %d, Col %d\n", line, column); column +=yyleng; }
else	{ printf("<KEYWORD, else> at line %d, Col %d\n", line, column); column +=yyleng; }
while	{ printf("<KEYWORD, while> at line %d, Col %d\n", line, column); column +=yyleng;  }
for	{ printf("<KEYWORD, for> at line %d, Col %d\n", line, column); column +=yyleng; }
char	{ printf("<KEYWORD, char> at line %d, Col %d\n", line, column); column +=yyleng; }
double	{ printf("<KEYWORD, double> at line %d, Col %d\n", line, column); column +=yyleng; }
void	{ printf("<KEYWORD, void> at line %d, Col %d\n", line, column); column +=yyleng; }

[a-zA-Z_][a-zA-Z0-9_]*	{ 
	printf("<IDENTIFIER, %s> at Line %d, Col %d\n", yytext, line, column); 
	column += yyleng;		
}
[0-9]+\.[0-9]+		{ 
	printf("<FLOAT, %s> at Line %d, Col %d\n", yytext, line, column);
        column += yyleng;
}
[0-9]+			{
	printf("<NUMBER, %s> at Line %d, Col %d\n", yytext, line, column);
        column += yyleng;
}
"==" {
	printf("<OPERATOR, %s> at Line %d, Col %d\n", yytext, line, column);
        column += yyleng;
}
"<="			{
	printf("<OPERATOR, %s> at Line %d, Col %d\n", yytext, line, column);
        column += yyleng;
}
"!="			{
	printf("<OPERATOR, %s> at Line %d, Col %d\n", yytext, line, column);
        column += yyleng;
}
">="			{
	printf("<OPERATOR, %s> at Line %d, Col %d\n", yytext, line, column);
        column += yyleng;
}
[=+\-*/<>]		{
	printf("<OPERATOR, %s> at Line %d, Col %d\n", yytext, line, column);
        column += yyleng;
}
[;(),{}]		{
	printf("<SEPARATOR, %s> at Line %d, Col %d\n", yytext, line, column);
        column += yyleng;
}
.			{
	printf("LEXICAL ERROR: %s at Line %d, Col %d\n", yytext, line, column);
        column += yyleng;
}
%%

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Usage: %s <source_files>\n", argv[0]);
		return 1;
	}
	
	yyin = fopen(argv[1], "r");
	if (!yyin) {
	perror("Cannot open file");
	return 1;
	}
	
	yylex();
	printf("No lexical errors found. Source code is correct.\n");
	return 0;
	}
