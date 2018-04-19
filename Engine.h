#ifndef ENGINE
#define ENGINE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//enum reprezentujący szachownice
typedef enum Chessboard{
    EMPTY, QUEEN
}chessboard;

//Wywołuje funkcje znajdującą rozwiązanie oraz wypisuje komunikaty o błędach
void engine(int sizeOfChessboard, char* name);

//Funkcja ustawia hetmanów na szachownicy i wywołuje funkcję save()
int findSolution(int sizeOfChessboard, char* name);

//Tworzy tablicę reprezentującą szachownice
chessboard** createBoard(int sizeOfChessboard);

//yAxisSolution znajduje położenie hetmanów w osi Y, w zależności od rozmiaru szachownicy
//funkcja może dodatkowo przekształcić tablicę zawierającą współrzędne Y za pomocą funkcji findTab2 i findTab3
int* yAxisSolution(int sizeOfChessboard);
void findTab2(int* tab, int sizeOfChessboard);
void findTab3(int* tab, int sizeOfChessboard);

//Zapisuje tablicę do pliku, w razie błędu zwórci 0
int save(chessboard** tab, char* name, int sizeOfChessboard);

#endif

