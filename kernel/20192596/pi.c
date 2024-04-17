#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4 // thread 개수
#define TOTAL_POINTS 20000000 // point의 총 개수

int total_points = 0; // 원 안의 point 개수(전역변수)
pthread_mutex_t mutex;


void *monte_carlo(void *thread_id) {
    int id = *((int *)thread_id);
    int points_per_thread = TOTAL_POINTS / NUM_THREADS;
    int local_points = 0; //지역변수
    int i;

    // 스레드별 시드를 생성, 난수 생성기 초기화
    srand(time(NULL) + id);
    
    //무작위 point 생성
    for (i = 0; i < points_per_thread; i++) {
        double x = (double)rand() / RAND_MAX*2 -1; 
        double y = (double)rand() / RAND_MAX*2 -1;

        // 원 내부에 있는지 확인
        if (x * x + y * y <= 1.0) {
            local_points++; // 원 안에 있으면 점의 수 증가
        }
    }
    pthread_mutex_lock(&mutex);
    total_points += local_points; //thread별 계산된 점의 수를 전역변수에 더함
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int pi() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;

    pthread_mutex_init(&mutex,NULL);

    // thread 생성
    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, monte_carlo, (void *)&thread_ids[i]);
    }

    // thread 종료 대기
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // π 값 계산 및 출력
    double pi_estimate = 4.0 * total_points / TOTAL_POINTS;
    printf("pi: %f\n", pi_estimate);

     pthread_mutex_destroy(&mutex);

    return 0;
}

