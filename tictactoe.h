#ifndef __tictactoe_h__
#define __tictactoe_h__

#include "boolean.h"
#include <string.h>

#define totalstate 108
#define totalcol 10
#define size 9

typedef struct{
	char strg[15];
}sentence;

typedef struct{
	sentence matrix[110][15]; 
}matrixofstring;

#define Elmt(M,i,j) ((M).matrix[(i)][(j)]).strg
#define str(s) (s).strg

void printstring(char string[15],int length);
//mengeprint string berupa array of char

void copystring(char buffer[200],matrixofstring* matrix_trans, int state);
//mengopy string dari buffer dan dipindahkan ke matrix_trans baris ke state

boolean eqstring(char ori[15],char input[15], int length);
//mengecek apakah string ori dan input sama

void printmatrix(matrixofstring matrix_trans);
//mengeprint trantition table dari file config.txt

int rotateinput(int input,int rotation);
//rotasi input agar sesuai dengan state yang ada

void drawboard(char string[15],int rotation);
//menggambar board papan dari string;

void drawtemp(sentence state, int input, int rotation);
//menggambar state sementara setelah player memilih tempat kosong

int findstate(char string[15],matrixofstring matrix_trans,int total);
//mencari string dalam trantition table

sentence transtate(sentence state,int input,matrixofstring matrix_trans);
//trantition function untuk mengubah state

#endif