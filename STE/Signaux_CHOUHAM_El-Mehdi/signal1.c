#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <signal.h>

// Définition de la fonction check :
#define CHECK(sts, msg)	\
	if (-1 == (sts)) {	\
		perror(msg) ;  \
	exit(EXIT_FAILURE) ; 	\
	}

#define SECONDES_DEFAUT 10


int main (int argc , char *argv[])
{
	sigset_t masque_nouv;
	sigset_t masque_anc;

	int secondes = 0 ;

	if (argc > 1) {
		secondes = atoi(argv[1]) ;
	}else{
		secondes = SECONDES_DEFAUT ;
	}

	printf("Inhibition du Ctrl+C. Arrêt dans : %d \n",secondes) ;

	//Initialisation du masque des signaux à ajouter
	CHECK(sigemptyset(&masque_nouv), "sigemptyset()") ;

	//Ajout de SIGINT
	CHECK(sigaddset(&masque_nouv , SIGINT), "sigaddset(SIGINT)") ;

	//Ajout dans le masque et sauvegarde de l'ancien masque
	CHECK(sigprocmask(SIG_BLOCK , &masque_nouv , &masque_anc), "sigprocmask()") ;
	CHECK(alarm(secondes), "alarm()") ;
	CHECK(pause(), "pause()") ;

	exit(0) ;

	return 0;
}
