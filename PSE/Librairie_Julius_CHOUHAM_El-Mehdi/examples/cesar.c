#include<julius.h>

int main()
{		
	CHECK();	//Vérifie si les arguments ont bien été definis dans une constantes symboliques dans le make file

	char * sortie = chiffrer(MOT, CLE);
	printf("Résultat : %s \n", sortie);
	free(sortie);
	
	return 0;
}
