#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PATH "/home/jongchank/syssw/16_inter-process_communication/key"

int main(int argc, char *argv[])
{
    key_t key;
    int shmid, i;
    char *ptr;

    key = ftok(PATH, 'z');
    if (key < 0) {
        perror(argv[0]);
        exit(1);
    }
    shmid = shmget(key, 4096, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror(argv[0]);
        exit(1);
    }

    printf("shmid = %d\n", shmid);

    ptr = shmat(shmid, NULL, 0);
    if (ptr == NULL) {
        perror(argv[0]);
        exit(1);
    }

    printf("Writing As\n");
    for (i = 0; i < 1024; i++) {
        ptr[i] = 'A'; 
    }
    sleep(10);
    printf("Writing Bs\n");
    for (i = 0; i < 1024; i++) {
        ptr[i] = 'B'; 
    }
    exit(1);
}
