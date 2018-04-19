#include "Engine.h"

void engine(int sizeOfChessboard, char* name)
{
    if(!name)
        puts("BRAK NAZWY PLIKU");
    else if((sizeOfChessboard > 1 && sizeOfChessboard < 4 )|| sizeOfChessboard == 0)
        puts("BRAK ROZWIAZANIA DLA TAKIEGO ROZMIARU TABLICY");
    else
    {
        if(!(findSolution(sizeOfChessboard, name)))
            puts("BLAD TWORZENIA TABLICY");
    }
}

int findSolution(int sizeOfChessboard, char* name)
{
    chessboard** tab = createBoard(sizeOfChessboard);
    int* yValue = yAxisSolution(sizeOfChessboard);
    int y = 0, returnValue = 1, i;

    if(!tab || !yValue)
        returnValue = 0;

    for(i = 0; i < sizeOfChessboard; i++)
        if(!tab[i])
            returnValue = 0;

    if(returnValue != 0)
    {
        for(i = 0; i < sizeOfChessboard; i++)
        {
            int j = yValue[i] - 1;
            tab[i][j] = QUEEN;
        }

        if(!save(tab, name, sizeOfChessboard))
            returnValue = 0;
    }

    for(y = 0; y < sizeOfChessboard; y++)
        free(tab[y]);

    free(tab);
    free(yValue);

    return returnValue;
}

chessboard** createBoard(int sizeOfChessboard)
{
    int i, j;
    chessboard **tab = (chessboard**)malloc(sizeof(chessboard*)*sizeOfChessboard);

    for(i = 0; i < sizeOfChessboard; i++)
        tab[i] = (chessboard*)malloc(sizeof(chessboard)*sizeOfChessboard);

    for(i = 0; i < sizeOfChessboard; i++)
    {
        for(j = 0; j < sizeOfChessboard; j++)
            tab[i][j] = EMPTY;
    }

    return tab;
}

int* yAxisSolution(int sizeOfChessboard)
{
    int * tab = malloc(sizeof(int)*sizeOfChessboard);

    if(!tab)
        return NULL;

    if(sizeOfChessboard == 1)
    {
        tab[0] = 1;
        return tab;
    }

    int i, k = 2;
    for(i = 0; i < sizeOfChessboard; i++)
    {
        if(k == sizeOfChessboard || (k+1) == sizeOfChessboard)
            k = 1;
        else if(i != 0)
            k += 2;

        tab[i] = k;
    }

    if((sizeOfChessboard%6) == 2)
        findTab2(tab, sizeOfChessboard);
    else if((sizeOfChessboard%6) == 3)
        findTab3(tab, sizeOfChessboard);

    return tab;
}

void findTab2(int* tab, int sizeOfChessboard)
{
    int i;
    for(i = 0; tab[i] != 5; i++)
    {
        if(tab[i] == 1)
        {
            tab[i] = 3;
            tab[++i] = 1;
        }
    }

    for(;i < sizeOfChessboard; i++)
    {
        if(i != (sizeOfChessboard - 1))
            tab[i] = tab[i +1];
        else
            tab[i] = 5;
    }
}

void findTab3(int* tab, int sizeOfChessboard)
{
    int i;
    for(i = 0; tab[i] != sizeOfChessboard - 1; i++)
        tab[i] = tab[i + 1];

    tab[i] = 2;

    for(i += 1; i < sizeOfChessboard - 2; ++i)
        tab[i] = tab[i + 2];

    tab[i] = 1;
    tab[i + 1] = 3;
}

int save(chessboard** tab, char* name, int size)
{
    FILE* txtFile;
    int x, y;
    char buffer[50];
    char extension[5] = ".txt\0";

    strcpy(buffer, name);
    strcat(buffer, extension);

    txtFile = fopen(buffer, "w+");
    if(!txtFile)
        return 0;

    for(y = 0; y < size; y++)
    {
        for(x = 0; x <  size; x++)
            if(tab[y][x] == EMPTY)
                fprintf(txtFile,"o ");
            else if(tab[y][x] == QUEEN)
                fprintf(txtFile, "h ");
        fprintf(txtFile,"\n");
    }

    fclose(txtFile);
    return 1;
}
