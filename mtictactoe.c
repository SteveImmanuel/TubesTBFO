#include <stdio.h>
#include "tictactoe.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	FILE *config;
	matrixofstring matrix_trans,finalstate;
	char buffer[200],temp[15]="----x----";
	sentence state,nstate;//state untuk state sekarang, nstate untuk state berikutnya
	arrayofstring liststate;
	int k,check,input,outinput,rotation=0,istate,end,p_score=0,c_score=0;

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
		printf("Your Score : %d\nComputer's Score : %d\n\n",p_score,c_score);
		printf("Option :\n1. You play first\n2. Computer plays first\n3. Help\n4. Exit\n");
		getinput(&outinput,1,4);
			if(outinput==1||outinput==2){
				end=0;
				eraseliststate(&liststate);
				if (outinput==1){//player pertama, pergi ke state ke-13
					strcpy(str(state),Elmt(matrix_trans,13,0));//load state
					addtoliststate(&liststate,str(state));
					srand(time(0));
					rotation=(rand()%4)*90;
					printf("Since you choose to go first, you automatically choose the middle.\n");
					drawboard(temp,rotation);
				}else{//cpu pertama, pergi ke state ke-1
					strcpy(str(state),Elmt(matrix_trans,1,0));//load state
					addtoliststate(&liststate,str(state));
					do{
						printf("\nComputer's turn.\n");
						drawboard(str(state),rotation);//jika cpu pertama, harus ditentukan ke mana player memilih agar tahu rotasinya
						printf("Your turn.\n");//dan input user tidak boleh 5 karena kotak 5 sudah terisi
						getinput(&input,1,9);
						if (input==1) rotation=0;
						else if (input==3||input==6) rotation=90;
						else if (input==4||input==7) rotation=270;
						else if (input==8||input==9) rotation=180;
						else printf("You cannot pick filled place.\n");
					}while(input==5);				
					input=rotateinput(input,rotation);
					drawtemp(state, input,rotation);
					state=transtate(state,input,matrix_trans);
					addtoliststate(&liststate,str(state));
				}
				printf("\nComputer's turn.\n");
				drawboard(str(state),rotation);
				do{
					printf("Your turn.\n");
					getinput(&input,1,9);
					input=rotateinput(input,rotation);
					nstate=transtate(state,input,matrix_trans);
					istate=findstate(str(nstate),finalstate,66);
					if (eqstring(str(nstate),str(state),size)){
						printf("You cannot pick filled place.\n");
					}else if(istate!=-1){
						drawtemp(state, input,rotation);
						state=transtate(state,input,matrix_trans);
						addtoliststate(&liststate,str(state));
						if (str(state)[size]=='w'){
							end=1;
							c_score++;
						}else if (str(state)[size]=='d'){
							end=2;
						}else{
							printf("error end state not found\n");
						}
					}else{
						drawtemp(state, input,rotation);
						state=transtate(state,input,matrix_trans);
						addtoliststate(&liststate,str(state));
					}
					printf("\nComputer's turn.\n");
					drawboard(str(state),rotation);
					if(end==1){
						printf("You lose.\n");
					}else if(end==2){
						printf("Round draw.\n");
					}
				}while(istate==-1);
				printliststate(liststate);
			}else if(outinput==3){
				printf("This is standard TIC TAC TOE games. However, should you \nchoose to go first, you must choose the middle first.\n");
			}
	}while(outinput!=4);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fclose(config);
		return 0;
}