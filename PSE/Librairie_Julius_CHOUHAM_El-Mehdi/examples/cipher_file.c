#include<julius.h>

int main(int argc, char * argv[])
{	
	char * buffer = malloc(MAXLEN*sizeof(char));
	char * texte_sortie;
	int cle;
	
	FILE * file;
	FILE * file_temp;
	
	
	//Si aucun chemin n'a été renseigné
	if(argc <= 2){
		printf("Merci d'inserer une cle de chiffrement et un chemin de fichier à chiffrer \n");
		exit(0);
		}
	
	cle = atoi(argv[1]);
	
	//Si le fichier renseigné ne peut p
	file = fopen(argv[2], "r"); //Importation d'un fichier de lecture 
	file_temp = fopen("file_temp", "a"); // Création d'un fichier temporaire
	
	//Génerer une erreur si le fichier n'existe pas
	if(file == NULL){
		printf("Problème rencontré à la lecture du fichier \n");
		exit(0);
		}
		
	while(fgets(buffer, MAXLEN, file) != NULL){
		texte_sortie = chiffrer(buffer, cle);
		fputs(texte_sortie, file_temp);
		free(texte_sortie);
	}
	free(buffer);
	
	//Suppression du fichier de base et renom du fichier temporaire
	remove(argv[2]);
	rename("file_temp", argv[2]);
	
	//Fermeture des fichiers
	fclose(file_temp);
	fclose(file);

	return 0;
}
