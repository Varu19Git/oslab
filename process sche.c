#include<stdio.h>
#define max 30
typedef struct pass
{
	int pid,at,bt,ct,st,tat,wt;
}ps;
int main()
{
	ps p[max];
	int n,i,j,temp=0,stat=0,swt=0;
	float atat,awt;
	printf("Enter the No.of processor");
	scanf("%d",&n);
	printf("Enter the processor id\n");
	for(i=0;i<n;i++)
		scanf("%d",&p[i].pid);
	printf("Enter the Arival time\n");
	for(i=0;i<n;i++)
		scanf("%d",&p[i].at);
	printf("Enter the burst time\n");
	for( i=0;i<n;i++)
		scanf("%d",&p[i].bt);
		
		
	for( i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(p[j].at>p[j+1].at)
			{
				temp=p[j+1].pid; 
				p[j+1].pid=p[j].pid;
				p[j].pid=temp;
				
				temp=p[j+1].at; 
				p[j+1].at=p[j].at;
				p[j].at=temp;
				
				temp=p[j+1].bt; 
				p[j+1].bt=p[j].bt;
				p[j].bt=temp;
			}
		}
	}	
	p[0].st=p[0].at;
	p[0].ct=p[0].st+p[0].bt;
	for(i=1;i<n;i++)
	{
		if(p[i].at > p[i-1].ct)
		p[i].st=p[i].at;
		else
		p[i].st=p[i-1].ct;
		
		p[i].ct=p[i].st+p[i].bt;
	}
	printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\n");
	for(i=0;i<n;i++)
	{
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
		stat+=p[i].tat;
		swt+=p[i].wt;
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].tat,p[i].wt);
		
	}	
	atat=(float)stat/n;
	awt=(float)swt/n;
	printf("Average TAT: %.2f\n",atat);
	printf("AVerage WT: %.2f",awt);
	return 0;
}
