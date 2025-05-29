#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t garfo[5];

void *filosofo(void *arg) {
    int id = *(int *)arg;
    int primeiro = id;
    int segundo = (id + 1) % 5;

    if (id == 4) {
        primeiro = (id + 1) % 5;
        segundo = id;
    }

    while (1) {
        printf("Filosofo %d está pensando...\n", id);
        sleep(1);

        sem_wait(&garfo[primeiro]);
        sem_wait(&garfo[segundo]);

        printf("Filosofo %d está comendo...\n", id);
        sleep(1);

        sem_post(&garfo[primeiro]);
        sem_post(&garfo[segundo]);
    }

    return NULL;
}

int main() {
    pthread_t threads[5];
    int ids[5];

    for (int i = 0; i < 5; i++) {
        sem_init(&garfo[i], 0, 1);
    }

    for (int i = 0; i < 5; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, filosofo, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
