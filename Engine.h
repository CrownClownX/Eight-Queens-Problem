#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define H "-h"
#define S "-s"
#define O "-o"

typedef enum Chessboard{
    EMPTY, QUEEN
}chessboard;

void engine(char** arg, int quantity);

int checkArg(char** arg, int quantity, int* size, char ** name);
int findSolution(int size, char* name);

void help();

chessboard** createBoard(int size);

void save(chessboard** tab, char* name, int size);
int checkDiagon(chessboard** tab, int y);
int ifDigit(char* arg);
