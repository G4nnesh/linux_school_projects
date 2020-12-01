@El Mehdi CHOUHAM
09/11/2020


Cas d'étude : Librairie Julius.

(Afin de voire la structue des fichier, voire le fichier "Structure.txt")

Pour installer :
	" make install"
	- compile la librairie en version statique et dynamique
	- compile les programmes d'exemple en statique et dynamique (objet puis compilé si nécessaires)
	- crée un lien symbolique avec la librairie dynamique dans usr/lib
	- crée des liens symboliques avec les programmes d'exemples dans usr/local/bin
	

Pour désinstaller :
	" make uninstall "
	- supprime tous les liens symboliques crées usr/lib/libjulius.so
	- supprime tous les liens symboliques des programmes d'exemples crées dans /usr/local/lib
	- execute un "make clean" : suppression des fichiers objets, des fichiers executables et des fichier.sp crées
	

Liste des commandes :
	- Commande : cesar_statique : nécessite d'inserer des arguments dans les variables symboliques MOT et CLE du fichier "makefile"
	- Commande : cesar_dynamique : nécessite d'inserer des arguments dans les variables symboliques MOT et CLE du fichier "makefile"
	
	
	- Commande : cipher_statique <Cle de décalage>    : demande un texte à chiffrer et afficher la valeur chiffré grace à la librairie
	- Commande : cipher_dynamique <Cle de décalage>   : demande un texte à chiffrer et afficher la valeur chiffré grace à la librairie


	- Commande : cipher_file_statique : <Cle de décalage> <chemin du fichier cible> : chiffre le fichier cible avec la clé donné
	- Commande : cipher_file_dynamique : <Cle de décalage> <chemin du fichier cible> : chiffre le fichier cible avec la clé donné
 
 
!!!!!!!!!!!!!!!!!!!!Le déchiffrement se fait en entrant -(la clé de chiffrement)!!!!!!!!!!!!!!!!!!!!!!


