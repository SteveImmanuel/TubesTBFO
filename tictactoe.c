#include <stdio.h>
#include "tictactoe.h"

void printstring(char string[15],int length)
//mengeprint string berupa array of char
{
	int i=0;
	for(i;i<length;i++){
		printf("%c",string[i]);
	}
}
void copystring(char buffer[200],matrixofstring* matrix_trans, int state)
//mengopy string dari buffer dan dipindahkan ke matrix_trans baris ke state
{
	int i,j=0,k=0;
	for(i=0;i<strlen(buffer);i++){
		if((buffer[i]!='	')&&(buffer[i]!='\n')){
			Elmt(*matrix_trans,state,k)[j]=buffer[i];
			j++;
		}else if(buffer[i]=='	'){
			j=0;
			k++;
		}else{
			break;
		}
	}
}

boolean eqstring(char ori[15],char input[15], int length)
//mengecek apakah string ori dan input sama
{
	int i=0;
	boolean eq=true;
	while((i<length) && eq){
		if(ori[i]!=input[i]){
			eq=false;
		}else{
			i++;
		}
	}
	return eq;
}



void printmatrix(matrixofstring matrix_trans)
//mengeprint trantition table dari file config.txt
{
	int i,j;
	for(i=1;i<=totalstate;i++){
		printf("%d ",i);
		for(j=0;j<totalcol-1;j++){
			
			printstring(Elmt(matrix_trans,i,j),size+1);
			printf(" ");
		}
		printstring(Elmt(matrix_trans,i,j),size+1);
		printf("\n");	
	}
}


void drawboard(char string[15])
//menggambar board papan dari string;
{
	int i,j;
	for(i=1;i<=6;i++){
		for(j=1;j<=11;j++){
			if(j==4||j==8){
				printf("|");
			}else if(i==1||i==3||i==5){
				if(j==2||j==6||j==10){
					printf("%c",string[(((j+2)/4)+((i-1)/2)*3)-1]);
				}else{
					printf(" ");
				}
			}else if(i==2||i==4){
				printf("_");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

int findstate(char string[15],matrixofstring matrix_trans,int total)
//mencari string dalam trantition table
{
	int i=1;
	boolean found=false;
	while((i<=total)&&!found){
		if (eqstring(string,Elmt(matrix_trans,i,0),size)){
			found=true;
		}else{
			i++;
		}
	}
	if ((!found)&&i>total){
		return -1;
	}else{
		return i;
	}
}

sentence transtate(sentence state,int input,matrixofstring matrix_trans)
//trantition function untuk mengubah state
{
	sentence temp;
	int i=findstate(str(state),matrix_trans,totalstate);
	strcpy(str(temp),Elmt(matrix_trans,i,input));
	return temp;
}

void drawtemp(sentence state, int input)
//menggambar state sementara setelah player memilih tempat kosong
{
	char temp[15];
	strcpy(temp,str(state));
	temp[input-1]='X';
	drawboard(temp);
}

void getinput(int* input,int min,int max)
//menerima input valid yaitu dari rentang min hingga max
{
	boolean stop;
	do{
		printf("Input anda : ");
		scanf("%d",&(*input));
		if(*input<min||*input>max){
			printf("Input salah. Input anda seharusnya antara %d sampai %d\n",min,max);
			stop=true;
		}else{
			stop=false;
		}
	}while(stop);
}

void printliststate(arrayofstring liststate)
//mengeprint semua state di liststate
{
	int i;
	printf("\nState yang dilewati :\n");
	for(i=1;i<=Neffarr(liststate);i++){
		printf("%s\n",Elarr(liststate,i));
	}
}
void addtoliststate(arrayofstring *liststate, char state[15])
//menambahkan state ke list state
{
	Neffarr(*liststate)++;
	strcpy(Elarr(*liststate,Neffarr(*liststate)),state);
}

void eraseliststate(arrayofstring *liststate)
//mendelete semua elemen liststate
{
	Neffarr(*liststate)=0;
}