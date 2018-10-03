#include <stdio.h>
#include "tictactoe.h"

int main()
{
	FILE *config;
	matrixofstring matrix_trans,finalstate;
	char buffer[200],temp[15]="----x----";
	sentence state;//state untuk state sekarang
	arrayofstring liststate;
	int k,check,input,outinput,rotation=0,istate,end,c_score=0,same;

	config =fopen("config.txt","r");//load file konfigurasi
	if (!config) {
		printf("Config file not found!\n");
		return 1;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	k=1;
	do{
		fgets (buffer, 1000, config);//copy trantition table ke matrix_trans
		check=strcmp(buffer,"//FINAL STATES\n");
		if ((check)&&strcmp(buffer,"//TRANTITION TABLES\n")) {//pilah bagian trantition table dan yang bukan
			copystring(buffer,&matrix_trans,k);
			k++;
		}
	}while(check);
	k=1;
	do{
		fgets (buffer, 1000, config);//copy final states ke finalstate
		check=strcmp(buffer,"//START STATES\n");
		if ((check)&&strcmp(buffer,"//FINAL STATES\n")) {//pilah bagian final states dan yang bukan
			copystring(buffer,&finalstate,k);
			k++;
		}
	}while(check);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	do{
		printf("\nTIC TAC TOE\n\n");
		printf("Skor Anda : %d\nSkor Komputer : %d\n\n",0,c_score);
		printf("Pilihan :\n1. Anda bermain pertama\n2. Anda bermain kedua\n3. Bantuan\n4. Keluar\n");
		getinput(&outinput,1,4);
			if(outinput==1||outinput==2){
				end=0;
				eraseliststate(&liststate);
				if (outinput==1){//player pertama, pergi ke state ke-42
					strcpy(str(state),Elmt(matrix_trans,42,0));//load state
					addtoliststate(&liststate,str(state));
					printf("Karena anda memilih pertama, maka anda otomatis memilih petak tengah.\n");
					drawboard(temp);
				}else{//cpu pertama, pergi ke state ke-1
					strcpy(str(state),Elmt(matrix_trans,1,0));//load state
					addtoliststate(&liststate,str(state));
				}
				printf("\nGiliran komputer.\n");
				drawboard(str(state));
				do{
					printf("Giliran anda.\n");
					getinput(&input,1,9);
					same=strcmp(str(state),str(transtate(state,input,matrix_trans)));
					state=transtate(state,input,matrix_trans);
					addtoliststate(&liststate,str(state));
					istate=findstate(str(state),finalstate,198);
					if(istate!=-1){
						drawtemp(state,input);
						if (str(state)[size]=='w'){
							end=1;
							c_score++;
						}else if (str(state)[size]=='d'){
							end=2;
						}else{
							printf("error end state not found\n");//untuk debugging
						}
					}else{
						if(same==0){
							printf("Anda tidak dapat memilih petak yang sudah terisi.\n");
						}
					}
					printf("\nGiliran komputer.\n");
					drawboard(str(state));
					if(end==1){
						printf("Anda kalah.\n");
					}else if(end==2){
						printf("Ronde seri.\n");
					}
				}while(istate==-1);
				printliststate(liststate);
			}else if(outinput==3){
				printf("Ini adalah permainan TIC TAC TOE standar.\nAnda harus mengisi tiga petak berurutan horizontal,\nvertikal, atau diagonal. Setiap petak bernomor antara 1 sampai 9.\n");
				printf("Namun, jika anda memilih untuk jalan duluan,\nAnda harus memilih petak tengah terlebih dahulu\n");
			}
	}while(outinput!=4);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fclose(config);
		return 0;
}