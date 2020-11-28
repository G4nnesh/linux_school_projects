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

static void signalHandler(int); //prototype de la fonction du gestionnaire

int main (int argc , char *argv[])
{
	int secondes = 0 ;

	if (argc > 1) {
		secondes = atoi(argv[1]) ;
	}else{
		secondes = SECONDES_DEFAUT ;
	}

	printf("Inhibition du Ctrl+C. Arrêt dans : %d \n",secondes) ;

	//Initisalisation de la sigaction comportant un traitement SIG_IGN
	struct sigaction action_nouv;
	struct sigaction action_anc;

	action_nouv.sa_handler = signalHandler; //appel du gestionnaire défini
	CHECK(sigemptyset(&action_nouv.sa_mask), "sigemptyset()");
	action_nouv.sa_flags = 0;

	//Installation du gestionnaire pour SIGINT
	CHECK(sigaction(SIGINT, &action_nouv, &action_anc), "sigaction()")

	CHECK(alarm(secondes), "alarm()") ;
	CHECK(pause(), "pause()");

	exit(0) ;

	return 0;
}

static void signalHandler(int numSig) //programme de la fonction du gestionnaire
{
	switch(numSig){
		case SIGINT :
			printf("\n Le contrôle-C est désactivé !\n");
			break;
		default :
			printf("\n Signal %d non traité \n", numSig);
			break;
	}
}
