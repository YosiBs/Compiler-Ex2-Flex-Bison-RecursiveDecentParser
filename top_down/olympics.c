/* 
    This is an example of a recursive descent parser.
    
This  program reads a list of olympic sport activities and the years they took place from its input.
    It prints the following:
        (1) Sport Activities that apeared in at least 7 Olympic games.
        (2) The average number of Olympic games per sport.
        
For an example of an input, see file input_olympics.txt 

To prepare the program, issue the following commands from
    The command line:

    flex olympics.lex    (This will generate a file called lex.yy.c)
    
    compile the program using a C compiler
    for example: 
        gcc lex.yy.c olympics.c -o olympics

    (note that file olympics.h is part of the program (it's included in
        other files)

    The input file for the program should be supplied as a command line argument
    for example:
        ./olympics input_olympics.txt


    Here is a grammar describing the input
        (tokens are written using uppercase letters):

    (1) input -> TITLE list_of_sports
    (2) list_of_sports -> list_of_sports sport_info | epsilon
    (3) sport_info -> SPORT NAME YEARS list_of_years
    (4) list_of_years -> list_of_years ',' year_spec | year_spec
    (5) year_spec -> YEAR_NUM | ALL | YEAR_NUM HYPHEN YEAR_NUM | SINCE YEAR_NUM


    Note that this grammar is not LL(1) because of the left recursion
    in the production for list_of_sports and because of the productions
    for list_of_years. It is not hard to find an equivalent LL(1) grammar
    but this was not necessary. See the functions sportList().

*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "olympics.h"

//#define DEBUG  

extern enum token yylex (void);
// the recursive descent parser
int lookahead;


typedef struct {
    char name[80];
    int appearances;
}GameInfo;

// Recursive descent parser functions
void start();
void parse();
void match(enum token expectedToken);
void sportList(GameInfo gameInfoArray[], int* arrLogicSize);
void printAnswer(GameInfo gameInfoArray[], int arrLogicSize);
int calculateAppearances();
void createNewGameInfo(GameInfo* pGameInfo);







int main (int argc, char **argv)
{
    extern FILE *yyin;
    if (argc != 2) {
        fprintf (stderr, "Usage: %s <input-file-name>\n", argv[0]);
	    return 1;
    }
    yyin = fopen (argv [1], "r");
    if (yyin == NULL) {
        fprintf (stderr, "failed to open %s\n", argv[1]);
	    return 2;
    }

    parse();

    fclose (yyin);
    return 0;
}

void parse()
{
    lookahead = yylex();
    start();
    if (lookahead != 0) {  // 0 means EOF
	    char e[100];
		sprintf(e, "EOF expected, found token %s\n", token_name(lookahead));
        errorMsg(e);
		exit(1);
    }
}

void start()
{
    match(TITLE);

    GameInfo gameInfoArray[MAX_GAME_TYPES]; /*array to hold the names and appearances of each game*/
    int arrLogicSize = 0; 

    sportList(gameInfoArray, &arrLogicSize);
    printAnswer(gameInfoArray, arrLogicSize);

}

void match(enum token expectedToken)
{
    if (lookahead == expectedToken){
        lookahead = yylex();
#ifdef DEBUG
    printf("token seen: %s\n", token_name(expectedToken));
#endif
    }else {
        char e[100]; 
        sprintf(e, "error: expected token %s, found token %s", 
                token_name(expectedToken), token_name(lookahead));
        errorMsg(e);
        exit(1);
    }
}

void sportList(GameInfo gameInfoArray[], int* arrLogicSize)
{
    while (lookahead != 0) {  // 0 means EOF
        createNewGameInfo(&gameInfoArray[*arrLogicSize]);
        (*arrLogicSize)++;

    }


}

void createNewGameInfo(GameInfo* pGameInfo)
{
#ifdef DEBUG
    printf("~~~~~~~~~~~~~~~~~~~~~~~~> NEW olympic game:\n");
#endif
    match(SPORT);
    pGameInfo->name[0] = '\0';
    pGameInfo->appearances = 0;

    strcpy(pGameInfo->name, yylval.name);
    match(NAME);
    match(YEARS); 


    pGameInfo->appearances = calculateAppearances();
    
}

int calculateAppearances()
{
    int appearances = 0;
    int startYear = 0;
    int endYear = 0;
    int calc = -1;
    do
    {
        switch(lookahead) 
        {
            case YEAR_NUM:
                startYear = yylval.yearNum;
                match(YEAR_NUM);
                if(lookahead == COMMA || lookahead == SPORT || lookahead == 0){
                    appearances += 1;
                }
                break;

            case COMMA:
                match(COMMA);
                break;
            
            case HYPHEN:
                match(HYPHEN);
                endYear = yylval.yearNum;
                appearances += ((endYear - startYear) / 4) + 1;
                match(YEAR_NUM);
                break;
            
            case SINCE:
                match(SINCE);
                appearances += ((2020 - yylval.yearNum) / 4 ) + 1;
                match(YEAR_NUM);
                break;
            
            case ALL:
                appearances += ((2020 - 1896) / 4 ) + 1;
                match(ALL);
                break;

            default:
                char e[100]; 
                sprintf(e, "error: found token %s", token_name(lookahead));
                errorMsg(e);
                exit(1);
        }
    }while(lookahead != SPORT && lookahead != 0);
    

#ifdef DEBUG
    printf("~> appearances is: %d\n",appearances);
#endif
    return appearances;
}


void errorMsg(const char *s)
{
    extern int yylineno;
    fprintf (stderr, "line %d: %s\n", yylineno, s);
}

void printAnswer(GameInfo gameInfoArray[], int arrLogicSize){

    int appearanceSum = 0;
    double avgGamesPerSport = 0;  /* (appearanceSum/arrLogicSize)*/

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