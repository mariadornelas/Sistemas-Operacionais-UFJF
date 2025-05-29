#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void* threadFunc(void* arg) {
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, threadFunc, NULL) != 0) {
            perror("Erro ao criar thread");
            exit(1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Todas as threads finalizaram\n");
    return 0;
}
