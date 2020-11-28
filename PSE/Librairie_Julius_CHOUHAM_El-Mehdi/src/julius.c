#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAXLEN 100


//Chiffrement d'un seul charactère
char	chiffre_charac(char charac, int cle)
{	
	if (islower(charac)) {
		charac = 'a' + (((charac - 'a' + cle) % 26) + 26) % 26 ;
		return toupper(charac);			//Changement de casse
	} else if (isupper(charac)) {
        	charac = 'A' + (((charac - 'A' + cle) % 26) + 26) % 26 ;
        	return tolower(charac);			//Changement de casse
	} else{
        	return charac ;
    	}
}	

//Chiffrement d'un mot
char * chiffrer(const char * message, int cle)
{	
	char * mot = (char*) malloc(MAXLEN);
	int i;
	strcpy(mot, message);
	
	for(i=0; mot[i] != '\0'; ++i){
		mot[i] = chiffre_charac(mot[i], cle);
	}
	
	return  mot;
}
