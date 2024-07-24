#include<stdio.h>
#define max 30
typedef struct pass
{
	int pid,at,bt,ct,st,tat,wt;
}ps;
int main()
{
	ps p[max],temp;
	int n,i,j;
	float stat=0,swt=0,atat=0,awt=0;
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
		for(j=0;j<n-1;j++)
		{
			if(p[j].at>p[j+1].at)
			{
				temp= p[j]; 
				p[j]=p[j+1];
				p[j+1]= temp;
			}
		}
	}	
	int curt=p[0].at;
	for(i=0;i<n;i++)
	{
		int min_bt=p[i].bt;
		int min_index=i;
		for(j=i+1;j<n;j++)
		{
			if(p[j].at<=curt && p[j].bt<min_bt)
			{
				min_bt=p[j].bt;
				min_index=j;
			}
		}
		temp=p[i];
		p[i]=p[min_index];
		p[min_index]=temp;
		if(p[i].at > p[i-1].ct)
		    p[i].st=p[i].at;
		else
		    p[i].st=curt;
		p[i].ct=p[i].st+p[i].bt;
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].st-p[i].at;
		curt=p[i].ct;
	    stat+=p[i].tat;
		swt+=p[i].wt;
	}
	atat=stat/n;
	awt=swt/n;
	printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].tat,p[i].wt);
		
	}
	printf("Average TAT: %f\n",atat);
	printf("Average WT: %f\n",awt);	
	return 0;
}
