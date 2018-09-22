#include <stdio.h>
#include "tictactoe.h"

int main()
{
	FILE *config;
	matrixofstring matrix_trans,finalstate;
	char buffer[200];
	sentence state,nstate;//state untuk state sekarang, nstate untuk state berikutnya
	int k,check,input,rotation=0,istate;
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
		fgets (buffer, 1000, config);//copy trantition table ke matrix_trans
		check=strcmp(buffer,"//START STATES\n");
		if ((check)&&strcmp(buffer,"//FINAL STATES\n")) {//pilah bagian trantition table dan yang bukan
			copystring(buffer,&finalstate,k);
			k++;
		}
	}while(check);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("1. You play first.\n2. Computer plays first.\n");scanf("%d",&input);
	if (input==1){//player pertama, pergi ke state 13
		strcpy(str(state),Elmt(matrix_trans,13,0));//load state dan nstate
	}else{//cpu pertama, pergi ke state 1
		strcpy(str(state),Elmt(matrix_trans,1,0));//load state dan nstate
		drawboard(str(state),rotation);//jika cpu pertama, harus ditentukan ke mana player memilih agar tahu rotasinya
		scanf("%d",&input);
		if (input==3||input==6) rotation=90;
		else if (input==4||input==7) rotation=270;
		else if (input==8||input==9) rotation=180;
		input=rotateinput(input,rotation);
		printf("rotated:%d\n",input);
		state=transtate(state,input,matrix_trans);
	}
	
	drawboard(str(state),rotation);
	
	do{
		scanf("%d",&input);
		input=rotateinput(input,rotation);
		//printf("rotated:%d\n",input);
		nstate=transtate(state,input,matrix_trans);
		istate=findstate(str(nstate),finalstate,66);
		printf("%d\n",istate);
		if (eqstring(str(nstate),str(state),size)){
			printf("You cannot pick filled place\n");
		}else if(istate!=-1){
			state=transtate(state,input,matrix_trans);
			if (str(state)[size]=='w'){
				printf("you lose\n");
			}else if (str(state)[size]=='d'){
				printf("round draw\n");
			}else{
				printf("ini error\n");
			}
		}else{
			state=transtate(state,input,matrix_trans);
		}
		drawboard(str(state),rotation);
	}while(istate==-1);
	



	


	fclose(config);
		return 0;
}