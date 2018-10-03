#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t ingr_mutex;
pthread_cond_t ingr_cond1;
pthread_cond_t ingr_cond2;
int papel = 0;
int cerillas = 0;
int tabaco = 0;
pthread_t tTabaco,tPapel,tCerillas,tAgente;

void *FumadorTC(){
    while(1){
        pthread_mutex_lock(&ingr_mutex);
        while(!(tabaco && cerillas))
            pthread_cond_wait(&ingr_cond1,&ingr_mutex);
        tabaco = 0;
        cerillas = 0;
        printf("Soy fumador papel hice un cigarillo\n");
        pthread_mutex_unlock(&ingr_mutex);
        pthread_cond_signal(&ingr_cond2);
        printf("Soy fumador papel y fume\n");
    }
    return 0;
}

void *FumadorPC(){
    while(1){
        pthread_mutex_lock(&ingr_mutex);
        while(!(papel && cerillas))
            pthread_cond_wait(&ingr_cond1,&ingr_mutex);
        papel = 0;
        cerillas = 0;
        printf("Soy fumador tabaco hice un cigarillo\n");
        pthread_mutex_unlock(&ingr_mutex);
        pthread_cond_signal(&ingr_cond2);
        printf("Soy fumador tabaco y fume\n");
    }
    return 0;
}

void *FumadorTP(){
    while(1){
        pthread_mutex_lock(&ingr_mutex);
        while(!(tabaco && papel))
            pthread_cond_wait(&ingr_cond1,&ingr_mutex);
        tabaco = 0;
        papel = 0;
        printf("Soy fumador cerillas hice un cigarillo\n");
        pthread_mutex_unlock(&ingr_mutex);
        pthread_cond_signal(&ingr_cond2);


        printf("Soy fumador cerillas y fume\n");
    }
    return 0;
}

void *Agente() {
     while (1) {
        sleep(2);
        int first = rand () % 3;
        switch (first){
          case 0:   papel = 1;
                    break;
          case 1:   cerillas = 1;
                    break;
          default:  tabaco = 1;
        }
        pthread_cond_broadcast(&ingr_cond1);

        int second = rand () % 3;
        if (second == first) second = (second + 1) % 3;
            switch (second){
                case 0:   papel = 1;
                    break;
                case 1:   cerillas= 1;
                    break;
                default:  tabaco = 1;
            }
        pthread_cond_broadcast(&ingr_cond1);
        pthread_mutex_unlock(&ingr_mutex);
     }
     return 0;
}

int main()
{
    pthread_cond_init(&ingr_cond1,NULL);
    pthread_cond_init(&ingr_cond2,NULL);
    pthread_mutex_init(&ingr_mutex,NULL);
    pthread_create(&tTabaco,NULL,FumadorPC,NULL);
    pthread_create(&tPapel ,NULL,FumadorTC,NULL);
    pthread_create(&tCerillas,NULL,FumadorTP,NULL);
    pthread_create(&tAgente,NULL,Agente,NULL);

    while(1){} //aca iria un join


    printf("Hello world!\n");
    return 0;
}
