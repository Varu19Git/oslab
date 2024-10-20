#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<semaphore.h>

#define KEY 1011

int main(){
	sem_t *mutex;
	key_t key=KEY;
	int shmid,pid;
	
	shmid=shmget(key,sizeof(sem_t),IPC_CREAT | 0666);
	
	mutex=(sem_t*)shmat(shmid,NULL,0);
	sem_init(mutex,1,0);
	pid=fork();
	if(pid>0){
		sleep(5);
		printf("p:I am executing--hi\n");
		sem_post(mutex);
		sleep(5); 
		printf("p:I am terminating\n");
		exit(1);
	}
	else if(pid==0){
		printf("c:GOod morning\n");
		sem_wait(mutex);
		printf("c:i am too terrminating\n");
		exit(1);
	}
}

