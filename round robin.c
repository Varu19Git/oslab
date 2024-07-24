/*#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
#define MAX 30

typedef struct roundrobin {
    int pid, at, bt, ct, st[10], tat, wt;
} process;

int main() {
    process p[MAX];
    int i, n, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the process IDs:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i].pid);

    printf("Enter the arrival times:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i].at);

    printf("Enter the burst times:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i].bt);

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    int c = n;
    float time = 0;
    int b[MAX], a[MAX];
    bool flag = false;

    for (i = 0; i < n; i++) {
        b[i] = p[i].bt;
        a[i] = p[i].at;
    }

    int tot_wt = 0, tot_tat = 0;

    while (c!= 0) {
        int min_index = -1;
        int min_arrival_time = INT_MAX;

        for (i = 0; i < n; i++) {
            if (a[i] <= time && min_arrival_time > a[i] && b[i] > 0) {
                min_index = i;
                min_arrival_time = a[i];
                flag = true;
            }
        }

        if (!flag) {
            time++;
            continue;
        }

        flag = false;

        int j = 0;
        while (p[min_index].st[j]!= 0)
            j++;

        p[min_index].st[j] = time;

        if (b[min_index] <= tq) {
            time += b[min_index];
            b[min_index] = 0;
        } else {
            time += tq;
            b[min_index] -= tq;
        }

        if (b[min_index] > 0)
            a[min_index] = time + 0.1;

        if (b[min_index] == 0) {
            c--;
            p[min_index].ct = time;
            p[min_index].wt = p[min_index].ct - p[min_index].at - p[min_index].bt;
            tot_wt += p[min_index].wt;
            p[min_index].tat = p[min_index].ct - p[min_index].at;
            tot_tat += p[min_index].tat;
        }
    }

    printf("P_id\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    float atat = (float)tot_wt / n;
    float awt = (float)tot_tat / n;

    printf("Average TAT: %f\n", atat);
    printf("Average WT: %f\n", awt);

    return 0;
}*/
#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

struct P
{
	int AT,BT,ST[20],WT,FT,TAT,pos;
};

int quant;

int main()
{
    int n, i, j;
    printf("Enter the no. of processes: ");
    scanf("%d",&n);
    struct P p[n];

    printf("Enter the quantum: ");
    scanf("%d",&quant);

    printf("Enter the process numbers: ");
    for(i=0;i<n;i++) 
		scanf("%d",&(p[i].pos));

    printf("Enter the Arrival time of processes: ");
    for(i=0;i<n;i++) 
		scanf("%d",&(p[i].AT));

    printf("Enter the Burst time of processes: ");
    for(i=0;i<n;i++) 
		scanf("%d",&(p[i].BT));

    int c=n, s[n][20];
    float time=0, mini=INT_MAX, b[n], a[n];
    int index=-1;
    for(i=0;i<n;i++)
	{
        b[i]=p[i].BT; 
		a[i]=p[i].AT;
        for(j=0;j<20;j++) 
			s[i][j]=-1;
    }

    int tot_wt=0, tot_tat=0;
    bool flag=false;

    while(c!=0)
	{
        mini=INT_MAX; flag=false;
        for(i=0;i<n;i++)
		{
            float p=time+0.1;
            if(a[i]<=p && mini>a[i] && b[i]>0)
			{
                index=i; 
				mini=a[i];
				flag=true;
            }
        }
        if(!flag)
		{ 
			time++;
			continue; 
		}
        j=0;
        while(s[index][j]!=-1) 
			j++;
        if(s[index][j]==-1)
		{ 
			s[index][j]=time; 
			p[index].ST[j]=time; 
		}
        if(b[index]<=quant)
		{ 
			time+=b[index]; 
			b[index]=0;
		}
        else
		{
			time+=quant; 
			b[index]-=quant; 
		}
        if(b[index]>0)
			a[index]=time+0.1;
        if(b[index]==0)
		{
            c--; 
			p[index].FT=time;
            p[index].WT=p[index].FT-p[index].AT-p[index].BT;
            tot_wt+=p[index].WT;
            p[index].TAT=p[index].BT+p[index].WT;
            tot_tat+=p[index].TAT;
        }
    }

    printf("P_id\tAT\tBT\tCT\tWT\tTAT\n");

    for(i=0;i<n;i++)
	{
        printf("%d\t%d\t%d\t", p[i].pos, p[i].AT, p[i].BT);
        printf("%d\t%d\t%d\n", p[i].FT, p[i].WT, p[i].TAT);
    }

    double avg_wt=tot_wt/(float)n, avg_tat=tot_tat/(float)n;
    printf("The average wait time is: %lf\n", avg_wt);
    printf("The average TurnAround time is: %lf\n", avg_tat);

    return 0;
}
