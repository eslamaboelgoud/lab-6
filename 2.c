// CPU-Scheduling-Algorithm-In-C
// Shortest Job First(SJF) Scheduling Algorithm(Non Pre-emptive)

#include<stdio.h>
#include<malloc.h>

void main()
{
    int n, i, j, pos, temp, * bt, * wt, * tat, * p, *arrivalTime, * readyArray;
    float avgwt = 0, avgtat = 0;
    printf("\n Enter the number of processes : ");
    scanf("%d", &n);

    p = (int*)malloc(n * sizeof(int));
    bt = (int*)malloc(n * sizeof(int));
    wt = (int*)malloc(n * sizeof(int));
    tat = (int*)malloc(n * sizeof(int));
    arrivalTime = (int*)malloc(n * sizeof(int));
    readyArray = (int*)malloc(n * sizeof(int));

    printf("\n Enter the burst time for each process \n");
    for (i = 0; i < n; i++)
    {
        printf(" Burst time for P%d : ", i);
        scanf("%d", &bt[i]);
        printf(" Arrival time for P%d : ", i);
        scanf("%d", &arrivalTime[i]);
        p[i] = i;
    }
    // sort arrival time
    for (i = 0; i < n; i++)
    {
        pos = i;
        for (j = i + 1; j < n; j++)
        {
            if (arrivalTime[j] < arrivalTime[pos])
            {
                pos = j;
            }
        }
        // arival time
        temp = arrivalTime[i];
        arrivalTime[i] = arrivalTime[pos];
        arrivalTime[pos] = temp;
        // burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;
        // process
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    int totalTime = 0;
    wt[0] = 0;
    tat[0] = bt[0];
    totalTime = bt[0];
    avgwt += wt[0];
    avgtat += tat[0];
    int counter = 0;
    int counter2 = 1;
    for (; counter2 < n; )
    {
        //fill readyArray
        for (i = counter2; i < n; i++)
        {
            if (arrivalTime[i] <= totalTime) {
                readyArray[counter] = i;
                counter++;
                counter2 = i+1;
            }
        }
        
        // sort readyArray index
        for (i = 0; i < counter; i++)
        {
            pos = i;
            for (j = i + 1; j < counter; j++)
            {
                if (bt[readyArray[j]] < bt[readyArray[pos]])
                {
                    readyArray[pos] = readyArray[j];
                }
            }
            temp = readyArray[i];
            readyArray[i] = readyArray[pos];
            readyArray[pos] = temp;
        }
        // calc wt tat
        for (i = 0 ; i < counter; i++)
        {
            wt[readyArray[i]] = totalTime - arrivalTime[readyArray[i]];
            totalTime += bt[readyArray[i]];
            tat[readyArray[i]] = wt[readyArray[i]] + bt[readyArray[i]];
            avgwt += wt[readyArray[i]];
            avgtat += tat[readyArray[i]];
        }
        counter = 0;
    }
    avgwt = avgwt / n;
    avgtat = avgtat / n;
    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);
}