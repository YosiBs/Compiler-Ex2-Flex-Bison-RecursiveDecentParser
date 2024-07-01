%{
#include <stdlib.h>
#include <string.h>
#include "olympics.h"
// yylex returns 0 when EOF is encountered

union _lexVal yylval; // semantic value of current token

extern int atoi (const char *);
extern double atof (const char *);
%}

%option noyywrap
%option yylineno

/* exclusive start condition -- deals with C++ style comments */ 
%x COMMENT


%%


"Olympic Sports" {
    strcpy(yylval.title , yytext);
		return TITLE;
}
"<sport>" {
    strcpy(yylval.sport, yytext);
    return SPORT;
}
"<years>" {
    strcpy(yylval.years, yytext);
    return YEARS;
}
\"([A-Z][A-Za-z]*(" "[A-Za-z]*)*)\" {
    strcpy(yylval.name, yytext);
    return NAME;
}
(1((89[6-9])|(9[0-9]{2})))|(20(([0-1][0-9])|(2[0-4]))) {
    yylval.yearNum = atoi (yytext);
    return YEAR_NUM;
}
"," {
    strcpy(yylval.comma, yytext);
    return COMMA;
}
"-"|"to" {
    strcpy(yylval.hyphen, yytext);
    return HYPHEN;
}
"since" {
    strcpy(yylval.since, yytext);
    return SINCE;
}
" all" {
    strcpy(yylval.all, yytext);
    return ALL;
}
"//"     { BEGIN (COMMENT); }
[\n\t ]+  /* skip white space */

<COMMENT>.+ /* skip comment */
<COMMENT>\n {  /* end of comment --> resume normal processing */
                BEGIN (0); }

. {
    fprintf (stderr, "Line number : %d unrecognized token %c \n",yylineno,yytext[0]);
}
%%

/* useful for error messages */
char *token_name(enum token token)
{
    switch(token) {
        case TITLE:  return "TITLE";
        case SPORT: return "SPORT";
        case YEARS:     return "YEARS";
        case NAME:       return "NAME";
        case YEAR_NUM:     return "YEAR_NUM";
        case COMMA:     return "COMMA";
        case HYPHEN:	return "HYPHEN";
        case SINCE:	return "SINCE";
        case ALL:	return "ALL";
        case 0:         return "EOF";
        default:        return "unknown token";        
    }
}