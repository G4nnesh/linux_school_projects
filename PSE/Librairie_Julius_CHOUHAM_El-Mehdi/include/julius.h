#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define MAXLEN 100



#ifndef CONST__LOADED
	#define CONST__LOADED
	#ifndef MOT 
		#define MOT -1
	#endif
	
	#ifndef CLE
		#define CLE -1
	#endif
	
	#define CHECK()	\
		if(*MOT == -1 || CLE == -1)	\
		{	\
			if(*MOT == -1)	\
			{	\
				printf("MERCI DE RENTER LE MOT A CODE \n");	\
			}	\
			if(CLE == -1)	\
			{	\
				printf("MERCI DE SAISIR LA CLE \n");	\
			}	\
			printf("here");	\
			exit(EXIT_SUCCESS);	\
		}else	
#endif






//Prototype des fonctions :
char * chiffrer(const char * message, int cle);
