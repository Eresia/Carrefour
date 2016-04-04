#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

int semalloc(key_t key, int vallInit);
int mutalloc(key_t key);

void P(int semid);
void V(int semid);

void *shmalloc(key_t key, int size);

int shmfree(key_t key, void *shmaddr);

int semfree(int semid);
