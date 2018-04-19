#include "Parameter.h"

void checkArg(char** arg, int quantity, int* size, char ** name)
{
    if(quantity <= 1)
        return;

    int i;
    for(i = 1; i < quantity; i++)
    {
        if(!(strcmp(arg[i], _H)))
            help();
        else if(!(strcmp(arg[i], _S)))
        {
            i++;
            if(i == quantity || !ifDigit(arg[i]))
                return;

            *size = atoi(arg[i]);
        }
        else if(!(strcmp(arg[i], _O)))
        {
            i++;
            if(i >= quantity || !(strcmp(arg[i], _S)))
                return;

            *name = createPath(arg[i]);

            if(!*name)
                return;
        }
    }
}

char* createPath(char * arg)
{
    char * path;
    int len = strlen(arg);

    if(len < 1)
        return NULL;

    path = (char*)malloc(sizeof(char)*( len + 1));

    if(!path)
        return NULL;

    strncpy(path, arg, len);
    path[len] = '\0';

    return path;
}

int ifDigit(char* arg)
{
    int i = strlen(arg)- 1;

    while(i >= 0)
    {
        if(!isdigit(arg[i]))
            return 0;
        i--;
    }

    return 1;
}

void help()
{
    printf("WITAJ W POMOCY PROGRAMU ROZWIĄZUJĄCEGO PROBLEM OŚMIU HETMANOW\n");
    printf("POMOC WYWOŁUJEMY ZA POMOCA PARAMETRU -h\n");
    printf("BY WYBRAĆ ROZMIAR TABLICY UZYWAMY PARAMETRU -s A PO NIM PODAJEMY ROZMIAR\n");
    printf("ROZMIAR TABLICY NIE MOŻE WYNOŚIĆ 0, 2 ANI 3 , PONIEWAZ PROBLEM STAJE SIĘ NIEMOŻLIWY DO ROZWIĄZANIA\n");
    printf("BY NADAĆ NAZWE PLIKOWI TEKSTOWEMU W KTÓRYM ODPOWIEDŹ ZOSTANIE ZAPISANA PODAJEMY PARAMETR -o A PO NIM NAZWE\n");
    printf("WYSTARCZY PODAĆ SAMĄ NAZWE PLIKU DO ZAPISU, PROGRAM AUTOMATYCZNIE DODA ROZSZEZENIE .TXT\n");
    printf("PRZYKŁAD EQP.exe -s 10 -o rozwiazania\n");
}
