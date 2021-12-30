/ CPU-Scheduling-Algorithm-In-C
// Non Pre-emptive Priority Scheduling Algorithm
// with Arrival Time

#include<stdio.h>
#include<malloc.h>
void main()
{
    int n, i, j, pos, temp, * burstTime, * waitingTime, * turnaroundTime, * process, * priorityTime, * arrivalTime, * priorityArray;
    float avgwt = 0, avgtat = 0, totalTime = 0;
    // tat Turnaround time
    // wt waiting time
    printf("\n Enter the number of processes : ");
    scanf("%d", &n);

    process = (int*)malloc(n * sizeof(int));     // p[n]
    burstTime = (int*)malloc(n * sizeof(int));    // Burst time
    priorityTime = (int*)malloc(n * sizeof(int));    // Priority time
    waitingTime = (int*)malloc(n * sizeof(int));    // Waiting time
    turnaroundTime = (int*)malloc(n * sizeof(int));   // Turnaround time
    arrivalTime = (int*)malloc(n * sizeof(int)); //Arrival time
    priorityArray = (int*)malloc(n * sizeof(int));
    
    printf("\n Enter the burst time and priority for each process ");
    for (i = 0; i < n; i++)
    {
        printf("\n Burst time of P%d : ", i);
        scanf("%d", &burstTime[i]);
        printf(" Priority of P%d : ", i);
        scanf("%d", &priorityTime[i]);
        printf(" Arrival Time of P%d : ", i);
        scanf("%d", &arrivalTime[i]);
        process[i] = i;
    }

    for (i = 0; i < n; i++)
    {
        pos = i;
        for (j = i + 1; j < n; j++)
        {
            // pos = i first
            // j second
            if (arrivalTime[j] < arrivalTime[pos])
            {
                pos = j;
            }
        }
        // priorityTime
        temp = priorityTime[i];
        priorityTime[i] = priorityTime[pos];
        priorityTime[pos] = temp;
         
        // burstTime
        temp = burstTime[i];
        burstTime[i] = burstTime[pos];
        burstTime[pos] = temp;

        // process
        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;

        // arrivalTime
        temp = arrivalTime[i];
        arrivalTime[i] = arrivalTime[pos];
        arrivalTime[pos] = temp;
    }

    waitingTime[0] = 0;
    turnaroundTime[0] = burstTime[0];
    totalTime = burstTime[0];

    avgwt += waitingTime[0];
    avgtat += turnaroundTime[0];
    j = 0;
    int stop = 1;
    for (i = 1; i < n; i++)
    {

        stop = i;
        j = 0;
        // array of arrival index
        for (; stop < n; stop++)
        {
            if (arrivalTime[stop] <= totalTime) {
                priorityArray[j] = stop;
                j++;
            }
        }
        i += j - 1;
        int cou = 0, cou2 = 0;
        for (; cou < j; cou++)
        {
            pos = cou;
            for (cou2 = cou + 1; cou2 < j; cou2++)
            {
                // pos = cou first
                // cou2 second
                if (priorityTime[priorityArray[cou2]] < priorityTime[priorityArray[pos]])
                {
                    pos = cou2;
                }
            }
            // priorityTime
            temp = priorityArray[cou];
            priorityArray[cou] = priorityArray[pos];
            priorityArray[pos] = temp;
        }
        
        for (cou = 0; cou < j; cou++)
        {
            waitingTime[priorityArray[cou]] = totalTime - arrivalTime[priorityArray[cou]];
            totalTime += burstTime[priorityArray[cou]];
            turnaroundTime[priorityArray[cou]] = waitingTime[priorityArray[cou]] + burstTime[priorityArray[cou]];
            avgwt += waitingTime[priorityArray[cou]];
            avgtat += turnaroundTime[priorityArray[cou]];
        }
        //waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];  //waiting time[p] = waiting time[p-1] + Burst Time[p-1]
        //turnaroundTime[i] = waitingTime[i] + burstTime[i];     //Turnaround Time = Waiting Time + Burst Time

        /*avgwt += waitingTime[i];
        avgtat += turnaroundTime[i];*/
    }

    avgwt = avgwt / n;
    avgtat = avgtat / n;

    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);

    /*printf("\n PROCESS \t PRIORITY \t BURST TIME \t WAITING TIME \t TURNAROUND TIME \n");
    printf("--------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        printf(" P%d \t\t %d \t\t %d \t\t %d \t\t %d \n", p[i], pt[i], bt[i], wt[i], tat[i]);
    }
    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);
    printf("\n \tGAANT CHART \n");
    printf("---------------------------\n");
    for (i = 0; i < n; i++)
    {
        printf(" %d\t|| P%d ||\t%d\n", wt[i], p[i], tat[i]);
    }*/
}