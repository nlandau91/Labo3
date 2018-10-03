#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#define BUFFER_SIZE 20

sem_t mutex;
sem_t fillCount;
sem_t emptyCount;
pthread_t prod1;
pthread_t prod2;
pthread_t cons1;
pthread_t cons2;
pthread_t cons3;


void *producer(){
    while(1){
        //item = produce(item);
        sem_wait(&emptyCount);
            sem_wait(&mutex);
            printf("produciendo\n");
            sem_post(&mutex);
        sem_post(&emptyCount);
    }
}

void *consumer(){
    while(1){
        sem_wait(&fillCount);
            sem_wait(&mutex);
            printf("consumiento\n");
            sem_post(&mutex);
        sem_post(&emptyCount);
    }
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&fillCount,0,0);
    sem_init(&fillCount,0,BUFFER_SIZE);
    pthread_create(&prod1,NULL,producer,NULL);
    pthread_create(&prod2,NULL,producer,NULL);
    pthread_create(&cons1,NULL,consumer,NULL);
    pthread_create(&cons2,NULL,consumer,NULL);
    pthread_create(&cons3,NULL,consumer,NULL);

    //aca va un join

    printf("Hello world!\n");
    return 0;
}
