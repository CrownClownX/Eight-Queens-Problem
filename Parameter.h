#ifndef PARAMETER
#define PARAMETER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//stałe reprezentujące parametry wyołania programu
#define _H "-h"
#define _S "-s"
#define _O "-o"

//Pobiera parametry i wywołuje funkcję sprawdzające ich poprawność
void checkArg(char** arg, int quantity, int* size, char ** name);

//Przetwarza nazwę ścieżki z parametru wywołania programu do char*
char* createPath(char * arg);

//Określa czy parametr jest liczbą, jeśli nie zwróci 0
int ifDigit(char* arg);

void help();

#endif
