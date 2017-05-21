#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum Tablica{
    PUSTE, HETMAN
}tablica;

void engine();

int checkArg(char**, int, int**, char**);
int znajdz(int*, char* );

void pomoc();

tablica** stworzTab(int*);

void zapisz(tablica** tab, char* nazwa, int* rozmiar);
int checkDiagon(tablica** tab, int y);
int czyLiczba(char* arg);
