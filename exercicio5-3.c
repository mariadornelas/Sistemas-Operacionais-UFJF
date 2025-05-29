#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t empty, full;
int buffer[5], index = 0;

void* produtor(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&empty);
        buffer[index++] = i;
        printf("Produzido: %d\n", i);
        sem_post(&full);
        usleep(100000);
    }
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&full);
        int item = buffer[--index];
        printf("Consumido: %d\n", item);
        sem_post(&empty);
        usleep(150000);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    pthread_create(&prod, NULL, produtor, NULL);
    pthread_create(&cons, NULL, consumidor, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
