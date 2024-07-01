%code {

/* 
    This  program reads a list of olympic sport activities and the years they took place from its input.
    It prints the following:
        (1) Sport Activities that apeared in at least 7 Olympic games.
        (2) The average number of Olympic games per sport. 


    For an example of an input, see file: input_olympics.txt 

    To prepare the program, issue the following commands from
    The command line:
    
    flex olympics.lex    (This will generate a file called lex.yy.c)
    bison -d olympics.y  (This will generate files olympics.tab.c & olympics.tab.h)
    
    compile  the files  that flex and bison generated with a C compiler
    for example: 
        gcc lex.yy.c olympics.tab.c -o olympics
        
    The input file for the program should be supplied as a command line argument
    for example:
        ./olympics  input_olympics.txt
*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#define MAX_GAME_TYPES 100
extern int atoi (const char *);

  /* yylex () and yyerror() need to be declared here */
extern int yylex (void);
void yyerror (const char *s);

int appearanceSum = 0;
double avgGamesPerSport = 0;  /* (appearanceSum/arrLogicSize)*/
int arrLogicSize = 0; /*array to hold the names and appearances of each game*/

typedef struct {
    char name [80];
    int appearances;
}GameInfo;

void printAnswer();
GameInfo createGameInfo(char* name, int appearances);

GameInfo gameInfoArray[MAX_GAME_TYPES];
}



/*-----------------------------------------------------------*/
/* note: no semicolon after the union */
%union {
    char title[20];
    char sport[10];
	char years[8];
	char name[80];
    int yearNum;
    char comma[2];
    char hyphen[5];
    char since[10];
    char all[5];

    int number;
}

%token <title> TITLE
%token <sport> SPORT
%token <years> YEARS
%token <name> NAME
%token <yearNum> YEAR_NUM
%token <comma> COMMA
%token <hyphen> HYPHEN
%token <since> SINCE
%token <all> ALL

%nterm <number> list_of_years
%nterm <number> year_spec



/*==========================================================*/
%%
input: TITLE list_of_sports { printAnswer(); }
    ;
list_of_sports: list_of_sports sport_info
    ;
list_of_sports: %empty
    ;

sport_info : SPORT NAME YEARS list_of_years
    {
        gameInfoArray[arrLogicSize] = createGameInfo($2,$4);
        arrLogicSize++;
    }
    ;

list_of_years: list_of_years COMMA year_spec
    {
        $$= $1 + $3;
    }
    ;

list_of_years: year_spec
    {
        $$ = $1;
    }
    ;

year_spec:  YEAR_NUM {$$ = 1;}
            | ALL {$$ = (((2020 - 1896) / 4) + 1);}
            | YEAR_NUM HYPHEN YEAR_NUM {$$ = ((($3 - $1) / 4) + 1);}
            | SINCE YEAR_NUM {$$ = (((2020 - $2) / 4) + 1);}
            ;

%%

int main (int argc, char **argv)
{
  extern FILE *yyin; /* defined by flex */
  if (argc != 2) {
     fprintf (stderr, "Usage: %s <input-file-name>\n", argv[0]);
	 return 1;
  }
  yyin = fopen (argv [1], "r");
  if (yyin == NULL) {
       fprintf (stderr, "failed to open %s\n", argv[1]);
	   return 2;
  }
#if 0

#ifdef YYDEBUG
   yydebug = 1;
#endif
#endif
  yyparse ();
  
  fclose (yyin);
  return 0;
}

/* called by yyparse() whenever a syntax error is detected */
void yyerror (const char *s)
{
  extern int yylineno; // defined by flex
  fprintf (stderr, "syntax Error, line %d:%s\n", yylineno,s);
}

GameInfo createGameInfo(char* name, int appearances){
    GameInfo gameInfo;
    strcpy(gameInfo.name, name);
    gameInfo.appearances = appearances;
    return gameInfo;
}

void printAnswer(){
    printf("sports which appeared in at least 7 olympic games:\n");
    for(int i = 0 ; i < arrLogicSize ; i++)
    {
        if(gameInfoArray[i].appearances >= 7){
            printf("%s\n",gameInfoArray[i].name);
        }
        appearanceSum += gameInfoArray[i].appearances;
        if(arrLogicSize != 0){
            avgGamesPerSport = (double)appearanceSum / arrLogicSize;
        }
    }
    printf("average number of games per sport: %.2f\n", avgGamesPerSport);
}

