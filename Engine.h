#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum Chessboard{
    EMPTY, QUEEN
}chessboard;

void engine();

int checkArg(char**, int, int**, char**);
int findSolution(int*, char* );

void help();

chessboard** createBoard(int*);

void save(chessboard**, char*, int*);
int checkDiagon(chessboard**, int);
int ifDigit(char*);
