#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NBMAX_THREADS   4
#define DUREE_MAX       5

#define CHECK_T(status, msg)                        \
  if (0 != (status))   {                            \
    fprintf(stderr, "pthread erreur : %s\n", msg);  \
    exit (EXIT_FAILURE);                            \
  }
//Forçage de type
typedef void * (*pf_t)(void *);
//Prototypes
unsigned int factorielle(unsigned int);
void  monThread (long);
void  bye(void);

//Fonction main
int main(int argc, char *argv[])
{
    long * status;
    
    int nb_thread = argc - 1;
    long liste_n[nb_thread];
    pthread_t tid[nb_thread];
 
    for(int i=0; i<nb_thread; i++){
    	liste_n[i] = atol(argv[i+1]);
    }	
	
    atexit(bye);
    printf("Le processus %d va créer %d threads\n", getpid(), nb_thread);

    for (int i = 0; i < nb_thread; i++){
        CHECK_T(pthread_create (&tid[i], NULL, (pf_t)monThread,
                                (void *)liste_n[i]), "pthread_create()");
    }

    for (int i = 0; i < nb_thread; i++) {
        CHECK_T(pthread_join (tid[i], (void **) & status),"pthread_join()");
        printf("-> Factorielle de %ld est : %ld\n", liste_n[i], *status);
        free(status);
    }
    return EXIT_SUCCESS;
}
//Fonction du thread
void  monThread (long n)
{
    long * retVal = (long *) malloc (sizeof(long));    
    *retVal = (long) factorielle(n);
    pthread_exit((void *) retVal);
}
//Fonction factorielle
unsigned int factorielle(unsigned int n) 
{ 
    if (n == 0) 
        return 1; 
    return n * factorielle(n - 1); 
}
//Fonctiona appellée à dans lors de l'exit
void bye (void)
{
    printf("Fin du processus %d\n", getpid());
}
