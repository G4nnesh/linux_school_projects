#include<julius.h>

int main(int argc, char * argv[])
{	
	char buffer[MAXLEN];
	char * texte_sortie;
	int cle;
	
	if(argc>1){
		cle = atoi(argv[1]);
		printf("Saisissez le texte à coder : \n");
		while(fgets(buffer, MAXLEN, stdin) != NULL){
			texte_sortie = chiffrer(buffer, cle);
			printf("Le texte codé est : %s \n", texte_sortie);
			//Désallocation de la mémoire allouée dans chiffrer(buffer, cle)
			free(texte_sortie);
			break;
		}
	}else{
		printf("Merci de saisir une clé de décalage en paramètre ! \n");
	}	
	
	return 0;
}
