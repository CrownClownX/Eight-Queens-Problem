#include "Engine.h"

void engine(char** arg, int ile)
{
    int *rozmiar = NULL;
    char *nazwa = NULL;

    if((checkArg(arg, ile, &rozmiar, &nazwa)) == 0)
    {
        puts("ZLY ARGUMENT\n");
        pomoc();
        return;
    }

    if(*rozmiar < 8)
    {
        puts("ZA MALY ROZMIAR TABLICY\n");
        return;
    }

    if((znajdz(rozmiar, nazwa)) == 0)
    {
        puts("BLAD TWORZENIA TABLICY\n");
        pomoc();
        return;
    }

    free(rozmiar);
    free(arg);
}

int checkArg(char** arg, int ile, int** rozmiar, char ** nazwa)
{
    char h[3] = "-h";
    char s[3] = "-s";
    char o[3] = "-o";
    int i;
    if(ile > 1)
    {
        for(i = 1; i < ile; i++)
        {
            if((strcmp(arg[i], h)) == 0)
                pomoc();
            else if((strcmp(arg[i], s)) == 0)
            {
                i++;
                if(czyLiczba(arg[i]) == 1)
                {
                    *rozmiar = (int*)malloc(sizeof(int));
                    **rozmiar = atoi(arg[i]);
                }
                else
                    return 0;
            }
            else if((strcmp(arg[i], o)) == 0)
            {
                i++;
                *nazwa = (char*)malloc(sizeof(char)*( strlen(arg[i])+ 1));
                strcpy(*nazwa, arg[i]);
            }
            else
                return 0;
        }
    }
    return 1;
}

void pomoc()
{
    printf("WITAJ W POMOCY PROGRAMU OBLICZAJ¥CEGO PROBLEM OŒMIU HETMANÓW\n");
    printf("POMOC WYWOLUJEMY ZA POMOCA PARAMETRU -h\n");
    printf("BY WYBRAC WIELKOSC TABLICY UZYWAMY PARAMETRU -s A PO NIM PODAJEMY WIELKOSC\n");
    printf("WIELKOSC TABLICY POWINNA BYC WIEKSZA NIZ 8, INACZEJ PROBLEM STAJE SIE NIEMOZLIWY DO ROZWIAZANIA\n");
    printf("BY NADAC NAZWE PLIKOWI TEKSTOWEMU W KTORYM ODPOWIEDZ ZOSTANIE ZAPISANA PODAJEMY PARAMETR -o A PO NIM NAZWE\n");
    printf("WYSTARCZY PODAC SAMA NAZWE PLIKU DO ZAPISU, PROGRAM AUTOMATYCZNIE DODA ROZSZEZENIE TXT\n");
    printf("PRZYKLAD Queens.exe -s 10 -o rozwiazania\n");

}

tablica** stworzTab(int* rozmiar)
{
    if(*rozmiar < 8)
        return NULL;

    int i, j;
    tablica **tab = (tablica**)malloc(sizeof(tablica*)*(*rozmiar));
    for(i = 0; i < *rozmiar; i++)
        tab[i] = (tablica*)malloc(sizeof(tablica)*(*rozmiar));

    for(i = 0; i < *rozmiar; i++)
        for(j = 0; j <  *rozmiar; j++)
            tab[i][j] = PUSTE;

    return tab;
}

void zapisz(tablica** tab, char* nazwa, int *rozmiar)
{
    FILE* plik;
    int x, y;
    char bufor[50];
    char t[5] = ".txt";

    strcpy(bufor, nazwa);
    strcat(bufor, t);

    if((plik = fopen(bufor, "w+"))==NULL)
    {
        puts("BLAD ZAPISU\n");
        return;
    }

    for(y = 0; y < *rozmiar; y++)
    {
        for(x = 0; x <  *rozmiar; x++)
            if(tab[y][x] == PUSTE)
                fprintf(plik,"o ");
            else if(tab[y][x] == HETMAN)
                fprintf(plik, "h ");
        fprintf(plik,"\n");
    }

    fclose(plik);
    return;
}

int znajdz(int* rozmiar, char* nazwa)
{
    tablica** tab = NULL;

    int y = 0, x = 0, het = 0;

    if(rozmiar == NULL)
        return 0;

    tab = stworzTab(rozmiar);

    if(tab == NULL)
        return 0;

    while(y < *rozmiar && het != 8)
    {
        tab[y][x] = HETMAN;
        het++;
        y++;
        x += 2;

        if(x >= *rozmiar)
            x = checkDiagon(tab, y);
    }

    zapisz(tab, nazwa, rozmiar);

    for(y = 0; y < *rozmiar; y++)
        free(tab[y]);
    free(tab);

    return 1;
}

int checkDiagon(tablica** tab, int y)
{
    int x = 1;

    while(y >= 0)
    {
        if(tab[y][x] == HETMAN)
            return 3;
        x++;
        y--;
    }

    return 1;
}

int czyLiczba(char* arg)
{
    int i = strlen(arg)- 1;

    while(i >= 0)
    {
        if(isdigit(arg[i]) == 0)
            return 0;
        i--;
    }

    return 1;
}
