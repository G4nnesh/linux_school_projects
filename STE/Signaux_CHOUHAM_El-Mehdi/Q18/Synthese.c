#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Définition de la fonction check :
#define CHECK(sts, msg)	\
	if (-1 == (sts)) {	\
		perror(msg) ;  \
	exit(EXIT_FAILURE) ; 	\
	}

#define PASSWORD "ESSAI"
#define MAXLEN  8
#define DUREE_MAX   30
#define ESSAIS_MAX  3

int temps_restant = 0;

// Prototypes :
int proc_fils(int);
static void signalHandler(int);

//Code du main :
int main(int argc, char *argv[])
{
    int max_essais, max_duree, status;
    int nb_echecs = 0;
    struct sigaction action_nouv;
    pid_t procFils, w;

    if (argc > 2){
        max_duree = atoi(argv[1]);    
        max_essais = atoi(argv[2]);
    }else{
        max_duree = DUREE_MAX;
        max_essais = ESSAIS_MAX;
    }

    if(max_duree <= 0 || max_essais <= 0){
        max_duree = DUREE_MAX;
        max_essais = ESSAIS_MAX; 
    } 
    
    printf("Vous avez %d secondes pour entrer votre mot de passe \n", max_duree);

    action_nouv.sa_handler = signalHandler;
    CHECK(sigemptyset(&action_nouv.sa_mask),"sigemptyset()");
    action_nouv.sa_flags = 0;

    CHECK(sigaction(SIGINT, &action_nouv, NULL),"sigaction()");
    CHECK(sigaction(SIGALRM, &action_nouv, NULL),"sigaction()");
    CHECK(sigaction(SIGUSR2, &action_nouv, NULL),"sigaction()");

    procFils = fork();
    switch(procFils){
        case 0 :
            //Code tâche fils 
            printf("Vous avez %d essais pour entrer votre mot de passe, et une durée limité !\n", max_essais);
            nb_echecs = proc_fils(max_essais);            
            CHECK(alarm(1),"alarm()");
            while(pause() == -1);
            exit(0);
        default :
            //Suite père
            w = waitpid(procFils, &status, 0);
            if(WIFEXITED(status)){
                if(nb_echecs == 0){
                    printf("Mot de passe valide : connexion acceptée \n");
                }else{
                    printf("Échec des %d tentatives : connexion refusée \n", max_essais);
                } 
            }
            printf("Je suis le père du processus : n°%d\n", procFils);
            break; 
    }

    exit(0);
    return 0;
}

//Code du processus fils :
int proc_fils(int nb_essais)
{   
    int nb_echecs = 0;
    struct sigaction action_nouv;

    action_nouv.sa_handler = signalHandler;
    CHECK(sigemptyset(&action_nouv.sa_mask),"sigemptyset()");
    CHECK(sigaddset(&action_nouv.sa_mask , SIGUSR2), "sigaddset(SIGUSR2)");//masque de SIGUSR2
    action_nouv.sa_flags = 0;

    int i = 0;
    while(i< nb_essais+1){ 
        char mdp [MAXLEN + 1];
        char *p;
        printf("Essai n° %d ..... : ", i);

        fgets(mdp, sizeof(mdp), stdin);
        if ((p = strchr(mdp, '\n')) != NULL){
            *p = '\0';
        }else{
            while (getchar() != '\n');
        }
        if (strcmp(mdp, PASSWORD) == 0){
            return 0;
        }else{
            nb_echecs++;
        }
        i++;
        
    }
    return nb_echecs;
}

//Code du gestionnaire de signaux :
static void signalHandler(int numSig)
{
    switch(numSig){
        case SIGALRM:
            temps_restant--;
            if (temps_restant<=0){
                struct sigaction action_nouv;
                action_nouv.sa_handler = signalHandler;
                CHECK(sigemptyset(&action_nouv.sa_mask),"sigemptyset()");
                action_nouv.sa_flags = 0;
                CHECK(sigaction(SIGUSR2, &action_nouv , NULL), "sigaction()");
            }else{
                CHECK(alarm(1),"alarm()")
            }
            break;
        case SIGUSR2:               //définition de SIGUSR2
            {
            struct sigaction action_nouv;
            action_nouv.sa_handler = signalHandler;
            CHECK(sigemptyset(&action_nouv.sa_mask),"sigemptyset()");
            action_nouv.sa_flags = 0;
            CHECK(sigaction(SIGINT , &action_nouv , NULL), "sigaction()");
            printf("Délai expiré : connexion refusée !\n");
            }
            break;
        
        default :
            break;
    }
}