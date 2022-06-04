#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define N_COUNTER 4 // 버퍼 사이즈
#define MILLI 1000  // time scale

void mywrite(int n);
int myread();

clock_t start, end;
float timecheck;

pthread_mutex_t critical_section; // 뮤텍스 객체
sem_t semWrite;
sem_t semRead;
int queue[N_COUNTER]; // shared buffer, 공유버퍼 4칸짜리 큐에
int wptr = -1; // write pointer for queue[] // write 포인터
int rptr = -1; // read pointer for queue[]  // read 포인터까지!

// producer thread function
void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        mywrite(i); /**** write i into the shared memory ****/
        printf("producer : wrote %d\n", i);

        // sleep m miliseconds
        int m = rand() % 10;
        usleep(MILLI * m * 10); // m*10
    }
    return NULL;
}

// consumer thread function
void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        int n = myread(); /**** read a value from the shared memory ****/
        printf("\tconsumer : read %d\n", i);

        // sleep m miliseconds
        int m = rand() % 10;
        usleep(MILLI * m * 10); // m*10 
    }
    return NULL;
}

// write n into the shared memory
void mywrite(int n) {
    sem_wait(&semWrite);

    pthread_mutex_lock(&critical_section);
    wptr++;
    wptr %= 4;
    queue[wptr] = n;
    pthread_mutex_unlock(&critical_section);

    sem_post(&semRead);
}

// write a value from the shared memory
int myread() {
    int n = 0;
    sem_wait(&semRead);

    pthread_mutex_lock(&critical_section);
    rptr++;
    rptr %= 4;
    n = queue[rptr];
    pthread_mutex_unlock(&critical_section);

    sem_post(&semWrite);
    return n;
}

int main() {
    start = clock();

    pthread_t t[2]; // thread structure
    srand(time(NULL)); // 시간은 난수로 생성

    pthread_mutex_init(&critical_section, NULL); // init mutex

    // init semaphore
    sem_init(&semWrite, 0, N_COUNTER);
    sem_init(&semRead, 0, 0);

    // create the threads for the producer and consumer
    pthread_create(&t[0], NULL, producer, NULL);
    pthread_create(&t[1], NULL, consumer, NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(t[i], NULL); // wait for the threads

      //destroy the semaphores
    sem_destroy(&semWrite);
    sem_destroy(&semRead);

    pthread_mutex_destroy(&critical_section); // destroy mutex 

    end = clock();
    timecheck = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Time : %.3fsec\n", timecheck);

    return 0;
}

