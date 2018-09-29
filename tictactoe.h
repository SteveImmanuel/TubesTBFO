#ifndef __tictactoe_h__
#define __tictactoe_h__

#include "boolean.h"
#include <string.h>

#define totalstate 269
#define totalcol 10
#define size 9

typedef struct{
	char strg[15];
}sentence;

typedef struct{
	sentence array[10];
	int n;
}arrayofstring;

typedef struct{
	sentence matrix[300][15]; 
}matrixofstring;

#define Elmt(M,i,j) ((M).matrix[(i)][(j)]).strg
#define Elarr(M,i) ((M).array[(i)]).strg
#define Neffarr(M) (M).n
#define str(s) (s).strg

void printstring(char string[15],int length);
//mengeprint string berupa array of char

void copystring(char buffer[200],matrixofstring* matrix_trans, int state);
//mengopy string dari buffer dan dipindahkan ke matrix_trans baris ke state

boolean eqstring(char ori[15],char input[15], int length);
//mengecek apakah string ori dan input sama

void printmatrix(matrixofstring matrix_trans);
//mengeprint trantition table dari file config.txt

void drawboard(char string[15]);
//menggambar board papan dari string;

void drawtemp(sentence state, int input);
//menggambar state sementara setelah player memilih tempat kosong

int findstate(char string[15],matrixofstring matrix_trans,int total);
//mencari string dalam trantition table

sentence transtate(sentence state,int input,matrixofstring matrix_trans);
//trantition function untuk mengubah state

void getinput(int* input,int min,int max);
//menerima input valid yaitu dari rentang min hingga max

void printliststate(arrayofstring liststate);
//mengeprint semua state di liststate

void addtoliststate(arrayofstring *liststate, char state[15]);
//menambahkan state ke list state

void eraseliststate(arrayofstring *liststate);
//mendelete semua elemen liststate

#endif