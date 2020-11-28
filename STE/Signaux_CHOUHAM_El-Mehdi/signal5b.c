#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

// Définition de la fonction check :
#define CHECK(sts, msg)	\
	if (-1 == (sts)) {	\
		perror(msg) ;  \
	exit(EXIT_FAILURE) ; 	\
	}

#define SECONDES_DEFAUT 10

static void signalHandler(int); //prototype de la fonction du gestionnaire

int secondes = 0;//la variable contenant le temps restant devient globale

int main (int argc , char *argv[])
{
	int status;

	if (argc > 1) {
		secondes = atoi(argv[1]) ;
	}else{
		secondes = SECONDES_DEFAUT ;
	}

	printf("Le Ctrl-C est désactivé pendant : %d \n",secondes);

	//Initisalisation de la sigaction 
	struct sigaction action_nouv;
	struct sigaction action_anc;

	action_nouv.sa_handler = signalHandler; //appel du gestionnaire défini
	CHECK(sigemptyset(&action_nouv.sa_mask), "sigemptyset()");
	action_nouv.sa_flags = 0;

	//Installation du gestionnaire pour SIGINT
	CHECK(sigaction(SIGINT, &action_nouv, &action_anc), "sigaction()")
	//Installation du gestionnaire pour SIGALRM
	CHECK(sigaction(SIGALRM, &action_nouv, &action_anc ), "sigaction")

	pid_t pidFils;

	pidFils = fork();
	switch (pidFils){
		case -1 :
			perror("Échec de la création d'un processus fils");
			exit (pidFils);
		case 0 :
			CHECK(alarm (1) , " alarm ()");
			while (pause() == -1);
			CHECK(wait(&status), "wait()");
			exit(0);
		default :
			printf("Je suis le père du processus ...... n°%d\n", pidFils ) ;
			break ;

	}
	exit(0) ;
	return 0;
}

static void signalHandler(int numSig) //programme de la fonction du gestionnaire
{
	switch(numSig){
		case SIGINT :
			printf("Le Ctrl-c est désactivé pendant : %d \n",secondes);
			break;
		case SIGALRM :
			secondes--;
			if (secondes > 0){
				CHECK(alarm(1), "alarm()");
			}else{
				struct sigaction action_nouv;
				struct sigaction action_anc;
				//initialisation de la stucture sigaction
				action_nouv.sa_handler = SIG_DFL;
				CHECK(sigemptyset(&action_nouv.sa_mask),"sigemptyset()");
				action_nouv.sa_flags = 0;
				//Installation du gestionnaire
				CHECK(sigaction(SIGINT, &action_nouv, &action_anc) ,"sigaction()");
				printf("Le traitement normal du Ctr-C est réactivé \n");
			}
			break;
		default :
			printf("\n Signal %d non traité \n", numSig);
			break;
	}
}
