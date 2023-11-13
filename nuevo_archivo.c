#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMBER_OF_THREADS 2
#define CANTIDAD_INICIAL_HAMBURGUESAS 20

int cantidad_restante_hamburguesas = CANTIDAD_INICIAL_HAMBURGUESAS;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *comer_hamburguesa(void *tid)
{
    while (1)
    {
        
        pthread_mutex_lock(&mutex);

        if (cantidad_restante_hamburguesas > 0)
        {
            printf("Hola! Soy el hilo (comensal) %ld, me voy a comer una hamburguesa! Quedan %d hamburguesas\n", (long)tid, cantidad_restante_hamburguesas);
            cantidad_restante_hamburguesas--; 
        }
        else
        {
            printf("SE TERMINARON LAS HAMBURGUESAS :( \n");
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

        
        pthread_mutex_unlock(&mutex);

        usleep(100000);

    
        printf("%ld\n", (long)tid);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i, ret;
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        printf("Hola!, soy el hilo principal. Estoy creando el hilo %d \n", i);
        status = pthread_create(&threads[i], NULL, comer_hamburguesa, (void *)i);
        if (status != 0)
        {
            printf("Algo salio mal, al crear el hilo recibi el codigo de error %d \n", status);
            exit(-1);
        }
    }

    for (i = 0; i < NUMBER_OF_THREADS; i++)
    {
        void *retval;
        ret = pthread_join(threads[i], &retval); 
    }
    pthread_exit(NULL);
}
