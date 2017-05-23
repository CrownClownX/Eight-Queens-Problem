#include "Engine.h"

void engine(char** arg, int quantity)
{
    int *size = NULL;
    char *name = NULL;

    if((checkArg(arg, quantity, &size, &name)) == 0)
    {
        puts("ZLY ARGUMENT\n");
        help();
        return;
    }

    if(*size < 8)
    {
        puts("ZA MALY ROZMIAR TABLICY\n");
        return;
    }

    if((findSolution(size, name)) == 0)
    {
        puts("BLAD TWORZENIA TABLICY\n");
        help();
        return;
    }

    free(size);
    free(name);
}

int checkArg(char** arg, int quantity, int** size, char ** name)
{
    char h[3] = "-h";
    char s[3] = "-s";
    char o[3] = "-o";
    int i = 0;
    if(quantity > 1)
    {
        for(i = 1; i < quantity; i++)
        {
            if((strcmp(arg[i], h)) == 0)
                help();
            else if((strcmp(arg[i], s)) == 0)
            {
                i++;
                if(ifDigit(arg[i]) == 1)
                {
                    *size = (int*)malloc(sizeof(int));
                    **size = atoi(arg[i]);
                }
                else
                    return 0;
            }
            else if((strcmp(arg[i], o)) == 0)
            {
                i++;
                *name = (char*)malloc(sizeof(char)*( strlen(arg[i])+ 1));
                strcpy(*name, arg[i]);
            }
            else
                return 0;
        }
    }
    return 1;
}

void help()
{
    printf("WITAJ W POMOCY PROGRAMU OBLICZAJ¥CEGO PROBLEM OŒMIU HETMANÓW\n");
    printf("POMOC WYWOLUJEMY ZA POMOCA PARAMETRU -h\n");
    printf("BY WYBRAC WIELKOSC TABLICY UZYWAMY PARAMETRU -s A PO NIM PODAJEMY WIELKOSC\n");
    printf("WIELKOSC TABLICY POWINNA BYC WIEKSZA NIZ 8, INACZEJ PROBLEM STAJE SIE NIEMOZLIWY DO ROZWIAZANIA\n");
    printf("BY NADAC NAZWE PLIKOWI TEKSTOWEMU W KTORYM ODPOWIEDZ ZOSTANIE ZAPISANA PODAJEMY PARAMETR -o A PO NIM NAZWE\n");
    printf("WYSTARCZY PODAC SAMA NAZWE PLIKU DO ZAPISU, PROGRAM AUTOMATYCZNIE DODA ROZSZEZENIE TXT\n");
    printf("PRZYKLAD Queens.exe -s 10 -o rozwiazania\n");
}

chessboard** createBoard(int* size)
{
    if(*size < 8)
        return NULL;

    int i, j;
    chessboard **tab = (chessboard**)malloc(sizeof(chessboard*)*(*size));
    for(i = 0; i < *size; i++)
        tab[i] = (chessboard*)malloc(sizeof(chessboard)*(*size));

    for(i = 0; i < *size; i++)
        for(j = 0; j <  *size; j++)
            tab[i][j] = EMPTY;

    return tab;
}

void save(chessboard** tab, char* name, int *size)
{
    FILE* txtFile;
    int x, y;
    char buffer[50];
    char extension[5] = ".txt";

    strcpy(buffer, name);
    strcat(buffer, extension);

    if((txtFile = fopen(buffer, "w+"))==NULL)
    {
        puts("BLAD ZAPISU\n");
        return;
    }

    for(y = 0; y < *size; y++)
    {
        for(x = 0; x <  *size; x++)
            if(tab[y][x] == EMPTY)
                fprintf(txtFile,"o ");
            else if(tab[y][x] == QUEEN)
                fprintf(txtFile, "h ");
        fprintf(txtFile,"\n");
    }

    fclose(txtFile);
    return;
}

int findSolution(int* size, char* name)
{
    chessboard** tab = NULL;

    int y = 0, x = 0, queens = 0;

    if(size == NULL)
        return 0;

    tab = createBoard(size);

    if(tab == NULL)
        return 0;

    while(y < *size && queens != 8)
    {
        tab[y][x] = QUEEN;
        queens++;
        y++;
        x += 2;

        if(x >= *size)
            x = checkDiagon(tab, y);
    }

    save(tab, name, size);

    for(y = 0; y < *size; y++)
        free(tab[y]);
    free(tab);

    return 1;
}

int checkDiagon(chessboard** tab, int y)
{
    int x = 1;

    while(y >= 0)
    {
        if(tab[y][x] == QUEEN)
            return 3;
        x++;
        y--;
    }

    return 1;
}

int ifDigit(char* arg)
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
