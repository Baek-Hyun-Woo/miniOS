#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define NUM_POINTS 10000000
#define NUM_THREADS 5

int syn_points_in_circle = 0;
pthread_mutex_t locks;

void *sync_gen_points(void *num) {
    int *count = (int*)num;
    double x,y;
    int i;

    for (i=0;i<*count; i++){
        x = (double)rand() /RAND_MAX;
        y = (double)rand() /RAND_MAX;

        if(x * x + y * y <= 1){
            pthread_mutex_lock(&locks);
            syn_points_in_circle++;
            pthread_mutex_unlock(&locks);
        }
    }

    pthread_exit(NULL);
}

int sync_cal_pi(){
    int ppt = NUM_POINTS / NUM_THREADS;
    pthread_t threads[NUM_THREADS];
    srand(time(NULL));

    if(pthread_mutex_init(&locks,NULL) != 0){
        printf("Fail to initialize mutex");
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++){
        pthread_create(&threads[i],NULL, sync_gen_points,&ppt);
    }

    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i],NULL);
    }
    double pi_estimate = 4.0 * syn_points_in_circle / NUM_POINTS;
    printf("pi(Estimated) : %1f\n",pi_estimate);

    pthread_mutex_destroy(&locks);
    return 0; 
}