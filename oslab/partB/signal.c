#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<signal.h>

void sigfn1(){
	printf("I am parent,Child u can proceed\n");
}
void sigfn2(){
	printf("I am child,parent u can proceed\n");
}
int main(){
	signal(SIGUSR1,sigfn1);
	signal(SIGUSR2,sigfn2);
	key_t key=ftok("worstfit.c",165);
	int shmid=shmget(key,10*sizeof(int),IPC_CREAT|0666);
	if(shmid>0){
		printf("Shared memory id=%d",shmid);
	}
	int *ptr=(int*)shmat(shmid,0,0);
	int pid=fork();
	if(pid==0){
		printf("I am child i am going to wait for parent to send data\n");
		pause();
		printf("c:I am got signal from parent\n");
		for(int i=0;i<10;i++){
			for(int j=i+1;j<10;++j){
				if(*(ptr+j)>*(ptr+i)){
					int temp=*(ptr+j);
					*(ptr+j)=*(ptr+i);
					*(ptr+i)=temp;
				}
			}
		}
	    printf("c:sorted data\n");
	    for(int i=0;i<10;i++){
			printf("%d ",*(ptr+i));
		}
		printf("I am signaling the parent\n");
		kill(getppid(),SIGUSR2);
		printf("c:I am going to terminate\n");
	}
	if(pid>0){
		printf("p:i am parent\n");
		printf("p:Enter 10 data\n");
		for(int i=0;i<10;i++){
			scanf("%d",ptr+i);
		}
		printf("p:Succesfully readed data\n");
		printf("p:child u can procced\n");
		kill(pid,SIGUSR1);
		printf("p:iam waiting for child to finish\n");
		pause();
		printf("p:i am terminating\n");
	}
	shmdt(ptr);
	return 0;
}
		
		
		
