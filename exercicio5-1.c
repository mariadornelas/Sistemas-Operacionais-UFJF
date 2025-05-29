#include <stdio.h>#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            printf("Filho %d criado\n", getpid());
            return 0;
        }
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Pai finalizado\n");
    return 0;
}
