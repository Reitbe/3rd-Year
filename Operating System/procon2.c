#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define N_COUNTER 4 // buffer size
#define MILLI 1000  // time scale

void mywrite(int n);
int myread();

clock_t start, end;
float timecheck;

sequencer seqWrite;
sequencer seqRead;

int queue[N_COUNTER]; // shared buffer, 
int wptr = -1; // write pointer for queue[] 
int rptr = -1; // read pointer for queue[] 
int input, output;


// producer thread function
void* producer(void* arg) { 
  for(int i=0; i<10; i++) {
    mywrite(i); /**** write i into the shared memory ****/
    printf("producer : wrote %d\n", i);

    // sleep m miliseconds
    int m = rand()%10; 
    usleep(MILLI*m*10); // m*10
  }
  return NULL;
}

// consumer thread function
void* consumer(void* arg) { 
  for(int i=0; i<10; i++) {
    int n = myread(); /**** read a value from the shared memory ****/ 
    printf("\tconsumer : read %d\n", i);

    // sleep m miliseconds
    int m = rand()%10; 
    usleep(MILLI*m*10); // m*10 
  }
  return NULL;
}

// write n into the shared memory
void mywrite(int n) { 
    int v = 0;

    v = ticket(seqWrite);
    await(input, v); // await until become it's turn
    await(output, v - N_COUNTER + 1); // (N_COUNTER-(v-output) > 1), if buffer is full, await

    wptr++;
    wptr %= 4;
    queue[wptr] = n;

    advance(input); // increase input counter and awake next ticketholder
}

// write a value from the shared memory
int myread() { 
    int n = 0;
    int u = 0;
    
    u = ticket(seqRead);
    await(output, u); // await until become it's turn
    await(input, u + 1); // (input - output < 1) if buffer is empty, await
    
    rptr++;
    rptr %= 4;
    n = queue[rptr];

    advance(output); // increase output counter and awake next ticketholder
  return n;
}

int main() {
    start = clock();

    pthread_t t[2]; // thread structure
    srand(time(NULL)); 


    // make sequence, eventcounter
    //---None---//

    // create the threads for the producer and consumer
    pthread_create(&t[0], NULL, producer, NULL);
    pthread_create(&t[1], NULL, consumer, NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(t[i], NULL); // wait for the threads

    end = clock();
    timecheck = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Time : %.3f", timecheck);

    return 0;
}

