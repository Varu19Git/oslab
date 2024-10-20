#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define SIZE 5

void sort(int arr[],int n){
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-1;j++){
			if(arr[j]>arr[j+1]){
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}
int main(){
	int pipefd[2];
	int numbers[SIZE]={7,8,4,9,1};
	int sorted_numbers[SIZE];
	pid_t pid;
	
	if(pipe(pipefd)==-1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	pid=fork();
	
	if(pid<0){
		perror("fork");
		exit(EXIT_SUCCESS);
	}
	if(pid>0){
		close(pipefd[0]);
		write(pipefd[1],numbers,sizeof(numbers));
		close(pipefd[1]);
		
		wait(NULL);
	}
	else{
		close(pipefd[1]);
		read(pipefd[0],sorted_numbers,sizeof(sorted_numbers));
		close(pipefd[0]);
		
		sort(sorted_numbers,SIZE);
		
		for(int i=0;i<SIZE;i++){
			printf("%d ",sorted_numbers[i]);
		}
		printf("\n");
		exit(0);
	}
	return 0;
}
