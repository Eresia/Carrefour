#include "ipcTools.h"

static struct sembuf sbuf;

int semalloc(key_t key, int vallInit){
	int semid;
	semid = semget(key, 1, IPC_CREAT|IPC_EXCL|0600);
	if(semid != -1){
		if(semctl(semid, 0, SETVAL, vallInit) != -1){
			return semid;
		}
	}
	return semid;
}

int mutalloc(key_t key){
	int semid;
	semid = semget(key, 1, IPC_CREAT|IPC_EXCL|0600);
	if(semid != -1){
		if(semctl(semid, 0, SETVAL, 1) != -1){
			return semid;
		}
	}
	return semid;
}

void *shmalloc(key_t key, int size){
	int shmid = shmget(key, size, IPC_CREAT|IPC_EXCL|0600);
	if(shmid == -1){
		shmid = shmget(key, size, 0600);
	}
	if(shmid != -1){
		void *addr = shmat(shmid, 0, 0);
		if(addr == -1){
			shmctl(shmid, IPC_RMID, 0);
		}
		else{
			return addr;
		}
	}
	return 0;
}

int shmfree(key_t key, void *shmaddr){
	int shmid = shmget(key, 0, 0600);
	if(shmid != -1){
		shmdt(shmaddr);
		shmctl(shmid, IPC_RMID, 0);
		return 0;
	}
	return -1;
}

void P(int semid){
		sbuf.sem_op = -1;
		semop(semid, &sbuf, 1);
}

void V(int semid){
		sbuf.sem_op = +1;
		semop(semid, &sbuf, 1);
}

int semfree(int semid){
	return semctl(semid, 0, IPC_RMID, 0);
}
