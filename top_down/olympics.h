#ifndef MYLEX
#define MYLEX

#define MAX_GAME_TYPES 100 //assume that it will be under 

// yylex returns 0 when EOF is encountered
enum token {
    TITLE=300,
    SPORT,
    YEARS,
    NAME,
    YEAR_NUM,
    COMMA,
    HYPHEN,
    SINCE,
    ALL
};

char *token_name(enum token token);
void errorMsg(const char *s);

union _lexVal{
	char title[20];
    char sport[10];
	char years[8];
	char name[80];
    int yearNum;
    char comma[2];
    char hyphen[5];
    char since[10];
    char all[5];
};

extern union _lexVal yylval;

void errorMsg(const char *s);
#endif
