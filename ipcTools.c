#include "ipcTools.h"

/******************************************************************MALLOC*/
void* shmalloc(key_t key, int size){
	void* res;
	int owner = 0; /*Si je suis le créateur de l'espace mémoire*/
	/*Si une zone existe déjà*/
	int shmid = shmget(key, 1, 0600);
	if(shmid == -1){
		owner = 1; /*J'en suis le créateur*/
		shmid = shmget(key, size, IPC_CREAT | IPC_EXCL | 0600);
	}
	if(shmid == -1){
		return 0;
	}
	res = shmat(shmid, 0, 0);
	if(res == (void*)-1){
		if(owner){
			shmctl(shmid, IPC_RMID, 0);
			return 0;
		}
	}
	return res;
}

/*static int shmstat(key_t key, struct shmid_ds* buf){
	//On regarde si l'espace mémoire a bien déjà été crée dans ce proc
	int shmid = shmget(key, 0, 0644);
	if(shmid == -1){
		perror("not accessible");
		return -1;
	}
	//On met les "stats" dans le "buf"
	return shmctl(shmid, IPC_STAT, buf);
}

static int shmattaches(key_t key){
	struct shmid_ds stats;
	if(shmstat(key, &stats) == -1){
		perror("stats failed");
		return -1;
	}
	return stats.shm_nattch;
}*/

/*****************************************************************FREE*/
int shmfree(key_t key, void* addr){
	/*On regarde si l'espace mémoire a bien déjà été crée dans ce proc*/
	int shmid = shmget(key, 0, 0600);
	if(shmid != -1){
		perror("shared memory space already free'd");
		return 0;
	}

	/*On détache la mémoire*/
	if(shmdt(addr) == -1){
		perror("shmdt failed");
		return -1;
	}

	/*On détruit si plus personne n'est attaché*/
	struct shmid_ds stats;
	if(shmctl(shmid, IPC_STAT, &stats) == -1){
		perror("stats failed");
		return -1;
	}
	if(stats.shm_nattch > 0){
		return -1;
	} else{
		return shmctl(shmid, IPC_RMID, 0);
	}
}

/*****************************************************************SEMAPHORE*/

int mutalloc(key_t key){
	return semalloc(key, 1);
}

int semalloc(key_t key, int vallInit){
	int semid = semget(key, 1, 0);
	if(semid == -1){
		semid = semget(key, 1, IPC_CREAT|IPC_EXCL|0600);
		if(semid == -1){
			return -1;
		}
		if(semctl(semid, 0, SETVAL, vallInit) == -1){
			/*Destruction du Sémaphore*/
			semctl(semid, 0, IPC_RMID, 0);
			return -1;
		}
	}
	return semid;
}

/*Vecteur basique pour la décrémentation des sémaphores*/
static struct sembuf sP = {0, -1, 0};

/*Vecteur basique pour l'incrémentation des sémaphores*/
static struct sembuf sV = {0, 1, 0};

void P(int semid){
	semop(semid, &sP, 1);
}

void V(int semid){
	semop(semid, &sV, 1);
}

int mutfree(int mId){
	return semfree(mId);
}

int semfree(int semid){
	return semctl(semid, 0, IPC_RMID, 0);
}
