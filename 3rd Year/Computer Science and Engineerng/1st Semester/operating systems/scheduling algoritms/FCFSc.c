//FCFS C implementation

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void sort(int **matrix, int process)
{
    for (int i = 0; i < process; i++)
    {
        for (int j = i + 1; j < process; j++)
        {
            if (matrix[i][1] > matrix[j][1])
            {
                for (int k = 0; k < 4; k++)
                {
                    int temp = matrix[i][k];
                    matrix[i][k] = matrix[j][k];
                    matrix[j][k] = temp;
                }
            }
        }
    }
}
#define max(a, b) (((a) > (b)) ? (a) : (b))
void FCFSandPrint(int **matrix, int totalProcess)
{
    int time = 0, waitingTime = 0;
    printf("Process ID\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for (int i = 0; i < totalProcess; i++)
    {
        time = max(time, matrix[i][1]);
        // printf("%d ", time);
        matrix[i][3] = time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t", matrix[i][0], matrix[i][1], matrix[i][2], time, time + matrix[i][2]);
        printf("%d\t\t\t%d\n", time+matrix[i][2] - matrix[i][1], matrix[i][3] - matrix[i][1]);
        waitingTime += (time - matrix[i][1]);
        time += matrix[i][2];
    }
    printf("Averange Waiting Time-> %f\n", (float)(((float)waitingTime) / totalProcess));
    printf("Total time-> %d\n", time);
}

int main()
{
    int TotalProcess;
    printf("Enter number of process-> ");
    scanf("%d", &TotalProcess);
    int **matrix = (int **)malloc(100 * sizeof(int *));
    for (int i = 0; i < TotalProcess; i++)
        matrix[i] = (int *)malloc(100 * sizeof(int));
    for (int i = 0; i < TotalProcess; i++)
    {
        printf("Enter process ID, Arrival Time, Burst Time->");
        for (int j = 0; j < 3; j++)
            scanf("%d", &matrix[i][j]);
    }
    sort(matrix, TotalProcess);
    FCFSandPrint(matrix, TotalProcess);
}